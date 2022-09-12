/*
 * lfsr.h
 * Scrambler
 *
 */
void resetLfsr();
void advanceLfsr();
extern unsigned short lfsr;
extern unsigned short lfsrSeed;
/*
 * lfsr.c
 * Scrambler
 *
 */
#include "DPScramble.h"
#include "lfsr.h"
/*
this routine implements the serial scrambling/descrambling algorithm in parallel form
for the internal LFSR polynomial: X^16+x^5+x^4+x^3+1
this advances the LFSR 8 bits every time it is called
this requires fewer than 25 xor gates to implement (with a static register)
The XOR required to advance 8 bits/clock is
bit 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
8 9 10 11 12 13 14 15 0 1 2 3 4 5 6 7
8 9 10 11 12 13 14 15
8 9 10 11 12 13 14 15
8 9 10 11 12 13 14 15
*/
unsigned short lfsr;
unsigned short lfsrSeed;
void resetLfsr() {
    lfsr = lfsrSeed;
}
void advanceLfsr() {
    int i;
    int bit[16];
    int bitOut[16];
    for (i = 0; i < 16; i++) // convert LFSR to bit array for legibility
        bit[i] = (lfsr >> i) & 1;
    // Advance the LFSR 8 serial clocks
    bitOut[0] = bit[8];
    bitOut[1] = bit[9];
    bitOut[2] = bit[10];
    bitOut[3] = bit[11] ^ bit[8];
    bitOut[4] = bit[12] ^ bit[9] ^ bit[8];
    bitOut[5] = bit[13] ^ bit[10] ^ bit[9] ^ bit[8];
    bitOut[6] = bit[14] ^ bit[11] ^ bit[10] ^ bit[9];
    bitOut[7] = bit[15] ^ bit[12] ^ bit[11] ^ bit[10];
    bitOut[8] = bit[0] ^ bit[13] ^ bit[12] ^ bit[11];
    bitOut[9] = bit[1] ^ bit[14] ^ bit[13] ^ bit[12];
    bitOut[10] = bit[2] ^ bit[15] ^ bit[14] ^ bit[13];
    bitOut[11] = bit[3] ^ bit[15] ^ bit[14];
    bitOut[12] = bit[4] ^ bit[15];
    bitOut[13] = bit[5];
    bitOut[14] = bit[6];
    bitOut[15] = bit[7];
    lfsr = 0;
    for (i = 0; i < 16; i++) // convert the LFSR back to an integer
        lfsr += (bitOut[i] << i);
}
/*
 *
 * DisplayPort Scrambler
 *
 * Includes scrambling of DP control symbols, and conversion between
 * DP control symbols and K codes
 *
 */
extern bool TrainingSequence; // TRUE if in training sequence
extern bool Multistream;      // TRUE if using Multi-stream format
extern bool DP_TX;            // TRUE at DP transmitter, FALSE at DP receiver
extern bool EnhancedFraming;  // TRUE for SST-mode connection using Enhanced Framing
extern int srSeq[4];
// K-code Single-stream Multi-stream
#define K28d0 0x11c // SR GP1 index 2
#define K28d1 0x13c // CP GP2 rsvd
#define K28d2 0x15c // SS GP1 index 3
#define K28d3 0x17c // BF GP1 index 4
#define K28d4 0x19c // rsvd GP2 rsvd
#define K28d5 0x1bc // BS GP2 SR
#define K28d6 0x1dc // rsvd GP1 index 5
#define K28d7 0x1fc // rsvd GP2 rsvd
#define K23d7 0x1f7 // FE GP1 index 0
#define K27d7 0x1fb // BE GP1 index 1
#define K29d7 0x1fd // SE GP1 index 6
#define K30d7 0x1fe // FS GP1 index 7
// Control symbols for single stream operation
enum { SR = K28d0, CP = K28d1, SS = K28d2, BF = K28d3, BS = K28d5, FE = K23d7, BE = K27d7, SE = K29d7, FS = K30d7 };
// Control symbols for multi stream operation
enum { MS_SR = K28d5 };
extern const int scrControlToKcode[8];
void resetSRSeq();
enum MS_SR_States { MS_SR_Reset, MS_SR_Lock1, MS_SR_Lock2, MS_SR_Locked, MS_SR_Error1, MS_SR_Error2 };
int scrambleByte(int inByte);
/*
 *
 * DisplayPort Scrambler
 *
 */
#include "DPScramble.h"
#include "lfsr.h"
/*
this routine implements the scrambling/descrambling algorithm in parallel form
The data is scrambled with the top byte of the lfsr. Note that the effect of scrambling
in parallel form is to bit reverse the top byte of the lfsr
data bit 7 6 5 4 3 2 1 0
lfsr bit 8 9 10 11 12 13 14 15
this routine is called on the TX side to scramble the outgoing symbol
and on the RX side to descramble the incoming symbol
the parameter inByte is either
a data value in the range 0 - 255
a representation of a K-code, represented as 0x100+val
a representation of a DP Control Symbol, represented by 0x200+index
(applies only on the transmit/scrambling side)
a representation of an errored symbol, represented by 0x400
the return value is encoded similarly
a data value in the range 0 - 255
a representation of a K-code, represented as 0x100+val
a representation of a DP Control Symbol, represented by 0x200+index
(applies only on the receive/descrambling side)
for robustness scrambler reset purposes, this function maintains the state variable
inEnhSRSeq between calls
*/
// the following defines the conversion between scrambled symbol index to K code
// 0 1 2 3 4 5 6 7
const int scrControlToKcode[8] = {K23d7, K27d7, K28d0, K28d2, K28d3, K28d6, K29d7, K30d7};
int srSeq[4];
bool inEnhSRSeq; // TRUE if have recognized the start of an Enhanced Framing scrambler reset sequence
enum MS_SR_States MS_SR_State = MS_SR_Reset;
unsigned short int MS_SR_symbol_count = 0; // 16 bit, wraps to zero after counting to 65535
void resetSRSeq() {
    int i;
    for (i = 0; i < 4; i++) srSeq[i] = 0;
}
int scrambleByte(int inByte) {
    int scrambit[16];
    int bit[16];
    int i, outbyte;
    int temp;       // for debugging
    if (inByte < 0) // called after the end of stream has been met
        return -1;
    // on descramble at the receiver in multistream mode, convert Kcodes in group 1 to
    // control symbol indices
    if (Multistream && !DP_TX) {
        for (i = 0; i < 8; i++)
            if (inByte == scrControlToKcode[i]) {
                inByte = i + 0x200;
                break;
            }
    }
    for (i = 0; i < 16; i++) { // convert LFSR to bit array for legibility
        bit[i] = (lfsr >> i) & 1;
    }
    for (i = 0; i < 11; i++)              // convert byte to be (un-)scrambled for legibility
        scrambit[i] = (inByte >> i) & 1;  // preserve Kcode and control symbol distinctive bits
    if ((!((inByte & 0x100) == 0x100)) && // if not a Kcode,
        (!((inByte & 0x400) == 0x400)) && // and not an errored symbol
        (!(TrainingSequence == TRUE)))    // and not in the middle of a training sequence
    {                                     // scramble or unscramble the data
        scrambit[0] ^= bit[15];           // data and multistream control symbol bit 0
        scrambit[1] ^= bit[14];           // data and multistream control symbol bit 1
        scrambit[2] ^= bit[13];           // data and multistream control symbol bit 2
        scrambit[3] ^= bit[12];           // data bit 3
        scrambit[4] ^= bit[11];           // data bit 4
        scrambit[5] ^= bit[10];           // data bit 5
        scrambit[6] ^= bit[9];            // data bit 6
        scrambit[7] ^= bit[8];            // data bit 7
    }
    advanceLfsr();
    // reset scrambler at scrambler reset time
    if (Multistream) { // Multistream as defined in DP Standard
        MS_SR_symbol_count++;
        if (inByte == MS_SR) {
            // robustness scrambler reset mechanism here, based on SR reception
            // at the correct interval (every 65536 symbols) - see DP MST section
            switch (MS_SR_State) {
                case MS_SR_Reset:
                    resetLfsr();
                    MS_SR_symbol_count = 0; // reset counter on entry to Lock1
                    MS_SR_State = MS_SR_Lock1;
                    break;
                case MS_SR_Lock1:
                    if (MS_SR_symbol_count == 0) {
                        resetLfsr();
                        MS_SR_State = MS_SR_Lock2;
                    }                       // else stay in this state
                    MS_SR_symbol_count = 0; // reset counter on re-entry to state
                    break;
                case MS_SR_Lock2:
                    if (MS_SR_symbol_count == 0) {
                        resetLfsr();
                        MS_SR_State = MS_SR_Locked;
                    } else {                    // Invalid position for a reset symbol
                        MS_SR_symbol_count = 0; // reset counter on entry to Lock1
                        MS_SR_State = MS_SR_Lock1;
                    }
                    break;
                case MS_SR_Locked:
                    if (MS_SR_symbol_count == 0) {
                        resetLfsr();
                    } else { // Invalid position for a reset symbol
                        MS_SR_State = MS_SR_Error1;
                        // don't adjust symbol count
                    }
                    break;
                case MS_SR_Error1:
                    if (MS_SR_symbol_count == 0) {
                        resetLfsr();
                        MS_SR_State = MS_SR_Locked;
                    } else { // Invalid position for a reset symbol
                        MS_SR_State = MS_SR_Error2;
                        // don't adjust symbol count
                    }
                case MS_SR_Error2:
                    if (MS_SR_symbol_count == 0) {
                        resetLfsr();
                        MS_SR_State = MS_SR_Locked;
                    } else {                       // Invalid position for a reset symbol
                        MS_SR_symbol_count = 0;    // on entry to Lock1
                        MS_SR_State = MS_SR_Lock1; // to restart the sync
                    }
                    break;
            } // end of MS_SR robustness state machine
        }     // end of processing SR
    } else {  // Single stream
        if (EnhancedFraming) {
            if (((inByte == SR) || (inByte == CP)) || (inByte == BF) || inEnhSRSeq) {
                // robustness scrambler reset mechanism here for enhanced framing, based on
                // detection of two correctly placed symbols in the sequence SR+BF+BF+SR or SR+CP+CP+SR
                // note that ??+BF+BF+?? is assumed to be BS, not SR
                if ((inByte == SR) || (inByte == CP) || (inByte == BF)) inEnhSRSeq = TRUE;
                for (i = 0; i < 3; i++) srSeq[i] = srSeq[i + 1]; // shuffle up
                srSeq[3] = ((inByte == SR) || (inByte == CP) || (inByte == BF)) ? inByte : 0;
                if (((srSeq[0] == SR) && ((srSeq[1] == BF) || (srSeq[1] == CP))) ||
                    ((srSeq[0] == SR) && ((srSeq[2] == BF) || (srSeq[2] == CP))) ||
                    ((srSeq[0] == SR) && (srSeq[3] == SR)) ||
                    (((srSeq[1] == CP) || (srSeq[1] == BF)) && (srSeq[3] == SR)) ||
                    (((srSeq[2] == CP) || (srSeq[2] == BF)) && (srSeq[3] == SR))) { // reset scrambler
                    resetLfsr();
                    resetSRSeq();
                    inEnhSRSeq = FALSE;
                }
                if ((srSeq[0] == 0) && (srSeq[1] == 0) && (srSeq[2] == 0) && (srSeq[3] == 0))
                    inEnhSRSeq = FALSE; // must have got into this as a result of
                // a bit error generating an isolated CP or SR
            }    // end of robustness mechanism
        } else { // Default Framing
            if (inByte == SR) resetLfsr();
        }
    }
    outbyte = 0;
    for (i = 0; i < 11; i++) { // convert data back to an integer
        temp = scrambit[i] << i;
        outbyte += (scrambit[i] << i);
    }
    // Convert control symbol to Kcode in multistream mode at the transmitter
    if (Multistream && DPTX && ((outbyte & 0x200) == 0x200)) outbyte = scrControlToKcode[outbyte & 0x7];
    return outbyte;
}
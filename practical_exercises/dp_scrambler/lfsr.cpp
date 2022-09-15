
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
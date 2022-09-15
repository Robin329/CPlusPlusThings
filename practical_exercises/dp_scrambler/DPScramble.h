
/*
 *
 * DisplayPort Scrambler
 *
 * Includes scrambling of DP control symbols, and conversion between
 * DP control symbols and K codes
 *
 */
#ifndef __DP_SCRAMBLER_H__
#define __DP_SCRAMBLER_H__
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

#define DPTX 1 // DP transmitter

// Control symbols for single stream operation
enum { SR = K28d0, CP = K28d1, SS = K28d2, BF = K28d3, BS = K28d5, FE = K23d7, BE = K27d7, SE = K29d7, FS = K30d7 };
// Control symbols for multi stream operation
enum { MS_SR = K28d5 };
extern const int scrControlToKcode[8];
void resetSRSeq();
enum MS_SR_States { MS_SR_Reset, MS_SR_Lock1, MS_SR_Lock2, MS_SR_Locked, MS_SR_Error1, MS_SR_Error2 };
int scrambleByte(int inByte);
#endif /* __DP_SCRAMBLER_H__ */
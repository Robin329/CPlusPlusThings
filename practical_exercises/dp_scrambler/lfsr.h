/*
 * lfsr.h
 * Scrambler
 *
 */
void resetLfsr();
void advanceLfsr();
extern unsigned short lfsr;
extern unsigned short lfsrSeed;
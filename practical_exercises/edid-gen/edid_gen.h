#ifndef __EDID_GEN_H__
#define __EDID_GEN_H__
#include <stdio.h>



#define EDID_SIZE 128

struct dtd {
	uint16_t pixel_repetition_input;
	int pixel_clock; /* kHz */
	uint8_t interlaced; /* 1 for interlaced, 0 progressive */
	uint16_t h_active;
	uint16_t h_blanking;
	uint16_t h_image_size;
	uint16_t h_sync_offset;
	uint16_t h_sync_pulse_width;
	uint8_t h_sync_polarity;
	uint16_t v_active;
	uint16_t v_blanking;
	uint16_t v_image_size;
	uint16_t v_sync_offset;
	uint16_t v_sync_pulse_width;
	uint8_t v_sync_polarity;
};

static inline void dump_dtd(struct dtd *d) {
	printf("\n\n");
	printf("       pixel_clock:%d\n", d->pixel_clock);
	printf("        interlaced:%d\n", d->interlaced);
	printf("          h_active:%d\n", d->h_active);
	printf("        h_blanking:%d\n", d->h_blanking);
	printf("      h_image_size:%d\n", d->h_image_size);
	printf("     h_sync_offset:%d\n", d->h_sync_offset);
	printf("h_sync_pulse_width:%d\n", d->h_sync_pulse_width);
	printf("   h_sync_polarity:%d\n", d->h_sync_polarity);
	printf("          v_active:%d\n", d->v_active);
	printf("        v_blanking:%d\n", d->v_blanking);
	printf("      v_image_size:%d\n", d->v_image_size);
	printf("     v_sync_offset:%d\n", d->v_sync_offset);
	printf("v_sync_pulse_width:%d\n", d->v_sync_pulse_width);
	printf("   v_sync_polarity:%d\n", d->v_sync_polarity);
	printf("\n\n");
}

static inline int edid_block_checksum(const uint8_t *raw_edid)
{
	int i;
	uint8_t csum = 0, crc = 0;

	for (i = 0; i < EDID_SIZE - 1; i++)
		csum += raw_edid[i];

	crc = 0x100 - csum;

	return crc;
}

#define BITS_PER_LONG 64

#define __AC(X, Y) (X##Y)
#define _AC(X, Y)  __AC(X, Y)
#define _AT(T, X)  ((T)(X))

#define _UL(x)		(_AC(x, UL))
#define _ULL(x)		(_AC(x, ULL))
#define UL(x)		(_UL(x))
#define ULL(x)		(_ULL(x))

#define __GENMASK(h, l)                    \
	(((~UL(0)) - (UL(1) << (l)) + 1) & \
	 (~UL(0) >> (BITS_PER_LONG - 1 - (h))))
#define GENMASK(h, l) __GENMASK(h, l)

#endif  /* __EDID_GEN_H__ */
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>

#include "edid_gen.h"

static uint8_t fake_edid[] = {
	0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x0A, 0x74, 0x00, 0x12, 0xB0, 0x04, 0x00, 0x00,
	0x28, 0x21, 0x01, 0x03, 0xB5, 0x35, 0x1E, 0x78, 0x23, 0xA6, 0x31, 0xA8, 0x55, 0x51, 0x9D, 0x25,
	0x0F, 0x50, 0x54, 0x00, 0x00, 0x00, 0xD1, 0xC0, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02, 0x3A, 0x80, 0x18, 0x71, 0x38, 0x2D, 0x40, 0x58, 0x2C,
	0x45, 0x00, 0xE0, 0x0E, 0x11, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0xFD, 0x00, 0x30, 0x4C, 0x55,
	0x55, 0x12, 0x01, 0x0A, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 0xFC, 0x00, 0x42,
	0x6C, 0x61, 0x63, 0x6B, 0x20, 0x53, 0x65, 0x73, 0x61, 0x6D, 0x65, 0x0A, 0x00, 0x00, 0x00, 0x10,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x58,
};


struct dtd define_dtd[] = {
	{
		/* vic 1 */
		.h_image_size = 4,
		.v_image_size = 3,
		.h_active = 640,
		.v_active = 480,
		.h_blanking = 160,
		.v_blanking = 45,
		.h_sync_offset = 16,
		.v_sync_offset = 10,
		.h_sync_pulse_width = 96,
		.v_sync_pulse_width = 2,
		.h_sync_polarity = 0,
		.v_sync_polarity = 0,
		.interlaced = 0, /* (progressive_nI) */
		.pixel_clock = 25175,
	},
	{
		/* vic 4 */
		/* 1280x720p @ 59.94/60Hz 16:9 */
		.h_active = 1280,
		.v_active = 720,
		.h_blanking = 370,
		.v_blanking = 30,
		.h_sync_offset = 110,
		.v_sync_offset = 5,
		.h_sync_pulse_width = 40,
		.v_sync_pulse_width = 5,
		.h_sync_polarity = 1,
		.v_sync_polarity = 1,
		.interlaced = 0,
		.pixel_clock = 74250,
	},
	{
		/* vic 96  */
		.h_active = 3840,
		.v_active = 2160,
		.h_blanking = 1440,
		.v_blanking = 90,
		.h_sync_offset = 1056,
		.v_sync_offset = 8,
		.h_sync_pulse_width = 88,
		.v_sync_pulse_width = 10,
		.h_sync_polarity = 1,
		.v_sync_polarity = 1,
		.interlaced = 0,
		.pixel_clock = 594000,
	},
	{
		.h_active = 1920,
		.v_active = 1080,
		.h_blanking = 280,
		.v_blanking = 45,
		.h_sync_offset = 88,
		.v_sync_offset = 4,
		.h_sync_pulse_width = 44,
		.v_sync_pulse_width = 5,
		.h_sync_polarity = 1,
		.v_sync_polarity = 1,
		.interlaced = 0,
		.pixel_clock = 148500,
	}
};

uint8_t edid_bit_field(const uint16_t data, uint8_t shift, uint8_t width)
{
	return ((data >> shift) & ((((uint16_t)1) << width) - 1));
}

uint16_t edid_concat_bits(uint8_t bhi, uint8_t ohi, uint8_t nhi, uint8_t blo,
			  uint8_t olo, uint8_t nlo)
{
	return (edid_bit_field(bhi, ohi, nhi) << nlo) |
	       edid_bit_field(blo, olo, nlo);
}

uint16_t edid_byte_to_word(const uint8_t hi, const uint8_t lo)
{
	return edid_concat_bits(hi, 0, 8, lo, 0, 8);
}

uint32_t edid_byte_to_dword(uint8_t b3, uint8_t b2, uint8_t b1, uint8_t b0)
{
	uint32_t retval = 0;

	retval |= b0 << (0 * 8);
	retval |= b1 << (1 * 8);
	retval |= b2 << (2 * 8);
	retval |= b3 << (3 * 8);
	return retval;
}

int edid_dtd_parse(struct dtd *mdtd, uint8_t data[18])
{
	mdtd->pixel_repetition_input = 0;

	mdtd->pixel_clock = edid_byte_to_word(data[1], data[0]);
	if (mdtd->pixel_clock < 0x01)
		return -EINVAL;

	mdtd->h_active = edid_concat_bits(data[4], 4, 4, data[2], 0, 8);
	mdtd->h_blanking = edid_concat_bits(data[4], 0, 4, data[3], 0, 8);
	mdtd->h_sync_offset = edid_concat_bits(data[11], 6, 2, data[8], 0, 8);
	mdtd->h_sync_pulse_width =
		edid_concat_bits(data[11], 4, 2, data[9], 0, 8);
	mdtd->h_image_size = edid_concat_bits(data[14], 4, 4, data[12], 0, 8);
	mdtd->v_active = edid_concat_bits(data[7], 4, 4, data[5], 0, 8);
	mdtd->v_blanking = edid_concat_bits(data[7], 0, 4, data[6], 0, 8);
	mdtd->v_sync_offset = edid_concat_bits(data[11], 2, 2, data[10], 4, 4);
	mdtd->v_sync_pulse_width =
		edid_concat_bits(data[11], 0, 2, data[10], 0, 4);
	mdtd->v_image_size = edid_concat_bits(data[14], 0, 4, data[13], 0, 8);
	if (edid_bit_field(data[17], 4, 1) != 1)
		return -EINVAL;
	if (edid_bit_field(data[17], 3, 1) != 1)
		return -EINVAL;

	mdtd->interlaced = edid_bit_field(data[17], 7, 1) == 1;
	mdtd->v_sync_polarity = edid_bit_field(data[17], 2, 1) == 0;
	mdtd->h_sync_polarity = edid_bit_field(data[17], 1, 1) == 0;
	if (mdtd->interlaced == 1)
		mdtd->v_active /= 2;
	mdtd->pixel_clock *= 10;
	printf("DTD pixel_clock: %d\ninterlaced: %d\n", mdtd->pixel_clock,
	       mdtd->interlaced);
	printf("h_active: %d\nh_blanking: %d\nh_sync_offset(HFP): %d\nh_back_porch(HBP): %d\n",
	       mdtd->h_active, mdtd->h_blanking, mdtd->h_sync_offset,
	       mdtd->h_blanking - mdtd->h_sync_offset -
		       mdtd->h_sync_pulse_width);
	printf("h_sync_pulse_width(HSYNC): %d\nh_image_size: %d\nh_sync_polarity: %d\n",
	       mdtd->h_sync_pulse_width, mdtd->h_image_size,
	       mdtd->h_sync_polarity);
	printf("v_active: %d\nv_blanking: %d\nv_sync_offset(VFP): %d\nv_back_porch(VBP):%d\n",
	       mdtd->v_active, mdtd->v_blanking, mdtd->v_sync_offset,
	       mdtd->v_blanking - mdtd->v_sync_offset -
		       mdtd->v_sync_pulse_width);
	printf("v_sync_pulse_width(VSYNC): %d\nv_image_size: %d\nv_sync_polarity: %d\n",
	       mdtd->v_sync_pulse_width, mdtd->v_image_size,
	       mdtd->v_sync_polarity);

	return 0;
}

int edid_bit_change(uint8_t *byte, uint8_t shift, uint8_t width,
		    const uint32_t in)
{
	// printf("%#x %#x *byte:%#x\n", ((in & GENMASK(shift - 1, 0)) << shift),
	//        (*byte & ~GENMASK(shift + width - 1, shift)), *byte);
	*byte = ((in & GENMASK(shift - 1, 0)) << shift) |
		(*byte & ~GENMASK(shift + width - 1, shift));

	return 0;
}

int edid_byte_gen(uint8_t *bhi, uint8_t ohi, uint8_t nhi, uint8_t *blo,
		  uint8_t olo, uint8_t nlo, const uint32_t dtd_data)
{
	edid_bit_change(bhi, ohi, nhi, (dtd_data >> nlo));
	edid_bit_change(blo, olo, nlo, dtd_data & GENMASK(nlo - 1, 0));

	return 0;
}

int edid_data_regen(uint8_t *edid, uint8_t size, struct dtd *in_dtd)
{
	uint32_t pixel_clock = in_dtd->pixel_clock * 1000 / 10000;

	if (!size)
		return -1;
	if (!in_dtd)
		return -1;

	dump_dtd(in_dtd);

	// edid[0] = pixel_clock & GENMASK(7, 0);
	// edid[1] = ((pixel_clock & GENMASK(15, 8)) >> 8);
	edid_byte_gen(&edid[1], 0, 8, &edid[0], 0, 8, pixel_clock);
	printf("edid:%#x %#x\n", edid[0], edid[1]);
	edid_byte_gen(&edid[4], 4, 4, &edid[2], 0, 8, in_dtd->h_active);

	edid_byte_gen(&edid[4], 0, 4, &edid[3], 0, 8, in_dtd->h_blanking);
	edid_byte_gen(&edid[11], 6, 2, &edid[8], 0, 8, in_dtd->h_sync_offset);
	edid_byte_gen(&edid[11], 4, 2, &edid[9], 0, 8,
		      in_dtd->h_sync_pulse_width);
	edid_byte_gen(&edid[14], 4, 4, &edid[12], 0, 8, in_dtd->h_image_size);

	edid_byte_gen(&edid[7], 4, 4, &edid[5], 0, 8, in_dtd->v_active);
	edid_byte_gen(&edid[7], 0, 4, &edid[6], 0, 8, in_dtd->v_blanking);
	edid_byte_gen(&edid[11], 2, 2, &edid[10], 4, 4, in_dtd->v_sync_offset);
	edid_byte_gen(&edid[11], 0, 2, &edid[10], 0, 4,
		      in_dtd->v_sync_pulse_width);
	edid_byte_gen(&edid[14], 0, 4, &edid[13], 0, 8, in_dtd->v_image_size);

	edid_bit_change(&edid[17], 7, 1, in_dtd->interlaced);
	edid_bit_change(&edid[17], 2, 1, in_dtd->v_sync_polarity);
	edid_bit_change(&edid[17], 1, 1, in_dtd->h_sync_polarity);

	return 0;
}

int main(int argc, char **argv)
{
	FILE *file;
	uint8_t edid_data[EDID_SIZE];
	char *path;
	int ret;
	struct dtd edid_dtd;

	if (argc < 2) {
		printf("Error, Please input edid path!\n");
		return 0;
	}
	path = argv[1];
	printf("\n\n%s\n\n", path);
	// 打开文件
	file = fopen(path, "r");
	if (file == NULL) {
		fprintf(stderr, "无法打开文件\n");
		return 1;
	}

	printf("----------------\n");
	printf("| Origin EDID  |\n");
	printf("----------------\n");
	// 读取文件内容到edid_data数组
	for (int i = 0; i < EDID_SIZE; ++i) {
		if (fscanf(file, "%hhX ", &edid_data[i]) != 1) {
			fprintf(stderr, "读取文件失败\n");
			fclose(file);
			return 1;
		}
	}

	// 关闭文件
	fclose(file);

	// 打印EDID数据
	for (int i = 0; i < EDID_SIZE; ++i) {
		printf("%02X ", edid_data[i]);
		if ((i + 1) % 16 == 0)
			printf("\n");
	}
	printf("\n\n");

	uint8_t preferred_vic[18];
	memcpy(preferred_vic, edid_data + 0x36, 0x12);
	edid_dtd_parse(&edid_dtd, preferred_vic);

	if (edid_data_regen(&edid_data[0x36], 0x12, &define_dtd[3])) {
		printf("edid data re gen failed!\n");
		return -1;
	}

	edid_data[127] = edid_block_checksum(edid_data);

	printf("edid crc:%#x\n", edid_block_checksum(edid_data));

	printf("----------------\n");
	printf("|   Gen EDID   |\n");
	printf("----------------\n");
	for (int i = 0; i < EDID_SIZE; ++i) {
		printf("%02X ", edid_data[i]);
		if ((i + 1) % 16 == 0)
			printf("\n");
	}
	printf("\n----------------------------------\n\n");

	memcpy(preferred_vic, edid_data + 0x36, 0x12);
	ret = edid_dtd_parse(&edid_dtd, preferred_vic);
	if (ret) {
		printf("edid dtd parse failed!(%d)\n", ret);
		return -1;
	}

	return 0;
}
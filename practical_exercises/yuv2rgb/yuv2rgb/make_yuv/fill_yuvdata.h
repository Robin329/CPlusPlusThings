/**
 * @file   fill_yuvdata.h
 * @author Late Lee <latelee@163.com>
 * @date   Fri Feb 14 15:46:52 2014
 *
 * @brief  ���YUV�������ݣ���ɫ�ο�ITU-R BT.601��׼����8����ɫ
 *
 *
 */

#ifndef FILL_YUVDATA_H
#define FILL_YUVDATA_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * ���UYVY��ʽ���ݣ�����
 *
 * @param buffer: ���ݻ��������ɵ��������벢��֤��Ч
 * @param width : ͼ���
 * @param height: ͼ���
 */
void fill_yuv_uyvy_1(unsigned char* buffer, int width, int height);

/**
 * ���UYVY��ʽ���ݣ�����
 *
 * @param buffer: ���ݻ��������ɵ��������벢��֤��Ч
 * @param width : ͼ���
 * @param height: ͼ���
 */
void fill_yuv_uyvy_2(unsigned char* buffer, int width, int height);

/**
 * ���YUV422P��ʽ���ݣ�����
 *
 * @param buffer: ���ݻ��������ɵ��������벢��֤��Ч
 * @param width : ͼ���
 * @param height: ͼ���
 */
void fill_yuv_yuv422_1(unsigned char* buffer, int width, int height);

/**
 * ���YUV422P��ʽ���ݣ�����
 *
 * @param buffer: ���ݻ��������ɵ��������벢��֤��Ч
 * @param width : ͼ���
 * @param height: ͼ���
 */
void fill_yuv_yuv422_2(unsigned char* buffer, int width, int height);

/**
 * ���YUV420P��ʽ���ݣ�����
 *
 * @param buffer: ���ݻ��������ɵ��������벢��֤��Ч
 * @param width : ͼ���
 * @param height: ͼ���
 */
void fill_yuv_yuv420_1(unsigned char* buffer, int width, int height);

/**
 * ���YUV420P��ʽ���ݣ�����
 *
 * @param buffer: ���ݻ��������ɵ��������벢��֤��Ч
 * @param width : ͼ���
 * @param height: ͼ���
 */
void fill_yuv_yuv420_2(unsigned char* buffer, int width, int height);

#ifdef __cplusplus
}
#endif

#endif /* FILL_YUVDATA_H */

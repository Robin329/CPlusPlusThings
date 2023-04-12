#ifndef __BST_DISPLAY_DRIVER_H__
#define __BST_DISPLAY_DRIVER_H__
#ifdef __cplusplus
extern "C" {
#endif
#include <34.list.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/types.h>

#define MAX_DISPLAYS        5
#define DISPLAY_DEV_NAME    "/dev/display%d"
#define PIPELINE_MAX_LAYERS 4

#define EOK 0
#define ERR 1

typedef enum {
    CONN_VOUT,
    CONN_MIPI_DSI0,
    CONN_MIPI_DSI1,
    CONN_LVDS0,
    CONN_LVDS1,
    CONN_EDP,
    CONN_WRITEBACK0,
    CONN_WRITEBACK1,
    CONN_WRITEBACK2,
    CONN_WRITEBACK3,
    CONN_WRITEBACK4,
    CONN_MAX,
} conn_type_e;

typedef enum {
    BST_DISP0,
    BST_DISP1,
    BST_SINGLE_DISP,
    BST_DISP_MAX,
} disp_type_e;

typedef enum {
    DISP_PIPELINE0,
    DISP_PIPELINE1,
    DISP_PIPELINE2,
    DISP_PIPELINE3,
    DISP_PIPELINE4,
    DISP_PIPELINE_MAX,
} pipeline_type_e;

typedef enum {
    PLANE_RICH_TYPE0,
    PLANE_SIMPLE_TYPE1,
    PLANE_RICH_TYPE2,
    PLANE_SIMPLE_TYPE3,
    PLANE_TYPE_BOTH,
    PLANE_WB_TYPE,
    PLANE_TYPE_MAX,
} plane_type_e;

typedef enum {
    BST_FORMAT_NONE,
    BST_FORMAT_RGBA4444,
    BST_FORMAT_RGBX4444,
    BST_FORMAT_RGBA5551,
    BST_FORMAT_RGBX5551,
    BST_FORMAT_RGB565,
    BST_FORMAT_RGB888,
    BST_FORMAT_BGRA8888,
    BST_FORMAT_BGRX8888,
    BST_FORMAT_XBGR8888,
    BST_FORMAT_RGBA8888,
    BST_FORMAT_RGBX8888,
    BST_FORMAT_RGBA1010102,
    BST_FORMAT_ARGB2101010,
    BST_FORMAT_YUV422_YUYV_8B,
    BST_FORMAT_YUV422_YUYV_10B,
    BST_FORMAT_YUV422_UYVY,
    BST_FORMAT_YUV420_NV12,
    BST_FORMAT_YUV420_NV16,
    BST_FORMAT_MAX,
} video_format_e;

struct pipeline_t;
struct plane_t;
struct video_timing_t;

typedef struct dp_in_range_t {
    int32_t start;
    int32_t end;
} dp_in_range_t;

typedef struct plane_t {
    struct pipeline_t* pipeline;
    plane_type_e       type; /* RICH, SIMPLE or WB */
    struct list_head   plane_list;
    uint8_t            plane_id;
    uint8_t            active;
    uint8_t            zorder;
    dp_in_range_t      hsize_in, vsize_in;
    video_format_e     format;
    size_t             size;
    uintptr_t          addr;
} plane_t;

typedef struct video_timing_t {
    uint32_t hactive;
    uint32_t hblank;
    uint32_t hfront;
    uint32_t hsync;
    uint32_t hback;
    uint32_t vactive;
    uint32_t vblank;
    uint32_t vfront;
    uint32_t vsync;
    uint32_t vback;
    bool     hpol;
    bool     vpol;
    uint32_t pclk_KHz;
    uint32_t reserved[3];
} video_timing_t;

typedef struct pipeline_t {
    char             name[32];
    int32_t          fd;
    pipeline_type_e  type;
    struct list_head pipeline_list;
    uint32_t         id;
    plane_t          planes;
    pthread_cond_t   cond;
    uint8_t          active : 1;
} pipeline_t;

typedef struct conn_t {
    pipeline_t*      pipeline;
    video_timing_t   timing;
    struct list_head conn_list;
    uint8_t          id;
    uint8_t          active : 1;
} conn_t;

typedef struct bst_display_t {
    pipeline_t pipeline;
    conn_t     conn;
} bst_display_t;

#ifdef __cplusplus
}
#endif
#endif /* __BST_DISPLAY_DRIVER_H__ */
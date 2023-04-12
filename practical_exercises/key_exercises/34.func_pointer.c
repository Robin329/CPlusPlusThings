#include "34.func_pointer.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "34.list.h"

bst_display_t *g_display;

static int32_t __bst_plane_list_update(pipeline_t *pp, int i) {
    if (!pp) {
        printf("Error, pipe is NULL!");
        return -1;
    }
    bool     new_plane = true;
    plane_t *plane;
    if (bst_list_empty(&pp->planes.plane_list)) {
        printf("plane list is empty!\n");
        new_plane = true;
    } else {
        bst_list_for_each_entry(plane, &pp->planes.plane_list, plane_list) { printf("list plane->id:%d\n", i); }
    }
    printf("list plane->id:%d new_plane:%d\n", i, new_plane);
    if (new_plane) {
        plane = (plane_t *)malloc(sizeof(plane_t));
        if (!plane) {
            printf("Error, malloc plane_t failed");
            return -1;
        }
        memset(plane, 0, sizeof(plane_t));
    } else {
        printf("plane id = %d have exits!\n", plane->plane_id);
        return EOK;
    }
    static int zorder = 0;
    plane->active = 0;
    plane->plane_id = i;
    plane->type = 0xff;
    plane->zorder = zorder++;
    bst_list_add_tail(&plane->plane_list, &pp->planes.plane_list);
    return EOK;
}

static int32_t __bst_pipeline_list_update(int i) {
    pipeline_t *pipeline;
    bool        new_pipeline = true;
    if (bst_list_empty(&g_display->pipeline.pipeline_list)) {
        printf("pipeline list is empty!");
        new_pipeline = true;
    } else {
        bst_list_for_each_entry(pipeline, &g_display->pipeline.pipeline_list, pipeline_list) {
            printf("list pipeline->id:%d\n", pipeline->id);
        }
    }
    printf("pipeline->id:%d new_pipeline:%d\n", i, new_pipeline);
    if (new_pipeline) {
        pipeline = (pipeline_t *)malloc(sizeof(pipeline_t));
        if (!pipeline) {
            printf("Error, malloc pipeline_t failed\n");
            return -1;
        }
        memset(pipeline, 0, sizeof(pipeline_t));
    } else {
        printf("pipeline have exits!pipeline(%d)\n", pipeline->id);
        return EOK;
    }
    pipeline->id = (uint32_t)i;

    switch (pipeline->id) {
        case 1:
            pipeline->type = DISP_PIPELINE0;
            pipeline->fd = 5;
            break;
        case 2:
            pipeline->type = DISP_PIPELINE1;
            pipeline->fd = 6;
            break;
        case 3:
            pipeline->type = DISP_PIPELINE2;
            break;
        case 4:
            pipeline->type = DISP_PIPELINE3;
            break;
        case 5:
            pipeline->type = DISP_PIPELINE4;
            break;
        default:
            break;
    }
    INIT_LIST_HEAD(&pipeline->planes.plane_list);
    bst_list_add_tail(&pipeline->pipeline_list, &g_display->pipeline.pipeline_list);

    return EOK;
}

static int32_t __bst_conn_list_update(int i) {
    conn_t *cn;
    bool    new_conn = true;
    if (bst_list_empty(&g_display->conn.conn_list)) {
        printf("conn list is empty!\n");
        new_conn = true;
    } else {
        bst_list_for_each_entry(cn, &g_display->conn.conn_list, conn_list) {
            printf("list conn->id:%d\n", cn->id);
            if (cn->id == i) {
                printf("conn id have exits!\n");
                new_conn = false;
                break;
            }
        }
    }

    if (new_conn) {
        cn = (conn_t *)malloc(sizeof(conn_t));
        if (!cn) {
            printf("Error, malloc conn_t failed\n");
            return -1;
        }
        memset(cn, 0, sizeof(conn_t));
    } else {
        return EOK;
    }
    cn->id = i;
    printf("cn->id:%d\n", cn->id);
    bst_list_add_tail(&cn->conn_list, &g_display->conn.conn_list);
    return EOK;
}
static int32_t __bst_conn_list_free(conn_t *conn) {
    conn_t *cn;
    bst_list_for_each_entry(cn, &conn->conn_list, conn_list) {
        bst_list_del(&cn->conn_list);
        free(cn);
    }
    return EOK;
}

static int32_t __bst_pipeline_list_free(pipeline_t *pipeline) {
    pipeline_t *p;
    bst_list_for_each_entry(p, &pipeline->pipeline_list, pipeline_list) {
        bst_list_del(&p->pipeline_list);
        free(p);
    }
    return EOK;
}

static int32_t __bst_plane_list_free(plane_t *plane) {
    plane_t *p;
    bst_list_for_each_entry(p, &plane->plane_list, plane_list) {
        bst_list_del(&p->plane_list);
        free(p);
    }
    return EOK;
}

static int32_t bst_display_dump(void) {
    if (!g_display) {
        printf("g_display is NULL!\n");
        return -1;
    }
    bst_display_t *disp = g_display;
    int            npipeline = 0;
    int            nplane = 0;
    int            nconn = 0;
    conn_t *       cn;

    plane_t *   plane;
    pipeline_t *pipeline;
    printf("========pipeline========\n");
    bst_list_for_each_entry(pipeline, &disp->pipeline.pipeline_list, pipeline_list) {
        npipeline++;
        printf("pipeline[%d]:\n", pipeline->id);
        printf("	   type:%d\n", pipeline->type);
        printf("	   name:%s\n", pipeline->name);
        printf("	     fd:%d\n", pipeline->fd);
        printf("     active:%d\n", pipeline->active);
        nplane = 0;
        bst_list_for_each_entry(plane, &pipeline->planes.plane_list, plane_list) {
            nplane++;
            printf("         plane[%d]:\n", plane->plane_id);
            printf("            type:%d\n", plane->type);
            printf("          active:%d\n", plane->active);
            printf("          zorder:%d\n", plane->zorder);
            printf("        hsize_in:(%d, %d)\n", plane->hsize_in.start, plane->hsize_in.end);
            printf("        vsize_in:(%d, %d)\n", plane->vsize_in.start, plane->vsize_in.end);
            printf("          format:%d\n", plane->format);
            printf("            size:%zu\n", plane->size);
            printf("            addr:%#lx\n", plane->addr);
            printf("        ---------\n");
        }
        printf("            total %d plane\n", nplane);
    }
    printf("total pipeline:%d\n", npipeline);
    printf("=======connector========\n");
    bst_list_for_each_entry(cn, &disp->conn.conn_list, conn_list) {
        nconn++;
        printf("        conn[%d]:\n", cn->id);
        printf("              active:%d\n", cn->active);
        printf("        ---------------------\n");
        printf("        |      timing       |\n");
        printf("        ---------------------\n");
        printf("              hactive :%d\n", cn->timing.hactive);
        printf("              hblank  :%d\n", cn->timing.hblank);
        printf("              hsync   :%d\n", cn->timing.hsync);
        printf("              hback   :%d\n", cn->timing.hback);
        printf("              vactive :%d\n", cn->timing.vactive);
        printf("              vblank  :%d\n", cn->timing.vblank);
        printf("              vfront  :%d\n", cn->timing.vfront);
        printf("              vsync   :%d\n", cn->timing.vsync);
        printf("              vback   :%d\n", cn->timing.vback);
        printf("              hpol    :%d\n", cn->timing.hpol);
        printf("              vpol    :%d\n", cn->timing.vpol);
        printf("              pclk_KHz:%d\n", cn->timing.pclk_KHz);
    }
    printf("    total %d connector\n", nconn);
    return EOK;
}

int test(plane_t *plane) {
    printf("plane id:%d plane->pipeline fd:%d\n", plane->plane_id, plane->pipeline->fd);
    return EOK;
}

int main() {
    g_display = (bst_display_t *)malloc(sizeof(bst_display_t));
    if (!g_display) {
        printf("Display malloc failed!\n");
        return -1;
    }
    memset(g_display, 0, sizeof(bst_display_t));
    INIT_LIST_HEAD(&g_display->conn.conn_list);
    INIT_LIST_HEAD(&g_display->pipeline.planes.plane_list);
    INIT_LIST_HEAD(&g_display->pipeline.pipeline_list);

    __bst_conn_list_update(1);
    __bst_conn_list_update(2);

    __bst_pipeline_list_update(1);
    __bst_pipeline_list_update(2);
    pipeline_t *pipeline;
    plane_t *   plane;
    bst_list_for_each_entry(pipeline, &g_display->pipeline.pipeline_list, pipeline_list) {
        printf("list pipeline->id:%d\n", pipeline->id);
        if (pipeline->id == 1) {
            __bst_plane_list_update(pipeline, 1);
            __bst_plane_list_update(pipeline, 2);
            __bst_plane_list_update(pipeline, 3);
            __bst_plane_list_update(pipeline, 4);
        } else if (pipeline->id == 2) {
            __bst_plane_list_update(pipeline, 5);
            __bst_plane_list_update(pipeline, 6);
            __bst_plane_list_update(pipeline, 7);
            __bst_plane_list_update(pipeline, 8);
        }
    }
    bst_list_for_each_entry(pipeline, &g_display->pipeline.pipeline_list, pipeline_list) {
        printf("list pipeline->id:%d\n", pipeline->id);
        if (pipeline->id == 1) {
            bst_list_for_each_entry(plane, &pipeline->planes.plane_list, plane_list) {
                printf("list plane->id:%d\n", plane->plane_id);
                plane->pipeline = pipeline;
                break;
            }
            break;
        }
    }
    printf("plane id:%d pipeline id:%d\n", plane->plane_id, plane->pipeline->fd);
    test(plane);
    bst_display_dump();
    return 0;
}
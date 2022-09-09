#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "vic_timings.h"

enum MODE { MODE_UNKNOWN = 0, MODE_VIC = 1, MODE_DMT = 2 };

const char *program_name;

void help(const char *section, const char *opt) {
    int count = 0;
    if (section == NULL) {
        fprintf(stderr, "Usage: %s <command> [arguments]\n", program_name);
        fprintf(stderr, "  Commands: vic  <vic id>\n");
        fprintf(stderr, "  Commands: dmt  <dmt id>\n");
    } else if (strcmp(section, "vic") == 0) {
        fprintf(stderr, "Usage: %s vic <vic id>\n", program_name);
        fprintf(stderr, "  Print the CEA-861 mode information for a given VIC id\n");
        if (opt != NULL && (strcmp(opt, "list") == 0)) {
            for (count = 0; count < sizeof(edid_cea_modes); count++) {
                if (count > 0 && count <= 127) {
                    fprintf(stderr, "vic:%d - %s (%.2fHz)\n", count, edid_cea_modes[count].name,
                            (edid_cea_modes[count].clock * 1000.0) /
                                    (edid_cea_modes[count].htotal * edid_cea_modes[count].vtotal));
                }
            }
            for (count = 193; count < sizeof(edid_cea_modes_193) + 193; count++) {
                if (count >= 193 && count <= 219)
                    fprintf(stderr, "vic:%d - %s (%.2fHz)\n", count, edid_cea_modes_193[count - 193].name,
                            (edid_cea_modes_193[count - 193].clock * 1000.0) /
                                    (edid_cea_modes_193[count - 193].htotal * edid_cea_modes_193[count - 193].vtotal));
            }
        }
    } else if (strcmp(section, "dmt") == 0) {
        fprintf(stderr, "Usage: %s dmt <dmt id>\n", program_name);
        fprintf(stderr, "  Print the VESA DMT mode information for a given DMT id\n");
        if (opt != NULL && (strcmp(opt, "list") == 0)) {
            for (count = 0; count < sizeof(drm_dmt_modes); count++) {
                if (count > 0 && count <= 88) {
                    fprintf(stderr, "vic:%d - %s (%.2fHz)\n", count, drm_dmt_modes[count].name,
                            (drm_dmt_modes[count].clock * 1000.0) /
                                    (drm_dmt_modes[count].htotal * drm_dmt_modes[count].vtotal));
                }
            }
        }
    }
}
/*
 *               Active                 Front           Sync           Back
 *              Region                 Porch                          Porch
 *     <-----------------------><----------------><-------------><-------------->
 *       //////////////////////|
 *      ////////////////////// |
 *     //////////////////////  |..................               ................
 *                                                _______________
 *     <----- [hv]display ----->
 *     <------------- [hv]sync_start ------------>
 *     <--------------------- [hv]sync_end --------------------->
 *     <-------------------------------- [hv]total ----------------------------->*
 *
 * This structure contains two copies of timings. First are the plain timings,
 * which specify the logical mode, as it would be for a progressive 1:1 scanout
 * at the refresh rate userspace can observe through vblank timestamps. Then
 * there's the hardware timings, which are corrected for interlacing,
 * double-clocking and similar things. They are provided as a convenience, and
 * can be appropriately computed using drm_mode_set_crtcinfo().
 */
void print_display_mode(const struct drm_display_mode *dm) {
    float framerate = (dm->clock * 1000.0) / (dm->htotal * dm->vtotal);
    if (dm->flags & DRM_MODE_FLAG_DBLCLK) {
        printf("  Pixel Clock: %d.%d MHz\n", dm->clock / 1000, dm->clock % 1000);
        printf("   Frame Rate: %f Hz\n", framerate);
    } else {
        printf("  Pixel Clock: %d.%d MHz (*2 = %d.%d MHz)\n", dm->clock / 1000, dm->clock % 1000, dm->clock * 2 / 1000,
               dm->clock * 2 % 1000);
        printf("   Frame Rate: %f Hz (*2 = %f Hz)\n", framerate, framerate * 2.0);
    }
    printf("Htotal x Vtotal: %d - %#x\n", dm->htotal * dm->vtotal, dm->htotal * dm->vtotal);
    printf("     H Active: %d - %#x\n", dm->hdisplay, dm->hdisplay);
    printf("H Front Porch: %d - %#x\n", dm->hsync_start - dm->hdisplay, dm->hsync_start - dm->hdisplay);
    printf("       H Sync: %d - %#x\n", dm->hsync_end - dm->hsync_start, dm->hsync_end - dm->hsync_start);
    printf(" H Back Porch: %d - %#x\n", dm->htotal - dm->hsync_end, dm->htotal - dm->hsync_end);
    printf("      H Total: %d - %#x\n", dm->htotal, dm->htotal);
    printf("     V Active: %d - %#x\n", dm->vdisplay, dm->vdisplay);
    printf("V Front Porch: %d - %#x\n", dm->vsync_start - dm->vdisplay, dm->vsync_start - dm->vdisplay);
    printf("       V Sync: %d - %#x\n", dm->vsync_end - dm->vsync_start, dm->vsync_end - dm->vsync_start);
    printf(" V Back Porch: %d - %#x\n", dm->vtotal - dm->vsync_end, dm->vtotal - dm->vsync_end);
    printf("      V Total: %d - %#x\n", dm->vtotal, dm->vtotal);
    printf("        Flags:%s%s%s%s%s%s\n", dm->flags & DRM_MODE_FLAG_PHSYNC ? " +hsync" : " -hsync",
           dm->flags & DRM_MODE_FLAG_PVSYNC ? " +vsync" : " -vsync",
           dm->flags & DRM_MODE_FLAG_INTERLACE ? " +interlace" : "",
           dm->flags & DRM_MODE_FLAG_DBLSCAN ? " +dblscan" : "", dm->flags & DRM_MODE_FLAG_DBLCLK ? " +dblclk" : "",
           dm->flags & DRM_MODE_FLAG_CSYNC ? (dm->flags & DRM_MODE_FLAG_PCSYNC ? " +pcsync" : " -pcsync") : "");
    printf("Active Pixels: %d\n", dm->hdisplay * dm->vdisplay);
    printf(" Total Pixels: %d\n", dm->htotal * dm->vtotal);
    printf(" 12bpp Bitclk: %d MHz\n", dm->htotal * dm->vtotal * 12 * 8 / 1000);
    printf(" 18bpp Bitclk: %d MHz\n", dm->htotal * dm->vtotal * 18 * 8 / 1000);
    printf(" 24bpp Bitclk: %d MHz\n", dm->htotal * dm->vtotal * 24 * 8 / 1000);
    printf("   8b10b Rate: %d.%d MHz (/25 = %d.%d MHz)\n", (dm->clock * 10) / 1000, (dm->clock * 10) % 1000,
           (dm->clock * 10 / 25) / 1000, (dm->clock * 10 / 25) % 1000);
}

int convert_number(const char *arg) {
    char *endptr = NULL;
    if (strlen(arg) > 2 && arg[0] == '0' && (arg[1] == 'x' || arg[1] == 'X')) {
        return (int)strtol(arg + 2, &endptr, 16);
    }
    return (int)strtol(arg, &endptr, 10);
}

int command_dmt(int argc, char **argv) {
    if (argc != 1) {
        help("dmt", NULL);
        return 1;
    }
    int dmtid = convert_number(argv[0]);

    const struct drm_display_mode *dm = NULL;
    if (dmtid > 0 && dmtid <= 88) {
        dm = drm_dmt_modes + dmtid;
    } else {
        printf("DMT ID out of range (1-88)\n");
        return 1;
    }

    print_display_mode(dm);
}
int command_vic(int argc, char **argv) {
    if (argc != 1) {
        help("vic", NULL);
        return 1;
    }
    int vic = convert_number(argv[0]);

    const struct drm_display_mode *dm = NULL;
    if (vic > 0 && vic <= 127) {
        dm = edid_cea_modes + vic;
    } else if (vic >= 193 && vic <= 219) {
        dm = edid_cea_modes_193 + (vic - 193);
    } else {
        fprintf(stderr, "VIC ID out of range (1-127, 193-219)\n");
        return 1;
    }

    print_display_mode(dm);

    return 0;
}

int main(int argc, char **argv) {
    int opt, vic;
    enum MODE mode = MODE_UNKNOWN;
    program_name = argv[0];

    if (argc <= 1) {
        help(NULL, NULL);
        return 1;
    }
    if (strcmp(argv[2], "list") != 0) {
        if (strcmp(argv[1], "vic") == 0) {
            mode = MODE_VIC;
        } else if (strcmp(argv[1], "dmt") == 0) {
            mode = MODE_DMT;
        }
    }

    switch (mode) {
        case MODE_VIC:
            return command_vic(argc - 2, argv + 2);

        case MODE_DMT:
            return command_dmt(argc - 2, argv + 2);

        default:
            help(argv[1], argv[2]);
    }
    return 1;
}
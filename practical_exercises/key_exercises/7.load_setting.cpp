//
// Created by renbin jiang on 2021/12/4.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <iostream>

#include "382_reg.h"
using namespace std;
const ichipsReg ichips788Reg[] = {
        {"B0_C788_CLKCTRL", 0x000801, 0, "", 0},
        {"B0_C788_CMOSOUTSETUP   ", 0x000901, 0, "", 0},
        {"B0_C788_POCLKCT", 0x000A01, 0, "", 0},
        {"B0_C788_POPLLCT", 0x000B01, 0, "", 0},
        {"B0_C788_POREFDIV   ", 0x000C01, 0, "", 0},
        {"B1_C788_OSDACTHST  ", 0x010E02, 0, "", 0},
        {"B1_C788_OSDACTHW   ", 0x011002, 0, "", 0},
        {"B1_C788_OSDACTVST  ", 0x011202, 0, "", 0},
        {"B1_C788_OSDACTVW   ", 0x011402, 0, "", 0},
        {"B8_C788_CURBIASR   ", 0x082301, 0, "", 0},
        {"B8_C788_CURBIASG   ", 0x082401, 0, "", 0},
        {"B8_C788_CURBIASB   ", 0x082501, 0, "", 0},
        {"B8_C788_CURPLTDTR0 ", 0x082601, 0, "", 0},
        {"B8_C788_CURPLTDTR1 ", 0x082701, 0, "", 0},
        {"B8_C788_CURPLTDTR2 ", 0x082801, 0, "", 0},
        {"B8_C788_CURPLTDTR3 ", 0x082901, 0, "", 0},
};
void save_setting_c788(const char *fname) {
    FILE *fp = nullptr;
    time_t t;
    struct tm *p;
    time(&t);
    p = localtime(&t); //取得当地时间
    fp = fopen(fname, "w+");
    if (fp == nullptr) {
        printf("File open error.");
        return;
    }
    // comment
    fprintf(fp, "; REGISTER DUMP FILE time:%02d:%02d:%02d\tdate:%d/%02d/%02d\n",
            (1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    fprintf(fp,
            "MCLK_FREQ\t32000000\n"
            "PO1CLK_FREQ\t27000000\n"
            "Sleep 12\r\n\n");
    char *pch;
    char *pSaveStr;
    char bank[8] = {0};
    char ichips[10] = "C788";
    for (int i = 0; i < sizeof(ichips788Reg) / sizeof(ichipsReg); i++) {
        int len = strlen(ichips788Reg[i].regName);
        char splitStr[len + 1];
        memset(splitStr, 0, len + 1);
        memcpy(splitStr, ichips788Reg[i].regName, len);
        pch = strtok_r(splitStr, "_", &pSaveStr);
        cout << "pch = " << pch << endl;
        if (strncmp(bank, pch, strlen(pch))) {
            fprintf(fp, "\n; %s%s registers\n", ichips, pch);
            memcpy(bank, pch, strlen(pch));
        }
        while (pch != NULL) {
            pch = strtok_r(NULL, "_", &pSaveStr);
            cout << __LINE__ << "pch = " << pch << endl;
            fprintf(fp, "%s%s\t%s\t%xh", ichips, bank, pSaveStr, ichips788Reg[i].addr);
            break;
        }
        if (strcmp(ichips788Reg[i].regFunc, "")) {
            fprintf(fp, "\t;;%s\n", ichips788Reg[i].regFunc);
        } else {
            fprintf(fp, "\n");
        }
        if (0 != ichips788Reg[i].isSleep) {
            fprintf(fp, "Sleep %d\n\n", ichips788Reg[i].isSleep);
        }
    }
    fclose(fp);
}

void save_setting_c382(const char *fname) {
    FILE *fp = nullptr;
    time_t t;
    struct tm *p;
    time(&t);
    p = localtime(&t); //取得当地时间
    fp = fopen(fname, "w+");
    if (fp == nullptr) {
        printf("File open error.");
        return;
    }
    // comment
    fprintf(fp, "; REGISTER DUMP FILE time:%02d:%02d:%02d\tdate:%d/%02d/%02d\n",
            (1900 + p->tm_year), (1 + p->tm_mon), p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);
    fprintf(fp,
            "MCLK_FREQ\t32000000\n"
            "PO1CLK_FREQ\t27000000\n"
            "Sleep 12\r\n\n");
    char *pch;
    char *pSaveStr;
    char *save;
    char bank[8] = {0};
    char ichips[10] = "C382";
    int index = 0;
    for (int i = 0; i < sizeof(ichips382Reg) / sizeof(ichipsReg); i++) {
        int len = strlen(ichips382Reg[i].regName);
        char splitStr[len + 1];
        memset(splitStr, 0, len + 1);
        memcpy(splitStr, ichips382Reg[i].regName, len);
        pch = strtok_r(splitStr, "_", &pSaveStr);
        cout << "pch = " << pch << endl;
        if (strncmp(bank, pch, strlen(pch))) {
            fprintf(fp, "\n; %s%s registers\n", ichips, pch);
            memcpy(bank, pch, strlen(pch));
        }
        while (pch != NULL) {
            pch = strtok_r(NULL, "_", &pSaveStr);
            cout << __LINE__ << "pch = " << pch << endl;
            fprintf(fp, "%s%s\t%s\t%xh", ichips, bank, pSaveStr, ichips382Reg[i].addr);
            break;
        }
        if (strcmp(ichips382Reg[i].regFunc, "")) {
            fprintf(fp, "\t;;%s\n", ichips382Reg[i].regFunc);
        } else {
            fprintf(fp, "\n");
        }
        if (0 != ichips382Reg[i].isSleep) {
            fprintf(fp, "Sleep %d\n\n", ichips382Reg[i].isSleep);
        }
    }
    fclose(fp);
}
int main() {
    const char *fname_c382 = "dump_file_c382.txt";
    const char *fname_c788 = "dump_file_c788.txt";
    save_setting_c382(fname_c382);
    save_setting_c788(fname_c788);
}
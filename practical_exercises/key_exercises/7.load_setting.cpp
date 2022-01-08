//
// Created by renbin jiang on 2021/12/4.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <vector>

#include "382_reg.h"
using namespace std;
const ichipsReg ichips788Reg[] = {
        {"B0_C788_CLKCTRL", 0x000801, 0, "", 0},    {"B0_C788_CMOSOUTSETUP", 0x000901, 0, "", 0},
        {"B0_C788_POCLKCT", 0x000A01, 0, "", 0},    {"B0_C788_POPLLCT", 0x000B01, 0, "", 0},
        {"B0_C788_POREFDIV", 0x000C01, 0, "", 0},   {"B1_C788_OSDACTHST", 0x010E02, 0, "", 0},
        {"B1_C788_OSDACTHW", 0x011002, 0, "", 0},   {"B1_C788_OSDACTVST", 0x011202, 0, "", 0},
        {"B1_C788_OSDACTVW", 0x011402, 0, "", 0},   {"B8_C788_CURBIASR", 0x082301, 0, "", 0},
        {"B8_C788_CURBIASG", 0x082401, 0, "", 0},   {"B8_C788_CURBIASB", 0x082501, 0, "", 0},
        {"B8_C788_CURPLTDTR0", 0x082601, 0, "", 0}, {"B8_C788_CURPLTDTR1", 0x082701, 0, "", 0},
        {"B8_C788_CURPLTDTR2", 0x082801, 0, "", 0}, {"B8_C788_CURPLTDTR3", 0x082901, 0, "", 0},
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
            "Sleep\t12\r\n\n");
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
        if (strncmp(bank, pch, strlen(pch))) {
            fprintf(fp, "\n; %s%s registers\n", ichips, pch);
            memcpy(bank, pch, strlen(pch));
        }
        while (pch != NULL) {
            pch = strtok_r(NULL, "_", &pSaveStr);
            fprintf(fp, "%s%s\t%s\t%xh", ichips, bank, pSaveStr, ichips788Reg[i].addr);
            break;
        }
        if (strcmp(ichips788Reg[i].regFunc, "")) {
            fprintf(fp, "\t;;%s\n", ichips788Reg[i].regFunc);
        } else {
            fprintf(fp, "\n");
        }
        if (0 != ichips788Reg[i].isSleep) {
            fprintf(fp, "Sleep\t%d\n\n", ichips788Reg[i].isSleep);
        }
    }
    fclose(fp);
}

std::vector<std::string> split(const std::string &in, const std::string &delim) {
    std::vector<std::string> ret;
    try {
        std::regex re{delim};
        return std::vector<std::string>{std::sregex_token_iterator(in.begin(), in.end(), re, -1),
                                        std::sregex_token_iterator()};
    } catch (const std::exception &e) {
        std::cout << "error:" << e.what() << std::endl;
    }

    return ret;
}

void save_setting_c382_cpp(const char *fname) {
    std::ofstream outFile;
    char ichips[] = "C382";
    time_t t;
    struct tm *p;
    time(&t);
    p = localtime(&t); //取得当地时间
    outFile.open(fname, ios::out | ios::trunc);
    outFile << "; REGISTER DUMP FILE time:" << setw(2) << (1900 + p->tm_year) << ":" << setw(2)
            << (1 + p->tm_mon) << ":" << setw(2) << p->tm_mday << "\tdate::" << p->tm_hour
            << setw(2) << p->tm_min << ":" << setw(2) << p->tm_sec << ":" << std::endl;
    outFile << "MCLK_FREQ\t32000000\n"
               "PO1CLK_FREQ\t27000000\n"
               "Sleep\t12\r\n\n";
    std::vector<ichipsReg> lines;
    int len = sizeof(ichips382Reg) / sizeof(ichipsReg);
    for (int i = 0; i < len; i++) {
        lines.push_back(ichips382Reg[i]);
    }
    for (int i = 0; i < len; i++) {
        std::vector<std::string> fieldsPre = split(lines.at(i).regName, "_");
        std::vector<std::string> fieldsPost =
                split(lines.at((i < (len - 1)) ? (i + 1) : i).regName, "_");
        if (i == 0) {
            outFile << "\n;\t" << ichips << fieldsPre.at(0) << "\tregisters\n";
        }
        outFile << ichips << fieldsPre.at(0) << "\t" << fieldsPre.at(2) << "\t" << lines.at(i).addr
                << "h"; // lines.at(i).addr --> read reg value
        if (std::string(lines.at(i).regFunc).compare("") != 0) {
            outFile << " ;; " << lines.at(i).regFunc << "\n";
        } else {
            outFile << "\n";
        }
        if (lines.at(i).isSleep != 0) {
            outFile << "Sleep " << lines.at(i).isSleep << "\n\n";
        }
        if (fieldsPre.at(0) != fieldsPost.at(0)) {
            //            cout << "fieldsPost=" << fieldsPost.at(0) << endl;
            outFile << "\n;\t" << ichips << fieldsPost.at(0) << "\tregisters\n";
        }
    }
    outFile.close();
}

void load_setting_c382_cpp(const char *fname) {
    std::ifstream inFile;
    char ichips[] = "C382";
    inFile.open(fname);
    if (!inFile.is_open()) {
        std::cout << "open " << fname << " failed!" << std::endl;
        return;
    }
    std::string line;
    int idx_line = 0;
    while (std::getline(inFile, line)) {
        idx_line++;
        if (idx_line < 5) continue;
        if (!line.compare("\n") || !line.compare("")) continue;

        if (!line.find(';')) continue;
        if (!line.find("Sleep", 0)) {
            cout << "need sleep " << split(line, " ").at(1) << "ms" << endl;
            continue;
        }

        std::vector<std::string> fields = split(line, "\t");
        //        cout << "fields0=" << fields.at(0) << " field1=" << fields.at(1) << endl;
        string name(fields.at(0).erase(0, 4) + "_" + ichips + "_" + fields.at(1));
        int len = sizeof(ichips382Reg) / sizeof(ichipsReg);
        for (int i = 0; i < len; i++) {
            if (!name.compare(ichips382Reg[i].regName)) {
                cout << " name : " << ichips382Reg[i].regName << " addr: " << std::hex
                     << ichips382Reg[i].addr << " value : " << ichips382Reg[i].value << endl;
            }
        }
    }

    inFile.close();
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
            "Sleep\t12\r\n\n");
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
        //        cout << "pch = " << pch << endl;
        if (strncmp(bank, pch, strlen(pch))) {
            pch = strtok_r(NULL, "_", &pSaveStr);
            fprintf(fp, "\n;\t%s%s\tregisters\n", ichips, pch);
            memset(bank, 0, sizeof(bank));
            memcpy(bank, pch, strlen(pch));
        }
        while (pch != NULL) {
            fprintf(fp, "%s%s\t%s\t%xh", ichips, bank, pSaveStr,
                    ichips382Reg[i].addr); // ichips382Reg[i].addr --> read reg value
            break;
        }
        if (strcmp(ichips382Reg[i].regFunc, "")) {
            fprintf(fp, "\t;;%s\n", ichips382Reg[i].regFunc);
        } else {
            fprintf(fp, "\n");
        }
        if (0 != ichips382Reg[i].isSleep) {
            fprintf(fp, "Sleep\t%d\n\n", ichips382Reg[i].isSleep);
        }
    }
    fclose(fp);
}

void load_setting_c788(const char *fname) {
    FILE *fp = nullptr;
    time_t t;
    char buf[256] = {0};
    const char dlm_cmt[] = ";";
    const char dlm_enter[] = "\t";
    struct tm *p;
    char *token;
    char *ctx;
    char ichips[10] = "C788";
    int index = 0;
    int reg_value = 0;
    char reg_name[16] = {};
    char bank[8] = {};
    char reg[64] = {};
    time(&t);
    p = localtime(&t); //取得当地时间
    fp = fopen(fname, "r");
    if (fp == nullptr) {
        printf("File open error.");
        return;
    }
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        if (strstr(buf, "MCLK_FREQ") || strstr(buf, "PO1CLK_FREQ")) continue;
        if (strstr(buf, dlm_cmt)) continue;
        if (strspn(buf, "\t\n") == strlen(buf)) continue;
        if ((token = strtok_r(buf, dlm_enter, &ctx)) != nullptr) {
            if (!strcmp(token, "Sleep")) {
                continue;
            }
            while (token != nullptr) {
                if (index == 0) memcpy(bank, token, strlen(token));
                token = strtok_r(nullptr, dlm_enter, &ctx);
                if (index == 0) memcpy(reg_name, token, strlen(token));
                if (index == 1) {
                    sscanf(token, "%xh", &reg_value);
                    index = 0;
                    snprintf(reg, sizeof(reg), "%s_%s_%s", bank + 4, ichips, reg_name);
                    memset(bank, 0, sizeof bank);
                    memset(reg_name, 0, sizeof reg_name);

                    break;
                }
                index++;
            }
            for (int i = 0; i < sizeof(ichips788Reg) / sizeof(ichipsReg); i++) {
                if (strncmp(reg, ichips788Reg[i].regName, strlen(reg)) == 0) {
                    printf("write addr --> %x reg value:%x\n", ichips788Reg[i].addr, reg_value);
                    break;
                }
            }
        }
    }
    fclose(fp);
}

void load_setting_c382(const char *fname) {
    FILE *fp = nullptr;
    time_t t;
    char buf[256] = {0};
    const char dlm_cmt[] = ";";
    const char dlm_enter[] = "\t";
    struct tm *p;
    char *token;
    char *ctx;
    char ichips[10] = "C382";
    int index = 0;
    int reg_value = 0;
    char reg_name[16] = {};
    char bank[8] = {};
    char reg[64] = {};
    time(&t);
    p = localtime(&t); //取得当地时间
    fp = fopen(fname, "r");
    if (fp == nullptr) {
        printf("File open error.");
        return;
    }
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        if (strstr(buf, "MCLK_FREQ") || strstr(buf, "PO1CLK_FREQ")) continue;
        if (strstr(buf, dlm_cmt)) continue;
        if (strspn(buf, "\t\n") == strlen(buf)) continue;
        if ((token = strtok_r(buf, dlm_enter, &ctx)) != nullptr) {
            if (!strcmp(token, "Sleep")) {
                continue;
            }
            while (token != nullptr) {
                if (index == 0) memcpy(bank, token, strlen(token));
                token = strtok_r(nullptr, dlm_enter, &ctx);
                if (index == 0) memcpy(reg_name, token, strlen(token));
                if (index == 1) {
                    sscanf(token, "%xh", &reg_value);
                    index = 0;
                    snprintf(reg, sizeof(reg), "%s_%s_%s", bank + 4, ichips, reg_name);
                    memset(bank, 0, sizeof bank);
                    memset(reg_name, 0, sizeof reg_name);
                    break;
                }
                index++;
            }
            for (int i = 0; i < sizeof(ichips382Reg) / sizeof(ichipsReg); i++) {
                if (strncmp(reg, ichips382Reg[i].regName, strlen(reg)) == 0) {
                    printf("write addr --> %x reg value:%x\n", ichips382Reg[i].addr, reg_value);
                    break;
                }
            }
        }
    }
    fclose(fp);
}
int main() {
    const char *fname_c382 = "dump_file_c382_cpp.txt";
    const char *fname_c788 = "dump_file_c788.txt";
    load_setting_c382_cpp(fname_c382);
    save_setting_c382_cpp(fname_c382);
    //    save_setting_c788(fname_c788);

    //    load_setting_c788(fname_c788);
    //    load_setting_c382(fname_c382);
}
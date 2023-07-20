#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <cstdint>

typedef struct {
    uint32_t magic;
    uint32_t type;
} status_1;

typedef struct {
    uint32_t os_magic;
    uint32_t arg2;
    uint32_t arg3;
} status_2;

struct data {
    int a;
    int b;
};
struct data g_data = {.a = 1, .b = 2};
typedef void (*callback_one)(status_1 status, void *ext);
typedef void (*callback_two)(status_2 status, void *ext);

static callback_two cb[10];

void my_callback(status_2 st, void *ext) {
    uint32_t d = *(uint32_t *)ext;
    printf("d:%d\n", d);
    printf("os_magic:%d arg2:%d arg3:%d\n", st.os_magic, st.arg2, st.arg3);
}

void func(void *ext) {
    uint32_t b = *(uint32_t *)ext;
    printf("--->>%d, b:%d\n", *(uint32_t *)ext, b);
}

void funcx(uint32_t tmp) {
        status_2 status1 = {
            .os_magic = 1523,
            .arg2 = 14,
            .arg3 = 22,
    };
    cb[0](status1, &tmp);
}


int main() {
    uint32_t a = 5;
    cb[0] = my_callback;
    cb[1] = my_callback;
    cb[2] = my_callback;
    cb[3] = my_callback;

    funcx(a);
    status_2 status2 = {
            .os_magic = 1423,
            .arg2 = 31,
            .arg3 = 52,
    };
    cb[1](status2, &g_data);

    status_2 status3 = {
            .os_magic = 1323,
            .arg2 = 11,
            .arg3 = 62,
    };
    cb[2](status3, &g_data);

    status_2 status4 = {
            .os_magic = 1223,
            .arg2 = 61,
            .arg3 = 12,
    };
    cb[3](status4, &g_data);
    func(&a);
    return 0;
}
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

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

void my_callback(status_2 st, void *ext) {
    struct data *d = (struct data *)ext;
    printf("a:%d b:%d\n", d->a, d->b);
    printf("os_magic:%d arg2:%d arg3:%d\n", st.os_magic, st.arg2, st.arg3);
}

static callback_two cb[10];

int main() {
    cb[0] = my_callback;
    cb[1] = my_callback;
    cb[2] = my_callback;
    cb[3] = my_callback;
    status_2 status1 = {
            .os_magic = 1523,
            .arg2 = 14,
            .arg3 = 22,
    };
    cb[0](status1, &g_data);

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
    return 0;
}
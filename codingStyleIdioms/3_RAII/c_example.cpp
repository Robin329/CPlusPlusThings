//
// Created by light on 19-12-12.
//

#include <stdio.h>
#include <string.h>

#include <memory>
int main() {
    char *str = (char *)malloc(7);
    strcpy(str, "toptal");
    printf("char array = \"%s\" @ 0x%s\n", str, str);

    str = (char *)realloc(str, 11);
    strcat(str, ".com");
    printf("char array = \"%s\" @ 0x%s\n", str, str);

    free(str);

    const char *s = nullptr;
    int a = 255;
    s = (const char *)&a;
    printf("s:%d\n", *s);

    return (0);
}
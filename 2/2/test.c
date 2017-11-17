#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int cpy(char *a, char *b, int size) { // ebp+0x8, ebp+0xc, ebp+0x10
    int i; // ebp-0x4
    char *dst = a; // ebp-0x8
    char *src = b; // ebp-0xc

    if(size == 0)
        return 0;

    for(i=0; i<size; i++) {
        dst[i] = src[i];
    }

    return size;
}

void *align(char *buf) { // ebp+0x8
    int mask = 0xfff; // ebp-0x4
    return (void *)(buf+mask) & (~mask);
}

void parse(char *src, int size) { // ebp+0x8, ebp+0xc
    char buf[0x1000]; // 4096
    cpy(buf, src, size);
}

int main() {
    int i = 0; // ebp-0x4
    int page_size = sysconf(0x1e); // ebp-0x8
    void *aligned = 0; // ebp-0xc
    void *buf = malloc(page_size + 0x2000); // ebp-0x10
    char ch; // ebp-0x14

    if(!d)
        return -1;

    aligned = align(buf);
    for(; i<=0x1fff; i++) { // 8192
        ch = getc(stdin);
        aligned[i] = ch;
    }

    if(aligned[0] == 'B')
        dummy(aligned);
    else
        parse(aligned, 0x2000);

    free(buf);
    return 0;
}

#include <stdio.h>

void readflag(int clifd) {
    // canary // rbp-0x08
    char buf[0x48]; // rbp-0x50
    FILE *fd = fopen("/home/canary/flag", "r"); // rbp-0x58
    // clifd // rbp-0x64

    fread(buf, 33, 1, fd);
    fclose(fd);

    send(clifd, buf, 33, 0);
}

void child(int fd) {
    // canary // -0x08
    char buf[0x88]; // -0x90
    int byte = 0; // -0x94
    int sent = 0; // -0x98
    // fd // -0xa4

    alarm(1);
    if((byte = recv(fd, buf, sysconf(0x1e), 0)) < 0) {
        // failure msg
        exit(1);
    }
    if((sent = send(fd, buf, byte, 0)) < 0) {
        // failure msg
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    // canary // -0x08
    short rbp0x2c; // -0x2c
    short rbp0x2e; // -0x2e
    short rbp0x30; // -0x30
    int rbp0x40; // -0x40
    int rbp0x44; // -0x44
    int rbp0x4c; // -0x4c
    // argc // -0x54
    // argv // -0x60
    if(argc <= 1) {
        // print error msg
        exit(1);
    }

    rbp0x44 = atoi(argv[1]);
    rbp0x4c = 1;
    if((rbp0x40 = socket(2, 1, 0)) == -1) {
        // error msg
        exit(1);
    }

    rbp0x30 = 2;
    rbp0x2e = htons(rbp0x44);
    rpb0x2c = htonl(0);
    setsockopt(....);
    
    return 0;
}

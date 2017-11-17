#include <stdio.h>
#include <stdlib.h>

typedef (void (*)(long, long, long)) myfunc

struct entry {
    char name[8];
    myfunc fn;
} *db[8];

getInt() {
}

getLong() {
}

getString() {
}

getAddr() {
    //strtoul(buf);
}

mainMenu() {
}

listFunctions() {
}

void printer(long a, long b, unsigned long *c) {
    printf("==> %lu, %lu, %08x\n", a, b, *c);
}

void registerFunction() {
    for(int i=0; i<8; i++) {
        if(db[i]) continue;

        if(!(db[i] = calloc(1, 12))) {
            printf("Enter the function name: ");
            getString(db[i].name, 8);

            printf("Enter the address (in hex): ");
            unsigned long addr = getAddr();
            db[i].fn = addr? addr: printer;
        }
    }
}

deleteFunction() {
}

void callFunction() {
    long p1; // 0xc
    long p2; // 0x10
    long p3; // 0x14
    int i; // 0x18
    unsigned long addr; // 0x1c

    printf("Enter the function number to call: ");
    i = getInt();
    printf("Enter the first argument: ");
    p1 = getLong();
    printf("Enter the second argument: ");
    p2 = getLong();
    printf("Enter the third argument: ");
    p3 = getAddr();

    // abort: ebx-0x4
    // ftruncate: ebx-0x18
    // printer: ebx-0x255b
    if(i <= 0 || i > 8)
        abort();
    
    addr = db[i-1].fn;
    if(addr > ftruncate || addr <= abort)
        if(addr != printer)
            return;

    db[i-1].fn(p1, p2, p3);
}

void whatisthis() {
    if(ptrace(0, 1, 0, 0) < 0)
        exit(-1);
}

int main() {
    unsigned int i;
    whatisthis();
    setbuf(stdout, NULL);
    puts("Welcome!");
    while(1) {
        i = mainMenu();
        if(i > 5) continue;

        switch(i) {
        case 1:
            listFunctions(); break;
        case 2:
            registerFunction(); break;
        case 3:
            deleteFunction(); break;
        case 4:
            callFunction(); break;
        case 5:
            return 0; break;
        }
    }
    return 0;
}

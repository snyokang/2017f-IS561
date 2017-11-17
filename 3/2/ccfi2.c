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
    if(addr > ftruncate || addr <= abort || addr == system || addr == execve)
        if(addr != printer)
            return;

    db[i-1].fn(p1, p2, p3);
}

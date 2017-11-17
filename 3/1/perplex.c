#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int go;
int alien_cnt;
unsigned long long int *age;
struct alien *aliens[10];

struct alien {
    int x;
    void *func;
};

void oops() { go = 1; }

void whatisthis() { __asm__("int3"); if(go == 0) exit(-1); }

void showflag(int x) { /*fopen, fgets, fclose, printf (/home/perplex/flag)*/ }

void sleep(int x) { printf("Alien (%d) is sleeping!\n", x); }

struct alien *create_alien() {
    struct alien *new;
    if((new = malloc(8)) == 0)
        return 0;
    new->x = alien_cnt++;
    new->func = sleep;
    printf("(%p) an alien (%d) added!\n", new, new->x);
    return new;
}

void delete_alien(struct alien *a) { printf("(%p) deleting alien %d\n", a, a->x); free(a); }

void show() {
    // prints aliens
}

void add() {
    for(int i=0; i<10; i++) {
        if(!aliens[i]) {
            aliens[i] = create_alien();
            printf("added.. %d\n", i);
            return;
        }
    }
}

void read_int() {
    char buf[8];
    return atoi(fgets(buf, 7, stdin));
    // canary check
}

void del() {
    int x = 0;
    puts("Enter an alien ID:");
    x = read_int();
    for(int i=0; i<10; i++) {
        if(aliens[i]) {
            if(aliens[i].x == x) {
                delete_alien(aliens[i]);
                return;
            }
        }
    }
}

void observe() {
    int x = 0;
    puts("Enter an alien ID:");
    x = read_int();
    for(int i=0; i<10; i++) {
        if(!aliens[i]) {
            if(x == aliens[i].x) {
                printf("observing.. %p\n", aliens[i].x);
                aliens[i].func(i);
            }
        }
    }
}

void setage() {
    char buf[0x80];
    if(age) free(age); // 56558088
    age = malloc(8);
    printf("(%p) Setting planet age: \n", age);
    fgets(buf, 0x7f, stdin);
    *age = strtoq(buf, 0, 10);
}

void showage() {
    printf("Your planet's age: %llu\n", age?*age:0);
}

void perplexed() {
    // puts menu
    whatisthis();
    switch(atoi(...)) {
        ...
    }
    perplexed();
    // canary check
}

int main() {
    ssignal(5, oops);
    setbuf(stdout, NULL);
    whatisthis();
    // puts IS561
    perplexed();
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 16

typedef enum msg_type {
  GET_DATA = 1,
  SET_DATA = 2,
  CHK_ALIVE = 3,
  EXIT = 4
} msg_type;

int data[BUFSIZE] = {0,}; // global data buffer

void __attribute__((noinline)) get_data()
{
  fwrite(data, BUFSIZE, 1, stdout);
}

void __attribute__((noinline)) set_data()
{
  char buf[sizeof(int) * BUFSIZE];
  int data_len = 0;
  fread(&data_len, sizeof(data_len), 1, stdin);
  if(data_len == 0) return;
  if(data_len > BUFSIZE) return;
  fread(buf, data_len * sizeof(int), 1, stdin); // integer, buffer overflow
  memcpy(data, buf, BUFSIZE * sizeof(int));
}

void __attribute__((noinline)) chk_alive()
{
  unsigned int len = 0;
  char token[32];
  fread(&len, sizeof(len), 1, stdin);
  if(len == 0) return;
  fgets(token, sizeof(token)-1, stdin);
  fwrite(token, len, 1, stdout); // Over read
}

msg_type __attribute__((noinline)) get_msg_type()
{
  msg_type t = EXIT;
  fread(&t, sizeof(msg_type), 1, stdin);
  return t;
}

void process()
{
  switch(get_msg_type()){
  case GET_DATA: get_data(); break;
  case SET_DATA: set_data(); break;
  case CHK_ALIVE: chk_alive(); break;
  case EXIT: return;
  }
  return process();
}

int main(void)
{
  setbuf(stdout, NULL);
  printf("\033[2J\033[1;1H"); // clear screen
  puts(" ___ ____       ____   __   _    ____ _____ _____");
  puts("|_ _/ ___|     | ___| / /_ / |  / ___|_   _|  ___|");
  puts(" | |\\___ \\ ____|___ \\| '_ \\| | | |     | | | |_");
  puts(" | | ___) |_____|__) | (_) | | | |___  | | |  _|");
  puts("|___|____/     |____/ \\___/|_|  \\____| |_| |_|");
  puts("\n");

  process();
  return 0;
}

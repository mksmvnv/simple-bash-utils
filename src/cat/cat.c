#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Flags {
  bool b, e, n, s, t, v;
} Flags;

Flags flag_parser(int argc, char** argv) {
  Flags flag = {false};
  struct option LongOptions[] = {{"number-nonblank", 0, NULL, 'b'},
                                 {"number", 0, NULL, 'n'},
                                 {"squeeze-blank", 0, NULL, 's'},
                                 {NULL, 0, NULL, 0}};
  int current_flag = getopt_long(argc, argv, "beEnstTv", LongOptions, NULL);
  switch (current_flag) {
    case 'b':
      flag.b = true;
      break;
    case 'e':
      flag.e = true;
    case 'E':
      flag.e = true;
      break;
    case 'n':
      flag.n = true;
      break;
    case 's':
      flag.s = true;
      break;
    case 't':
      flag.t = true;
      flag.v = true;
    case 'T':
      flag.t = true;
      break;
    case 'v':
      flag.v = true;
      break;
  }
}

void flag_mark_endl(Flags flag, char* line, int read) {
  for (int i = 0; i < read; ++i) {
    if (flag.e && line[i] == '\n') putchar('$');
    putchar(line[i]);
  }
}

void read_file() { return; }

int main(int argc, char** argv) {
  Flags flag = flag_parser(argc, argv);
  FILE* f = fopen(argv[1], "r");
  char* line = NULL;
  size_t memline = 0;
  int read = 0;
  read = getline(&line, &memline, f);
  while (read != -1) {
    flag_mark_endl(flag, line, read);
    read = getline(&line, &memline, f);
  }
  fclose(f);
  return 0;
}
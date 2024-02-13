#ifndef FAKE_CAT_H
#define FAKE_CAT_H

#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct {
  bool b;
  bool e;
  bool n;
  bool s;
  bool t;
  bool v;
} short_flags = {false};

const struct option long_flags[] = {
    {"number-nonblank", 0, NULL, 'b'}, {"show-ends", 0, NULL, 'E'},
    {"number", 0, NULL, 'n'},          {"squeeze-blank", 0, NULL, 's'},
    {"show-tabs", 0, NULL, 'T'},       {NULL, 0, NULL, 0}};

void scan_flag(int argc, char** argv);
void open_file(char* argv[]);
void print_file(FILE* file, int* count_line, int* last);
void print_visible_character(int ch);

#endif  // FAKE_CAT_H
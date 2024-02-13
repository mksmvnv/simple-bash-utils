#ifndef FAKE_GREP_H
#define FAKE_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_01 "fake_grep: %s: No such file or directory\n"

typedef struct {
  bool e;
  bool i;
  bool v;
  bool c;
  bool l;
  bool n;
  bool h;
  bool s;
  bool f;
  bool o;
  int count_files;
  int number_line;
  int count_matches;
} options;

void fake_grep(int argc, char **argv);

int scan_flag(int argc, char **argv, options *flags, char **template);
void print_main_data(char *str, options *options, char *tmpl, char *name);
void set_flag_f(options *flags, char **template, char *optarg);
void set_flag_e(options *flags, char **template, char *optarg);
void print_flag_o(regex_t my_regex, char *str, options flags);
void read_file(char *name, options flags, char *tmpl);
void print_extra_data(options flags, char *path);
void *increase_length_str(void *str, int size);
int create_template(char **str, char *optarg);
void setup_flag(options *flags, int argc);
void add_template(char **str, char *optarg);

#endif  // FAKE_GREP_H
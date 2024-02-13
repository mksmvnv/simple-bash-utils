#include "fake_cat.h"

int main(int argc, char* argv[]) {
  scan_flag(argc, argv);
  open_file(argv);
  return 0;
}

void scan_flag(int argc, char** argv) {
  int flags = getopt_long(argc, argv, "bnseEtTv", long_flags, 0);
  for (int i = 0; i < argc; i++) {
    for (; flags != -1;
         flags = getopt_long(argc, argv, "bnseEtTv", long_flags, 0)) {
      switch (flags) {
        case 'b':
          short_flags.b = true;
          break;
        case 'e':
          short_flags.e = true;
          short_flags.v = true;
          break;
        case 'E':
          short_flags.e = true;
          break;
        case 'n':
          short_flags.n = true;
          break;
        case 's':
          short_flags.s = true;
          break;
        case 't':
          short_flags.t = true;
          short_flags.v = true;
          break;
        case 'T':
          short_flags.t = true;
          break;
        case 'v':
          short_flags.v = true;
          break;
        case '?':
          break;
      }
    }
  }
}

void open_file(char** argv) {
  int count_line = 1;
  int last_char = '\n';
  for (int i = 1; argv[i] != NULL; i++) {
    if (argv[i][0] != '-' && argv[i][1] != '-') {
      FILE* file = fopen(argv[i], "r");
      if (file == NULL) {
        printf("fake_cat: %s: No such file or directory\n", argv[i]);
      } else {
        print_file(file, &count_line, &last_char);
      }
    }
  }
}

void print_file(FILE* file, int* count_line, int* last_char) {
  int count_b = 0;
  int empty_lines = 0;
  int ch;
  while ((ch = fgetc(file)) != EOF) {
    if (short_flags.s && ch == '\n') {
      if (empty_lines >= 1) {
        continue;
      }
      empty_lines++;
    } else {
      empty_lines = -1;
    }
    if (((!short_flags.b) && short_flags.n && *last_char == '\n') ||
        (short_flags.b && ch != '\n' && *last_char == '\n')) {
      if (count_b != 1) {
        printf("%6d\t", (*count_line)++);
        count_b++;
      }
    }
    if (short_flags.v && ch != '\t' && ch != '\n') {
      print_visible_character(ch);
    } else {
      if (short_flags.e && ch == '\n') {
        printf("%c", '$');
      }
      if (short_flags.t && ch == '\t') {
        printf("^I");
      } else {
        printf("%c", ch);
        *last_char = ch;
        count_b = 0;
      }
    }
  }
  fclose(file);
}

void print_visible_character(int ch) {
  if (ch >= 32 && ch < 127) {
    printf("%c", ch);
  } else if (ch == 127) {
    printf("^?");
  } else if (ch >= 128 + 32 && ch < 128 + 127) {
    printf("M-%c", ch - 128);
  } else if (ch >= 128) {
    printf("M-^%c", ch - 128 + 64);
  } else {
    printf("^%c", ch + 64);
  }
}
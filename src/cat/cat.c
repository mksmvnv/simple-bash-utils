#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

typedef struct Flags {
  bool number_nonblank;
  bool dollar_endl;
  bool number_all;
  bool squeeze_blank;
  bool tab_endl;
} Flags;

int cat_flag_parser(Flags* flags, char** argv, char* filename);
int cat_flags_execute(Flags* flag, int argc, char** argv, char* filename);
int cat_without_flags(int fd, char* filename);
int cat_with_flags(int argc, char** argv);

int main(int argc, char** argv) {
  if (argc == 1)
    if ((cat_without_flags(STDIN_FILENO, argv[0])) == 1)
      return 1;
    else if (cat_with_flags(argc, argv) == 1)
      return 1;
  return 0;
}

int cat_flag_parser(Flags* flags, char** argv, char* filename) {
  ++argv;
  if (*argv == '-') {
    ++argv;
    if (strcmp(argv, "number-nonblank") == 0) {
      flags->number_nonblank = true;
    } else if (strcmp(argv, "number") == 0) {
      flags->number_all = true;
    } else if (strcmp(argv, "squeeze-blank") == 0) {
      flags->squeeze_blank = true;
    } else {
      dprintf(STDERR_FILENO, "%s: invalid option '--%s'\n", filename, argv);
    }
    return 0;
  }
  for (char* val = argv; *val; ++val) {
    switch (*val) {
      case 'b':
        flags->number_nonblank = true;
        break;
      case 'e':
        flags->dollar_endl = true;
        break;
      case 'n':
        flags->number_all = true;
        break;
      case 's':
        flags->squeeze_blank = true;
        break;
      case 't':
        flags->tab_endl = true;
        break;
      default:
        dprintf(STDERR_FILENO, "%s: invalid option -- '%s'\n", filename, argv);
        return 1;
    }
  }
  return 0;
}

int cat_flags_execute(Flags flag, int argc, char** argv, char* filename) {
  char buf[4096];
  int fd = open(argv[0], O_RDONLY);
  if (fd == -1) {
    perror(filename);
    return 1;
  }
  int bytes_read = read(fd, buf, 4096);
  while (bytes_read != -1) {
    printf("%.*s", bytes_read, buf);
    bytes_read = read(fd, buf, 4096);
  }
  return 0;
}

int cat_without_flags(int fd, char* filename) {
  char buf[4096];
  if (fd == -1) {
    perror(filename);
    return 1;
  }
  int bytes_read = read(fd, buf, 4096);
  while (bytes_read != -1) {
    printf("%.*s", bytes_read, buf);
    bytes_read = read(fd, buf, 4096);
  }
  return 0;
}

int cat_with_flags(int argc, char** argv) {
  Flags flags = {0, 0, 0, 0, 0};
  for (int i = 1; i != argc; ++i) {
    if (*argv[i] == '-') {
      if (cat_flag_parser(&flags, argv[i], argv[0]) == 0) return 1;
    }
  }
  if ((flags.number_nonblank || flags.dollar_endl || flags.number_all ||
       flags.squeeze_blank || flags.tab_endl) == 0) {
    for (int i = 1; i != argc; ++i) {
      if (*argv[i] == '-')
        if (cat_without_flags(open(argv[i], O_RDONLY), argv[0]) == 0) return 1;
    }
  } else if ((flags.number_nonblank || flags.dollar_endl || flags.number_all ||
              flags.squeeze_blank || flags.tab_endl) == 0) {
    for (int i = 1; i != argc; ++i) {
      if (*argv[i] == '-')
        if (cat_flags_execute(flags, argc, argv) == 0) return 1;
    }
  }
  return 0;
}
#include "fake_grep.h"

int main(int argc, char **argv) {
  fake_grep(argc, argv);
  return 0;
}

void fake_grep(int argc, char **argv) {
  if (argc > 1) {
    char *temp = NULL;
    options flags = {false};

    for (int x = scan_flag(argc, argv, &flags, &temp); x < argc; x += 1)
      read_file(argv[x], flags, temp);

    if (temp != NULL) free(temp);
  }
}

int scan_flag(int argc, char **argv, options *flags, char **template) {
  for (int sym = 0; (sym = getopt(argc, argv, "e:ivclnhsf:o")) != (-1);) {
    switch (sym) {
      case 'i':
        flags->i = true;
        break;
      case 'v':
        flags->v = true;
        break;
      case 'c':
        flags->c = true;
        break;
      case 'l':
        flags->l = true;
        break;
      case 'n':
        flags->n = true;
        break;
      case 'h':
        flags->h = true;
        break;
      case 's':
        flags->s = true;
        break;
      case 'o':
        flags->o = true;
        break;
      case 'e':
        set_flag_e(flags, template, optarg);
        break;
      case 'f':
        set_flag_f(flags, template, optarg);
        break;
    }
  }
  if (!(flags->e || flags->f)) {
    create_template(template, argv[optind]);
    optind += 1;
  }
  setup_flag(flags, argc);
  return optind;
}

void read_file(char *path, options flags, char *template) {
  FILE *file = fopen(path, "r");
  if (file != NULL) {
    for (char sym = '0'; (sym = getc(file)) != EOF;) {
      char *line = calloc(256, 1);
      flags.number_line += 1;
      int length = 0;

      for (line[length] = '\0'; sym != EOF && sym != '\n'; sym = getc(file)) {
        line[length] = sym;
        line[length += 1] = '\0';
        if (length % 255 == 0) line = increase_length_str(line, length + 256);
      }

      print_main_data(line, &flags, template, path);
      free(line);
    }
    print_extra_data(flags, path);
    fclose(file);
  } else if (flags.s == 0) {
    fprintf(stderr, ERROR_01, path);
  }
}

void set_flag_f(options *flags, char **template, char *optarg) {
  FILE *file = fopen(optarg, "r");
  if (file != NULL) {
    for (char sym = '0'; (sym = getc(file)) != EOF;) {
      int length = 0;
      char *line = calloc(256, 1);

      for (line[length] = '\0'; sym != EOF && sym != '\n'; sym = getc(file)) {
        line[length] = sym;
        line[length += 1] = '\0';
        if (length % 255 == 0)
          line = (char *)increase_length_str(line, length + 256);
      }

      if (!(flags->e || flags->f))
        flags->f = create_template(template, line);
      else
        add_template(template, line);
      free(line);
    }
    fclose(file);
  } else if (!(flags->s)) {
    fprintf(stderr, ERROR_01, optarg);
  }
}

void set_flag_e(options *flags, char **template, char *optarg) {
  if (!(flags->e || flags->f))
    flags->e = create_template(template, optarg);
  else
    add_template(template, optarg);
}

void print_extra_data(options flags, char *path) {
  if (flags.c) {
    if (flags.l) {
      if (flags.count_files > 1) {
        printf("%s:1\n", path);
      }
    } else {
      if (flags.count_files > 1) printf("%s:", path);
      printf("%i\n", flags.count_matches);
    }
  }
  if (flags.l && flags.count_matches) printf("%s\n", path);
}

void print_main_data(char *line, options *flags, char *template, char *path) {
  regex_t regex;
  if (regcomp(&regex, template, flags->i ? REG_ICASE : REG_EXTENDED) == 0) {
    if (regexec(&regex, line, 0, NULL, 0) == flags->v) {
      flags->count_matches += 1;
      if ((flags->c || flags->l) == 0) {
        if (flags->count_files > 1 && !(flags->h)) printf("%s:", path);
        if (flags->n) printf("%i:", flags->number_line);
        if (!flags->o)
          printf("%s\n", line);
        else {
          print_flag_o(regex, line, *flags);
        }
      }
    }
    regfree(&regex);
  }
}

void print_flag_o(regex_t regex, char *line, options flags) {
  int first_iteration = 0;
  while (regexec(&regex, line, 0, NULL, 0) == flags.v) {
    if (flags.n && first_iteration != 0) printf("%i:", flags.number_line);
    first_iteration = 1;
    char *aux = (char *)calloc(strlen(line) + 1, 1);
    strcpy(aux, line);
    int end = strlen(line);
    while (regexec(&regex, aux, 0, NULL, 0) == flags.v) {
      end--;
      aux[strlen(aux) - 1] = 0;
    }
    aux[strlen(aux)] = line[strlen(aux)];
    int start = 0;
    while (regexec(&regex, aux, 0, NULL, 0) == flags.v && strlen(aux) > 0) {
      start++;
      int j = 0;
      while (aux[j] != 0) {
        aux[j] = aux[j + 1];
        j++;
      }
    }
    start--;
    int i = strlen(aux);
    while (i != 0) {
      aux[i] = aux[i - 1];
      i--;
    }
    aux[0] = line[start];
    printf("%s\n", aux);
    free(aux);
    i = start + 1;
    while (line[i] != 0) {
      line[i - start - 1] = line[i];
      i++;
    }
    line[i - start - 1] = 0;
  }
}

void setup_flag(options *flags, int argc) {
  if (flags->v && flags->o) exit(0);
  if (flags->o && (flags->l || flags->c || flags->v)) flags->o = 0;
  flags->count_files = argc - optind;
}

int create_template(char **str, char *optarg) {
  *str = calloc(strlen(optarg) + 1, 1);
  if (*str) strcpy(*str, optarg);
  return str ? 1 : 0;
}

void add_template(char **str, char *optarg) {
  *str = increase_length_str(*str, strlen(*str) + strlen(optarg) + 2);
  if (*str) strcat(strcat(*str, "|"), optarg);
}

void *increase_length_str(void *str, int size) {
  char *aux = realloc(str, size);
  return aux;
}
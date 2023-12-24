#include <stdio.h>
#include <getopt.h>
#include <stdbool.h>

typedef struct {
    bool number_nonblank;
    bool mark_endl;
    bool number;
    bool squeeze_blank;
    bool tab;
    bool print_nonprintable;
}Flags;

Flags cat_read_flags(int argc, char *argv[]) {
    struct option longOptions[] = {
        {"number-nonblank", 0, NULL, 'b'},
        {"number", 0, NULL, 'n'},
        {"squeeze-blank", 0, NULL, 's'},
        {NULL, 0, NULL, 0}
    };
    int current_flag = getopt_long(argc, argv, "bevEnstT", longOptions, NULL);
    Flags flags = {false, false, false, false, false};
    for (;current_flag != -1
         ;current_flag = getopt_long(argc, argv, "bevEnstT", longOptions, NULL)) {
            switch (current_flag) {
                case 'b':
                    flags.number_nonblank = true;
                    break;
                case 'e':
                    flags.mark_endl = true;
                case 'v':
                    flags.print_nonprintable = true;
                    break;
                case 'E':
                    flags.mark_endl = true;
                    break;
                case 'n':
                    flags.number = true;
                    break;
                case 's':
                    flags.squeeze_blank = true;
                    break;
                case 't':
                    flags.tab = true;
                    flags.print_nonprintable = true;
                case 'T':
                    flags.tab = true;
                    break;
            }

    }
    return flags;
}


int main(int argc, char *argv[]) {
    Flags flags = cat_read_flags(argc, argv);
    if (flags.number_nonblank)
        printf("number_nonblank\n");
    if (flags.mark_endl)
        printf("mark_endl\n");
    if (flags.number)
        printf("number\n");
    if (flags.squeeze_blank)
        printf("squeeze_blank\n");
    if (flags.tab)
        printf("tab\n");
    if (flags.print_nonprintable)
        printf("print_nonprintable\n");
    return 0;
}

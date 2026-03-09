#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

void print_usage(char **argv);

FILE *open_file(char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "ERROR: Could not open file %s\n", filepath);
        exit(1);
    }
    return file;

}

void count_all(FILE *file, int lflag, int wflag, int mflag) {
    int c;
    int in_word = 0;
    unsigned long int nl = 0lu, w = 0lu, ch = 0lu;
    while ((c = fgetc(file)) != EOF) {
        if (mflag) ++ch;
        if (lflag && c == '\n') ++nl;
        if (wflag) {
            if (isprint(c) && !isspace(c)) {
                in_word = 1;
            } else if (in_word) {
                ++w;
                in_word = 0;
            }
        }
    }
    if (wflag && in_word) ++w;
    if (lflag) printf("lines: %lu\n", nl);
    if (wflag) printf("words: %lu\n", w);
    if (mflag) printf("characters: %lu\n", ch);
}

int main (int argc, char **argv) {

    char c;
    int mflag = 0;
    int lflag = 0;
    int wflag = 0;
    opterr = 0;

    while (( c = getopt(argc, argv, "hmlw")) != -1) {
        switch (c) {
            case 'm':
                mflag = 1;
                break;
            case 'l':
                lflag = 1;
                break;
            case 'w':
                wflag = 1;
                break;
            case 'h':
                print_usage(argv);
                break;
            case '?':
                fprintf(stderr, "ERROR: Unrecognized flag `%c'.\n", optopt);
                print_usage(argv);
                break;
        }
    }

    // default
    if (lflag == 0 && wflag == 0 && mflag == 0) {
        lflag = wflag = mflag = 1;
    }

    for (int i = optind; i < argc; i++) {
        printf("%s:\n", argv[i]);
        FILE *fp = open_file(argv[i]);
        count_all(fp, lflag, wflag, mflag);
        fclose(fp);
    }
    return 0;
}

void print_usage(char **argv) {
    printf("Usage: %s [-hmlw] <file>\n", argv[0]);
    printf("Options:\n");
    printf("   -h Print this help message.\n");
    printf("   -m Print the character count.\n");
    printf("   -l Print the line count.\n");
    printf("   -w Print the word count.\n");
    exit(0);
}


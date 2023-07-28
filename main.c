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

void count_lines(FILE *file) {
    int c;
    unsigned long int nl = 0lu;
    while ((c = fgetc(file)) != EOF)
        if (c == '\n')
            ++nl;
    printf("lines: %lu\n", nl);
}

void count_words(FILE *file) {
    int c, currword;
    unsigned long int w = 0lu;
    currword = 0;
    while ((c = fgetc(file)) != EOF) {
        if (isprint(c) && !isspace(c)) {
           ++currword; 
        }
        else if (currword > 0){
            ++w;
            currword = 0;
        }
    }
    printf("words: %lu\n", w);
}

void count_chars(FILE *file) {
    int c;
    unsigned long int ch = 0lu;
    while ((c = fgetc(file)) != EOF) {
        ++ch;
    }
    printf("characters: %lu\n", ch);
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
        if (lflag == 1) {
            count_lines(fp);
            rewind(fp);
        }
        if (wflag == 1) {
            count_words(fp);
            rewind(fp);
        }
        if (mflag == 1) {
            count_chars(fp);
        }
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


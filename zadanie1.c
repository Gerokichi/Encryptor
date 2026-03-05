#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int UsherResult(int argc, char *argv[], char **pass, char **infile, char **outfile);

void Error();
void Copy(char *content, char **sosud);


int main(int argc, char *argv[]) {
    char *pass = NULL;
    char *infile = NULL;
    char *outfile = NULL;

    const int res = UsherResult(argc, argv, &pass, &infile, &outfile);
    if (res == 1) {
        printf("ENcrypt\n");
    } else if (res == -1) {
        printf("DEcrypt\n");
    } else {
        Error();
    }

    printf("--- Configuration ---\n");

    // Печатаем пароль (скрываем его или пишем "not set")
    if (pass != NULL) {
        printf("Password: %s\n", pass);
    } else {
        printf("Password: (not set)\n");
    }

    // Печатаем файлы
    printf("Input file:  %s\n", infile  ? infile  : "none");
    printf("Output file: %s\n", outfile ? outfile : "none");

    printf("---------------------\n");

    free(pass);
    free(infile);
    free(outfile);
    return 0;
}


int UsherResult(const int argc, char *argv[], char **pass, char **infile, char **outfile) {
    if (argc != 8) return 0;

    int res = 0;

    for (int i = 1; i < argc; i++) {
        printf("%s\n", argv[i]);
        if (argv[i][0] == '-' && strlen(argv[i]) == 2) {
            char **sosud = NULL;

            switch (argv[i][1]) {
                case 's':
                    if (res != 0) return 0;
                    res = 1;
                    break;
                case 'd':
                    if (res != 0) return 0;
                    res = -1;
                    break;
                case 'p':
                    sosud = pass;
                    break;
                case 'i':
                    sosud = infile;
                    break;
                case 'o':
                    sosud = outfile;
                    break;
                default:
                    return 0;
            }

            if (sosud != NULL) {
                if (i + 1 < argc) {
                    Copy(argv[i + 1], sosud);
                    i++;
                } else {
                    return 0;
                }
            }

        } else {
            return 0;
        }
    }

    return res;
}



void Error() {
    printf("chyba\n");
}

void Copy(char *content, char **sosud) {
    if (*sosud != NULL) free(*sosud);

    *sosud = malloc(strlen(content) + 1);
    if (*sosud != NULL) {
        strcpy(*sosud, content);
    }
}
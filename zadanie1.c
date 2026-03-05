#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int UsherResult(int argc, char *argv[], char **pass, char **infile, char **outfile);
bool AuraX (char *infile, char* outfile, char* password, bool decrypt);

void Error();
void Copy(char *content, char **sosud);


int main(int argc, char *argv[]) {
    char *pass = NULL;
    char *infile = NULL;
    char *outfile = NULL;

    const int res = UsherResult(argc, argv, &pass, &infile, &outfile);
    if ((res == 1 || res == -1) && pass && infile && outfile) {
        bool decrypt = (res == -1);
        if (!AuraX(infile, outfile, pass, decrypt)) Error();
    } else {
        Error();
    }

    free(pass);
    free(infile);
    free(outfile);
    return 0;
}


int UsherResult(const int argc, char *argv[], char **pass, char **infile, char **outfile) {
    if (argc != 8) return 0;

    int res = 0;

    for (int i = 1; i < argc; i++) {
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

bool AuraX (char *infile, char* outfile, char* password, bool decrypt) {
    FILE *in = fopen(infile, "rb");
    if (in == NULL) return false;

    FILE *out = fopen(outfile, "wb");
    if (out == NULL) {
        fclose(in);
        return false;
    }

    size_t pass_len = strlen(password);
    size_t i = 0;
    int c;

    while ((c = fgetc(in)) != EOF) {
        unsigned char atom = (unsigned char) c;
        unsigned char key = (unsigned char)(password[i % pass_len] + i);

        if (decrypt) {
            unsigned char unfinal = (unsigned char)(atom - i);
            unsigned char decrypted = (unsigned char)(unfinal ^ key);
            fputc(decrypted, out);
        } else {
            unsigned char xored = (unsigned char)(atom ^ key);
            unsigned char encrypted = (unsigned char)(xored + i);
            fputc(encrypted, out);
        }

        i++;
    }

    fclose(in);
    fclose(out);
    return true;
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
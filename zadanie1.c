#include <stdio.h>
#include <string.h>

int UsherResult(int argc, char *argv[], char **pass, char **infile, char **outfile);

void Error();


int main(int argc, char *argv[]) {
    char *pass = NULL;
    char *infile = NULL;
    char *outfile = NULL;

    const int res = UsherResult(argc, argv, &pass, &infile, &outfile);
    if (res == 1) {
        printf("ENcrypt\n");
    }
    else if (res == -1) {
        printf("DEcrypt\n");
    }
    else {
        Error();
    }

    return 0;
}


int UsherResult(const int argc, char *argv[], char **pass, char **infile, char **outfile) {
    int res = 0;

    if (argc != 8) {
        return res;
    }

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-' && strlen(argv[i]) == 2) {
            switch (argv[i][1]) {
                case 's':
                    res = 1;
                    break;
                case 'd':
                    res = -1;
                    break;
                case 'p':

                    break;
                case 'i':
                    break;
                case 'o':
                    break;
                default:
                    res = 0;
                    break;
            }
        }
        else {
            res = 0;
            break;
        }
    }

    return res;
}



void Error() {
    printf("chyba\n");
}

void Copy(char *content, char *sosud) {

}
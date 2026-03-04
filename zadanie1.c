#include <stdio.h>
#include <stdbool.h>

bool StandardsMet(int argc, char *argv[]);

void Error();


int main(int argc, char *argv[]) {
    if (StandardsMet(argc, argv)) {
        printf("Jee boy\n");
    } else {
        Error();
    }

    return 0;
}

bool StandardsMet(const int argc, char *argv[]) {
    if (argc < 2 || argc > 8) {
        return false;
    }


    return true;
}

void Error() {
    printf("chyba\n");
}

#include <dirent.h>
#include <stdio.h>
#include <stdio.h>
#include <unistd.h>

int main() {
    const char *filename = "test.txt";

    if (access(filename, F_OK) == 0) {
        printf("File exists.\n");

        if (access(filename, R_OK) == 0)
            printf("You have read permission.\n");
        else
            printf("No read permission.\n");

        if (access(filename, W_OK) == 0)
            printf("You have write permission.\n");
        else
            printf("No write permission.\n");
    } else {
        printf("File does not exist.\n");
    }

    return 0;
}

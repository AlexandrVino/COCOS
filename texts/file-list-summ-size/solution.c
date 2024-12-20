#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

const int BUFFER_SIZE = 4096;

int main(int argc, char const *argv[]) {
    char buffer[BUFFER_SIZE]; 
    size_t total_size = 0; 
    struct stat file_stat;

    while (EOF != scanf("%s", buffer)) {
        if (stat(buffer, &file_stat) != -1) {
            if (S_ISREG(file_stat.st_mode)) {
                total_size += file_stat.st_size;
            }
        } 
        
    }

    printf("Total size: %ld bytes\n", total_size);
    return 0;
}

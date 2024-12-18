#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>


const int BUFFER_SIZE = 4096;

struct Item {
  int value;
  uint32_t next_pointer;
};

int close_if(int fd) {
    if (fd != -1) close(fd);
}

int close_all(int fd1, int fd2, int fd3) {
    close_if(fd1);
    close_if(fd2);
    close_if(fd3);
}

int main(int argc, char const* argv[])
{    
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {    
        return 1;
    }
    
    int fd_int_out = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (fd_int_out == -1) {
        close_all(fd, -1, -1);
        return 2;
    }
    int fd_other_out = open(argv[3], O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (fd_other_out == -1) {
        close_all(fd, fd_int_out, -1);
        return 2;
    }

    char buffer[BUFFER_SIZE];
    char bufferNums[BUFFER_SIZE];
    char bufferOthers[BUFFER_SIZE];

    int buffNumIndex = 0;
    int buffOtherIndex = 0;

    while (1) {
        int res = read(fd, &buffer, sizeof(buffer));
        if (res == -1) {
            close_all(fd, fd_int_out, fd_other_out);
            return 3;
        }
        if (res == 0) break;

        for (int i = 0; i < res / sizeof(char); ++i) {
            if ('0' <= buffer[i] && '9' >= buffer[i]) {
                bufferNums[buffNumIndex++] = buffer[i];
                if (buffNumIndex >= BUFFER_SIZE) {
                    buffNumIndex = 0;
                    if (write(fd_int_out, &bufferNums, sizeof(bufferNums)) == -1) {
                        close_all(fd, fd_int_out, fd_other_out);
                        return 3;
                    }
                }
            } else {
                bufferOthers[buffOtherIndex++] = buffer[i];
                if (buffOtherIndex >= BUFFER_SIZE) {
                    buffOtherIndex = 0;
                    if (write(fd_other_out, &bufferOthers, sizeof(bufferOthers)) == -1) {
                        close_all(fd, fd_int_out, fd_other_out);
                        return 3;
                    }
                }
            }
        }

        if (buffNumIndex > 0) {
            if (write(fd_int_out, &bufferNums, sizeof(char) * buffNumIndex) == -1) {
                close_all(fd, fd_int_out, fd_other_out);
                return 3;
            }
        }

        if (buffOtherIndex > 0) {
            if (write(fd_other_out, &bufferOthers, sizeof(char) * buffOtherIndex) == -1) {
                close_all(fd, fd_int_out, fd_other_out);
                return 3;
            }
        }
    }
    
    close_all(fd, fd_int_out, fd_other_out);
    return 0;
}
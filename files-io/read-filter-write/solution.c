#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>

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
    char item;
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

    while (1) {
        int res = read(fd, &item, sizeof(char));
        if (res == -1) {
            close_all(fd, fd_int_out, fd_other_out);
            return 3;
        }
        if (res == 0) break;

        if ('0' <= item && '9' >= item) {
            // printf("%c", item);
            if (write(fd_int_out, &item, sizeof(char)) == -1) {
                close_all(fd, fd_int_out, fd_other_out);
                return 3;
            }
        } else {
            if (write(fd_other_out, &item, sizeof(char)) == -1) {
                close_all(fd, fd_int_out, fd_other_out);
                return 3;
            }
        }
         
        if (item == '\0') {
            break;
        }
    }
    
    close_all(fd, fd_int_out, fd_other_out);
    return 0;
}
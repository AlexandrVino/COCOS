// C program for writing
// struct to file
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>

struct Item {
  int value;
  uint32_t next_pointer;
};

int main(int argc, char const* argv[])
{    
    struct Item item;
    int fd = open(argv[1], O_RDONLY);

    while (0 < read(fd, &item, sizeof(struct Item))) {
        printf("%d ", item.value);
        if (item.next_pointer != 0) {
            lseek(fd, item.next_pointer, SEEK_SET);
        } else {
            break;
        }
    }
    close(fd);

    return 0;
}
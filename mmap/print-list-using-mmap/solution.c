#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

struct Item
{
    int value;
    uint32_t next_pointer;
};

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        return 1;
    }

    struct stat file_stat;
    if (fstat(fd, &file_stat) == -1 || file_stat.st_size == 0)
    {
        close(fd);
        return 0;
    }

    void *start = mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    struct Item *content = (struct Item *)start;
    printf("%d ", content->value);
    while (content->next_pointer != 0)
    {
        content = (struct Item *)(start + content->next_pointer);
        printf("%d ", content->value);
    }

    munmap(start, file_stat.st_size);
    close(fd);

    return 0;
}
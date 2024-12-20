#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if (argc < 3)
        return 1;

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        return 1;

    struct stat file_stat;
    if (fstat(fd, &file_stat) == -1 || file_stat.st_size == 0)
    {
        close(fd);
        return 1;
    }

    char *content = (char *)mmap(NULL, file_stat.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (content == NULL)
    {
        close(fd);
        return 1;
    }

    const char *search_string = argv[2];
    size_t search_string_len = strlen(search_string);
    if (search_string_len > file_stat.st_size)
        close(fd);

    char *pos = content;
    for (size_t i = 0; i <= file_stat.st_size - search_string_len; ++i)
    {
        if (memcmp(pos, search_string, search_string_len) == 0)
            printf("%ld ", i);
        ++pos;
    }

    if (munmap(content, file_stat.st_size) == -1)
    {
        close(fd);
        return 1;
    }
    close(fd);

    return 0;
}
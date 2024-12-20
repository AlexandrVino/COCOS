#include <stdio.h>
#include <stdlib.h>

extern void normalize_path(char *path)
{
    char *source = path;
    char *dest = path;

    while (*source)
    {
        if (*source == '/') // adda///////ad
        {
            *dest++ = '/';
            while (*source == '/')
            {
                source++;
            }
            continue;
        }

        if (*source == '.' && source[1] == '/') // daasd/./adasd
        {
            source++;
            while (*source == '/')
            {
                source++;
            }
            continue;
        }

        if (*source == '.' && source[1] == '.' && source[2] == '/') // adad/../adad
        {
            source += 2;
            while (*source == '/')
            {
                source++;
            }
            if (dest > path + 1)
            {
                dest--;
                while (dest > path && *(dest - 1) != '/')
                {
                    dest--;
                }
            }
            continue;
        }
        *dest++ = *source++;
    }
    if (dest > path + 1 && *(dest - 1) == '/')
    {
        dest--;
    }

    *dest = '\0';
}

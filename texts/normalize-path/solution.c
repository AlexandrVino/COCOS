#include <stdio.h>
#include <stdlib.h>

extern void normalize_path(char *path) {
    fgets(path, sizeof(path), stdin);
    
    int i = 0;
    while (*(path + i) != '\0') {
        if (*(path + i) == ' ') continue;
        printf("%c.", *(path + i));
        ++i;
    }
    printf("\n");

    i = 0;
    while (*(path + i) != '\0') {
        if (*(path + i) == '.') {
            if (*(path + i + 1) == '.') {
                *(path + i - 1) = ' ';
                *(path + i) = ' ';
                *(path + i + 1) = ' ';
                *(path + i + 2) = ' ';
                int j = i - 1;
                while (j > 0 && *(path + j - 1) != '/') {
                    *(path + j - 1) = ' ';
                    --j;
                }
                ++i;
                ++i;
                ++i;                
            } else if (*(path + i + 1) == '/') {
                *(path + i) = ' ';
                *(path + i + 1) = ' ';
                ++i;
                ++i;
            }
        } else if (*(path + i) == '/' && *(path + i + 1) == '/') {
            *(path + i) = ' ';
            ++i;
        } else {
            ++i;
        }
    }
    
    i = 0;
    while (*(path + i) != '\0') {
        if (*(path + i) == ' ') continue;
        printf("%c", *(path + i));
        ++i;
    }
    printf("\n");
    
    return 0;
}

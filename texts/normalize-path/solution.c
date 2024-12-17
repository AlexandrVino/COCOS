#include <stdio.h>
#include <stdlib.h>

extern void normalize_path(char *path) {
    fgets(path, sizeof(path), stdin);
    
    strcspn(path, "\n");
    return 0;
}

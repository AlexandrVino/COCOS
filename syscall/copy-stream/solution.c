#include <signal.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

long syscall(long number, ...);

const int BUFF_SIZE = 1024;

int _start()
{    
    char buff[BUFF_SIZE];

    int size;
    while ((size = syscall(SYS_read, 0, buff, BUFF_SIZE * sizeof(char))) > 0) {
        syscall(SYS_write, 1, buff, size * sizeof(char));
    }
    syscall(SYS_exit, 0);
}

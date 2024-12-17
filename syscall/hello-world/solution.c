#include <signal.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>

long syscall(long number, ...);

int _start()
{    
    char *message = "Hello, World!\n";
    syscall(SYS_write, 1, message, 14 * sizeof(char));
    syscall(SYS_exit, 0);
}
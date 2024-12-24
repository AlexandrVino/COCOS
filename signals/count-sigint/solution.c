#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int counter = 0;

void execute(int sign)
{
    if (sign == SIGINT)
    {
        ++counter;
    }
    else if (sign == SIGTERM)
    {
        printf("%d", counter);
        exit(0);
    }
}

int main(int argc, char const *argv[])
{
    pid_t pid = getpid();
    printf("%d\n", pid);
    fflush(NULL);

    if (signal(SIGINT, execute) == SIG_ERR)
        exit(1);
    if (signal(SIGTERM, execute) == SIG_ERR)
        exit(1);

    while (1)
    {
        pause();
    }
}
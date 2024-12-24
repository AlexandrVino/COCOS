#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

const int BUFFER_SIZE = 4096;
int index = 1;

void print_via_fork(int n)
{
    for (int i = 1; i <= n; ++i)
    {
        pid_t pid = fork();
        if (pid == -1)
            exit(1);

        if (pid == 0)
        {
            printf("%d", i);
            printf(i == n ? "\n" : " ");
            exit(0);
        }
        wait(NULL);
    }
}

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        exit(1);
    }
    int n;
    sscanf(argv[1], "%d", &n);

    print_via_fork(n);
}
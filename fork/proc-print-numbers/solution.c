#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

const int BUFFER_SIZE = 4096;

void print_via_fork(int curr, int n)
{
    if (curr <= 0) 
        exit(0);
    
    pid_t pid = fork();
    if (pid == -1)
    {
        exit(1);
    }

    if (pid == 0)
    {
        print_via_fork(curr - 1, n);
        exit(0);
    }
    else
    {
        wait(NULL);
        printf("%d", curr);
        printf(curr == n ? "\n": " ");
    }
}

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        exit(1);
    }
    int n;
    sscanf(argv[1], "%d", &n);
    print_via_fork(n, n);
}
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


int main(int argc, char const *argv[])
{
    if (argc < 3)
    {
        exit(1);
    }

    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1)
    {
        exit(1);
    }

    if (pid == 0)
    {
        dup2(pipefd[1], 1);
        close(pipefd[0]);
        close(pipefd[1]);
        execlp(argv[1], argv[1], (char *)NULL);
        exit(1);
    }
    else
    {
        dup2(pipefd[0], 0);
        close(pipefd[1]);
        close(pipefd[0]);
        execlp(argv[2], argv[2], (char *)NULL);
        exit(1);
    }

    waitpid(pid, NULL, 0);
    return 0;
}
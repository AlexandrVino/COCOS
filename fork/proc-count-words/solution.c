#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

const int BUFFER_SIZE = 4096;

int main(int argc, char const *argv[])
{
    int words = 0;
    int child_res = 0;
    char buffer[BUFFER_SIZE];
    while (1)
    {
        pid_t pid = fork();
        if (pid == -1)
        {
            continue;
        }
        if (pid == 0)
        {
            if (scanf("%s", buffer) == 1)
                return 0;
            return 1;
        }
        else
        {
            wait(&child_res);
            if (child_res == 0)
                ++words;
            else
                break;
        }
    }
    printf("%d\n", words);
}
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{

        int pipe0[2], pipe1[2];

        pipe(pipe0);

        printf("2 Pipes 2 Process");

        char buffer;
        int fd = open("log", O_RDONLY);

        if(fd == -1)
                printf("Error opening file!");
        else
        {
                while(read(fd, &buffer, 1))
                        write(pipe0[1], &buffer, 1);
        }

        pipe(pipe1);
        int forkRes = fork();

        if(forkRes == 0)
        {
                dup2(pipe0[0], 0);
                dup2(pipe1[1], 1);
                close(pipe0[1]);
                close(pipe1[0]);
                execlp("head", "head", "-n2", NULL);
                //execlp("grep", "grep", "admin", NULL);
        }
        else
        {
                wait(NULL);
                dup2(pipe1[0], 0);
                close(pipe0[0]);
                close(pipe0[1]);
                close(pipe1[1]);
                execlp("wc", "wc", "-l", NULL);
        }
}

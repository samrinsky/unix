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


//or


#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>

#define READ 0
#define WRITE 1

int main(){
        int fd1[2], fd2[2];
        int forkresult;

        if(pipe(fd1)==-1 || pipe(fd2)==-1){
                perror("pipes could not be created");
                exit(1);
        }
//      perror("Pipes created");
        int log = open("log", O_RDONLY);

        int i;
        char buf[1];
        while(i=(read(log,buf,1))>0)
        {
                write(fd1[WRITE], buf, 1);
        }
//      perror("wrote file: about to fork");
        forkresult = fork();
        if(forkresult <0){
//              perror("fork failed");
                exit(2);
        }

        if(forkresult==0){
//              perror("in child");
                dup2(fd1[READ], READ);
                dup2(fd2[WRITE], WRITE);
//              perror("before execl");
                execlp("grep", "grep", "admin",NULL);
        }
        else{
//              perror("before wait");
                wait(NULL);
//              perror("after wait");
                close(fd1[READ]);
                close(fd2[WRITE]);
                dup2(fd2[READ], READ);
//              dup2(stdout, WRITE);
//              perror("before execlp");
                execlp("wc", "wc", "-l", NULL);
        }
}

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int fd[2];
    if( pipe(fd) < 0 ) exit(-1);

    pid_t pid = fork();
    if( pid < 0) exit(-1);
    if( pid == 0 )
    {
        int data[2];
        if( read( fd[0], data, 2 * sizeof(int) ) != 2 * sizeof(int) )  exit(-1);

        int result = data[1] * data[0];

        if( write( fd[1], &result, sizeof(int)) != sizeof(int) ) exit(-1);

        exit(0);
    }
    else
    {
        int input[2];
        scanf("%d %d", input, input + 1);

        if( write( fd[1], input, 2 * sizeof(int)) != 2 * sizeof(int) ) exit(-1);

        int status;
        wait(&status);

	int output;
        if( read( fd[0], &output, sizeof(int) ) != sizeof(int)) exit(-1);
        printf("%d\n", output);
    }
    return 0;
}

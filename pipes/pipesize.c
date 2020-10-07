#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int fd[2];

	if(pipe(fd) < 0)
	{
		exit(-1);
	}

	size_t pipeSize = 0;

	while(write(fd[1], "a", 1)) printf("%ld\n",++pipeSize);
	close(fd[1]);
	close(fd[0]);
}

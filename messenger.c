#include <stdio.h>
#include <sys/types>
#include <unistd.h>

#define SIZE 100


void Write(const char* fifo_name)
{

	int fd;
	if ((fd = open(fifo_name, O_WRONLY)) < 0) exit(-1);

	char message[SIZE + 1] = {};

	while(1) {
		fgets(message, SIZE, stdin);
		write(fd, message, SIZE);
		memset(message, '\0', SIZE);
	}
}

void Read(const char* fifo_name)
{
	int fd;
	if ((fd = open(fifo_name, O_RDONLY)) < 0) exit(-1);

	char message[SIZE + 1] = {};

	while(1) {
		int size = read(fd, message, SIZE);
		if (size <= 0) {
			close(fd);
			exit(0);
		}
		printf("%s\n", message);
		memset(message, '\0', SIZE);
	}
}

int main(int argc, char *argv[])
{
	int f1 = mknod("0", S_IFIFO | 0666, 0);

	if (f1 < 0 && errno != EEXIST) exit(-1);

	int f2 = mknod("1", S_IFIFO | 0666, 0);

	if (f2 < 0 && errno != EEXIST) exit(-1);

	char r_fifo[2] = {};
	char w_fifo[2] = {};

	int client = atoi(argv[1]);
	if (client == 1)
	{
		r_fifo[0] = '1';
		w_fifo[0] = '0';
	 }
	if (client == 2)
	{
		r_fifo[0] = '0';
		w_fifo[0] = '1';
	}

	pid_t pid = fork();
	
	if (pid < 0) exit(-1);
	else if (pid == 0)
		Write(fifo_write);
	else
		Read(fifo_read);
	return 0
}


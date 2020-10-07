#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <string.h>

int main()
{
    int N = 8;
    int fd = open("tex", O_RDONLY);

    char* buffer = (char*)calloc(N + 1, sizeof(char));
    while( read(fd, buffer, N) > 0) 
    {
        printf("%s\n", buffer);
        memset(buffer, '\0', N+1);
    .}
    free(buffer);
    close(fd);

    return 0;
}

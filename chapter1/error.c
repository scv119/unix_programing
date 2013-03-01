#include <errno.h>
#include <fcntl.h>
extern int errno;

int main()
{
    int fd;
    fd = open("file", O_RDONLY);

    if (fd == -1)
    {
        perror("Cannot open file!");
    }

    return 0;
}

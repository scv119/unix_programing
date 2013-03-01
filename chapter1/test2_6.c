#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#define BUFFERSIZE 1024

void oops(const char* str0, const char* str1);

int main(int argc, char *argv[])
{
    int fd0, fd1, fd2;
    int  n_char;
    char buffer[BUFFERSIZE];
    char* message = "testing 123...";

    if (argc != 2) {
        fprintf(stderr, "usage: %s file\n", argv[0]);
        exit(1);
    }

    if ((fd0 = open(argv[1], O_RDONLY)) == -1)
        oops("Error open file", argv[1]);

    if ((fd1 = open(argv[1], O_WRONLY)) == -1)
        oops("Error open file", argv[1]);

    if ((fd2 = open(argv[1], O_RDONLY)) == -1)
        oops("Error open file", argv[1]);

    memset(buffer, 0, BUFFERSIZE);

    if (read(fd0, buffer, 20) != 20)
        oops("Error read file", argv[1]);

    printf("%s\n", buffer);

    if (write(fd1, message, sizeof(message)) != sizeof(message))
        oops("Error write file", argv[1]);

    memset(buffer, 0, BUFFERSIZE);

    if (read(fd2, buffer, 20) != 20)
        oops("Error read file", argv[1]);

    printf("%s\n", buffer);

    return 0;
}

void oops(const char* str0, const char* str1)
{
    fprintf(stderr, "Error: %s", str0);
    perror(str1);
    exit(1);
}

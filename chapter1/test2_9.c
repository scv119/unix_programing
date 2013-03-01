#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
char buffer[BUFFER_SIZE];
char* str = "hello world!";

void oops(const char *file, const char *message)
{
    fprintf(stderr, "Error %s:", file);
    perror(message);
    exit(1);
}

void read_before(const char* file)
{
    int fd;


    if ((fd = open(file, O_RDONLY)) == -1)
        oops(file, "Failed to open file");
     
    if (lseek(fd, 100, SEEK_END) == -1)
        oops(file, "Failed to lseek");

    memset(buffer, 0, BUFFER_SIZE); 

    if (read(fd, buffer, 10) != 10)
        oops(file, "Failed to read");

    printf(buffer);

    if (close(fd) == -1)
        oops(file, "Failed to close");
}

void write_before(const char* file)
{
    int fd;
    if ((fd = open(file, O_WRONLY)) == -1)
        oops(file, "Failed to open file");

    if (lseek(fd, 100, SEEK_END) == -1)
        oops(file, "Failed to lseek");

    if (write(fd, str, sizeof(str)) != sizeof(str))
        oops(file, "Failed to write");

    if (close(fd) == -1)
        oops(file, "Failed to close");
}

int main(int argc, char* argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s file", argv[0]);
        exit(1);
    }

//    read_before(argv[1]);
    write_before(argv[1]);
}

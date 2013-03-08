#include <fcntl.h>
#include <stdio.h>

char filename[] = "averyverylongfilenamethatmaybetruncatedbylinux";

int main(void)
{
    int fd;
    if ((fd = open(filename, O_WRONLY|O_CREAT|O_TRUNC, 0644)) == -1)
        perror("failed to create file");
    exit(1);
}

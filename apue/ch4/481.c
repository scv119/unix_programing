#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(int argc, char *argv[])
{
    umask(0); 
    if (creat("foo.out", RWRWRW) < 0) 
        perror("creat file error");
    umask(0077);
    if (creat("bar.out", RWRWRW) < 0)
        perror("creat file error");
    return 0;
}

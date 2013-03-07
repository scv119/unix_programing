#include <unistd.h>

int main(void)
{
    printf("hello world from process ID %d\n", getpid());
    printf("my parent process ID %d\n", getppid());
    return 0;
}

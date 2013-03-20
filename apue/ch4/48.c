#include <unistd.h>
#include <stdio.h>

void test_access();

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: %s path_to_file\n", argv[0]);
        exit(1);
    }
    
    test_access(argv[1], R_OK, "read");
    test_access(argv[1], W_OK, "write");
    test_access(argv[1], X_OK, "execute");
    test_access(argv[1], F_OK, "exist");

    return 0;
}

void test_access(const char *path, int amode, const char *msg)
{
    if (access(path, amode) < 0)
        fprintf(stderr, "failed to %s %s\n", msg, path);
    else
        printf("%s %s OK\n", msg, path);
    return;
}

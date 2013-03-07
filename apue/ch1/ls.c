#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[])
{
    DIR *dir_ptr;
    struct dirent *dirent_ptr;

    if (argc != 2) {
        fprintf(stderr, "usage: %s directory_name", argv[0]);
        exit(1);
    }

    if ((dir_ptr = opendir(argv[1])) == NULL) {
        fprintf(stderr, "can't open dir");
        perror(argv[1]);
        exit(1);
    }

    while ((dirent_ptr = readdir(dir_ptr)) != NULL)
        printf("%s \n", dirent_ptr -> d_name);

    closedir(dir_ptr);

    exit(0);
}

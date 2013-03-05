#include <stdio.h>
#include <sys/stat.h>
#include <time.h>

void show_info(const char*, const struct stat*);

int main(int argc, char* argv[])
{
    struct stat info; 

    if (argc > 1) {
        if (stat(argv[1], &info) == -1) 
            perror(argv[1]);
        else {
            show_info(argv[1], &info);
            return 1;
        }
    }

    return 1;
}

void show_info(const char* file, const struct stat* info_ptr)
{
    printf("mode: %o\n", info_ptr->st_mode);
    printf("links: %d\n", info_ptr->st_nlink);
    printf("user: %d\n", info_ptr->st_uid);
    printf("group: %d\n", info_ptr->st_gid);
    printf("size: %d\n", info_ptr->st_size);
    const char *ptr = ctime(&(info_ptr->st_mtime));
    printf("modtime: %s\n", ptr);
//    free(ptr);
    printf("name: %s\n", file);
}

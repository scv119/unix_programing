#include <dirent.h>
#include <stdio.h>

void do_ls(const char*);

int main(int argc, char *argv[])
{
    if (argc == 1)
        do_ls(".");
    else
        while (--argc) {
            printf("%s:\n", * (++argv));
            do_ls(*argv);
        }
    return 0;
}

void do_ls(const char* dirname)
{
    DIR* dir_ptr;
    struct dirent* dir_entry_ptr;

    if ((dir_ptr = opendir(dirname)) == NULL)
        fprintf(stderr, "Failed to open dir %s\n", dirname);
    else {
        while ((dir_entry_ptr = readdir(dir_ptr)) != NULL)
            printf("%s\n", dir_entry_ptr -> d_name);
        closedir(dir_ptr);
    }
}

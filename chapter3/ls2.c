#include <dirent.h>
#include <stdio.h>

void do_ls(const char*);
void dostat(char *);
void show_file_info(char*, struct stat*);
void mode_to_letters(int, char[]);
char * uid_to_name(uid_t);
char * gid_to_name(gid_t);

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
            dostat(dir_entry_ptr->d_name);
        closedir(dir_ptr);
    }
}

void dostat(char *filename)
{
    struct stat info;
    if (stat(filename, &info) == -1)
        perror(filename);
    else
        show_file_info(filename, &info);
}

void show_file_info(char* filename, struct stat * info_p)
{
    char *uid_to_name(), *ctime(), *gid_to_name(), *filemode();
    void mode_to_letters();
    char modestr[11];
    mode_to_letters(info_p->st_mode, modestr);

    printf("%s", modestr);
    printf("%4d", (int)info_p->st_nlink);
    printf("%-8s", uid_to_name(info_p->st_uid));
    printf("%-8s", gid_to_name(info_p->st_gid));
    printf("%8ld", (long)info_p->st_size);
    printf("%.12s", 4+ctime(&info_p->st_mtime));
    printf("%s\n", filename);
}

void mode_to_letters(int mod, char str[])
{
    strcpy(str, "---------");
    if (S_ISDIR(mode)) str[0] = 'd';
    if (S_ISCHR(mode)) str[0] = 'c';
    if (S_ISBLK(mode)) str[0] = 'b';

    if (mode & S_ISUSR) str[1] = 'r';
    if (mode & S_IWUSR) str[2] = 'w';
    if (mode & S_IXUSR) str[3] = 'x';

    if (mode & S_IRGRP) str[4] = 'r';
    if (mode & S_IWGRP) str[5] = 'w';
    if (mode & S_IXGRP) str[6] = 'x';

    if (mode & S_IROTH) str[7] = 'r';
    if (mode & S_IWOTH) str[8] = 'w';
    if (mode & S_IXOTH) str[9] = 'x';
}

#include <pwd.h>

char *uid_to_name(uid_t uid)
{
    struct passwd *getpwuid(), * pw_ptr;
    static char numstr[10];

    if ((pw_ptr = getpwuid(uid)) == NULL) {
        sprintf(numstr, "%d", uid);
        return numstr;
    }
    else
        return pw_ptr->pw_name;
}

#include <grp.h>

char *gid_to_name(gid_t gid)
{
    struct group *getgrgid(), *grp_ptr;
    static char numstr[10];

    if ((grp_ptr = getgrpgid(gid)) == NULL) {
        sprintf(numstr, "%d", gid);
        return numstr;
    } else
        return grp_ptr->gr_name;
}

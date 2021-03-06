#include <stdio.h>
#include <utmpx.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define SHOWHOST

void show_info(struct utmpx* record);

int main()
{
    struct utmpx current_record;
    int utmpx_fd;
    int record_len = sizeof(current_record);

    if ((utmpx_fd = open(_PATH_UTMPX, O_RDONLY)) == -1) {
        perror(_PATH_UTMPX);
        exit(1);
    }
    
    while (read(utmpx_fd, &current_record, record_len) == record_len)
        show_info(&current_record);
    close(utmpx_fd);
    
    return 0;
}

void show_info(struct utmpx* record)
{
    printf("%s", record->ut_user);
    printf(" ");
    printf("%s", record->ut_id);
    printf(" ");
    printf("%d", record->ut_type);
#ifdef SHOWHOST
    printf(" ");
    printf("%s", record->ut_host);
#endif
    printf("\n");
}

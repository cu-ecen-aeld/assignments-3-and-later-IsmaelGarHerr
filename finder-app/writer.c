#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <syslog.h>
#include <unistd.h>

#define ARGS_NUMBER     3U
#define OPERATION_ERROR -1

 int main ( char argc, char *argv[])
 {
    int   fd = 0;
    int   wr = 0;
    char* filePath;
    char* string;
    
    if(argc != ARGS_NUMBER)
    {
        printf("Usage: %s <path> <string>\n", argv[0]);
        exit(1);
    }
    else
    {
        filePath = argv[1];
        string   = argv[2];

        openlog("writer", LOG_PID | LOG_CONS, LOG_DEBUG);
        
        fd = open(filePath, O_WRONLY | O_CREAT | O_TRUNC, 0600);

        if(fd == OPERATION_ERROR)
        {
            syslog(LOG_ERR, "Failed to open file %s", filePath);
            perror("open");
            printf("File Not Open\n");
            exit(1);
        }
        else
        {
            wr = write(fd, string, strlen(string));

            if (wr == OPERATION_ERROR)
            {
                syslog(LOG_ERR, "Cannot write to file %s", filePath);
                printf("File Write NOT Success");
                exit(1);
            }
            else
            {
                syslog(LOG_DEBUG, "Write succesfully done to file %s", filePath);
                
            }
            
        }

        close(fd);
        closelog();
    }

    return 0;
 }

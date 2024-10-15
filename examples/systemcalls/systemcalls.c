#include "systemcalls.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>

#define TERMINATION_STATUS_SUCCESS 0u
#define TERMINATION_STATUS_FAILED  -1

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{

/*
 * TODO  add your code here
 *  Call the system() function with the command set in the cmd
 *   and return a boolean true if the system() call completed with success
 *   or false() if it returned a failure
*/
    bool retVal = false;
    int  cmdRet = 0;

    cmdRet = system(cmd);

    if(cmdRet == TERMINATION_STATUS_SUCCESS)
    {
        retVal = true;
    }
    else
    {
        /*retVal stays as FALSE*/
    }

    return retVal;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    int retVal = false;
    int status;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];

/*
 * TODO:
 *   Execute a system command by calling fork, execv(),
 *   and wait instead of system (see LSP page 161).
 *   Use the command[0] as the full path to the command to execute
 *   (first argument to execv), and use the remaining arguments
 *   as second argument to the execv() command.
 *
*/

    va_end(args);

    openlog("SysCalls do_exec()", LOG_PID | LOG_CONS, LOG_DEBUG);

    pid_t pid = fork();

    if(pid == TERMINATION_STATUS_FAILED)
    {
        syslog(LOG_ERR, "Can not start new child process");
    }
    else
    {
        syslog(LOG_INFO, "Child process started");
        int exec = execv(command[0], command);

        if(exec == TERMINATION_STATUS_FAILED)
        {
            syslog(LOG_ERR, "Can not execute command: %s", command[0]);
            exit(1);
        }
        else
        {
            wait(&status);
            if(status == TERMINATION_STATUS_SUCCESS)
            {
                syslog(LOG_INFO, "Child process finished successfully");
                retVal = true;
            }
            else
            {
                syslog(LOG_ERR, "Child Process not finished correctly");
            }
        }
    }

    closelog();
    return retVal;
}

/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/
bool do_exec_redirect(const char *outputfile, int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    int retVal = false;
    int status;
    int fd;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];


/*
 * TODO
 *   Call execv, but first using https://stackoverflow.com/a/13784315/1446624 as a refernce,
 *   redirect standard out to a file specified by outputfile.
 *   The rest of the behaviour is same as do_exec()
 *
*/

    va_end(args);

    openlog("SysCalls do_exec()", LOG_PID | LOG_CONS, LOG_DEBUG);

    fd = open(outputfile, O_WRONLY);

    if(fd == -1)
    {
        syslog(LOG_ERR, "Can not open file %s", outputfile);
    }
    else
    {
        if(dup2(fd, 1) < 0)
        {
            syslog(LOG_ERR, "Can not redirect stdout to file");
        }
        else
        {
            pid_t pid = fork();
            if(pid == TERMINATION_STATUS_FAILED)
            {
                syslog(LOG_ERR, "Can not start new child process");
            }
            else
            {
               syslog(LOG_INFO, "Child process started");
               int exec = execv(command[0], command);
               if(exec == TERMINATION_STATUS_FAILED)
               {
                   syslog(LOG_ERR, "Can not execute command: %s", command[0]);
                   exit(1);
               }
               else
               {
                   wait(&status);
                   if(status == TERMINATION_STATUS_SUCCESS)
                   {
                       syslog(LOG_INFO, "Child process finished successfully");
                       retVal = true;
                   }
                   else
                   {
                       syslog(LOG_ERR, "Child Process not finished correctly");
                   }
               }
            }
  
        }
    }

    
    closelog();
    return retVal;
}

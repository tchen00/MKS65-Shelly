#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <limits.h>
#include <pwd.h>

char * command_line();
char ** parse_args( char * line, char * limit );
int redirect_pipe(char ** args);
int find_redirect(char * args);
int redirect_input(char * line);
int redirect_output(char * line);
char * trim_white(char * str);
int main();

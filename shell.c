#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

char * command_line() {
  char *prompt = (char *)calloc(256,1);
  printf("$ " );
  fgets(prompt,256,stdin);
  prompt[strlen(prompt)-1] = 0;
  return prompt;
}

// adapted from previous assignment
char ** parse_args( char * line, char * limit ){
  char ** args = malloc(256);
  char * token;
  int i = 0;
  // counts number of tokens
  while (token){
    // all items on the command line are to be separated by a single space
    token = strsep(&line, limit);
    args[i] = token;
    i++;
  }
  return args;
}

int redirect_pipe(char ** args){
    /* TESTING PURPOSES
      printf("larg[0]: %s\n",args[0] );
      printf("arg[1]: %s\n",args[1] );
    */
    char * input  = args[0];
    char * output = args[1];
    char line[256];
    char cmd[256];
    FILE *read = popen(input,"r");
    while (fgets(line,256,read)) {
      line[sizeof(line)-1] = 0;
      strcat(cmd,line);
    }
    pclose(read);
    FILE *write = popen(output,"w");
    fprintf(write,"%s",cmd);
    pclose(write);
    return 0;
}

int find_redirect(char * args){
    if (strstr(args,"|")) return 1;
    if (strstr(args,">")) return 2;
    if (strstr(args,"<")) return 3;
    return 0;
}

int redirect_output(char * line){
    fflush(stdout);
    char ** arg = parse_args(line, ">");
    int file;
    file = open(arg[1], O_CREAT | O_WRONLY, 0644);
    dup(STDOUT_FILENO);
    dup2(file, STDOUT_FILENO);
    char ** args = parse_args(arg[0], " ");
    execvp(args[0], args);
    close(file);
    return 0;
}

int redirect_input(char * line) {
    fflush(stdout);
    char ** arg = parse_args(line, "<");
    fflush(stdout);
    char ** args = parse_args(arg[0], " ");
    int file = open(arg[1], O_RDONLY, 0644);
    dup(STDIN_FILENO);
    dup2(file, STDIN_FILENO);
    fflush(stdout);
    execvp(args[0], args);
    close(file);
    return 0;
}

char * white_space(char * str) {
    // if there is a white space before the string
    while (*str == ' ') {
        str++;
    }
    // if there is white space after the string
    int i = strlen(str)-1;
    for (; i > 1 ; i--){
        if (str[i] == ' ' || str[i] == '\n' ){
            str[i] = 0;
        }
        else {
            break;
        }
    }
    return str; // updated string
}

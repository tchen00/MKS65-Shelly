# Project 1: :shell:Shell[ing]:shell: out commands
### Description & Features of the Shell
This is my attempt at writing a bash shell.
It includes the following functional features:
- Reads a line at a time & parses the line to separate the command from its arguments. After this, it will fork and exec the command.
  - The parent process should wait until the exec'd program exits and then it should read the next command.
- Exit and cd are both implemented (not from the forked child process)
- Reads and separates multiple commands on one line
- Implements simple redirection using > (redirecting stdout) and < (redirecting stdin)
- Implement simple pipes using popen()
### Extra Features
- Compiles the make file :)

### Attempted but Unsuccessful Features
- Implementing multiple pipes
- Double redirection in the same line

### Bugs In the Program
- None during testing

### Function Header
shell.c
- contains all the helper functions that are essential for the shell to run
- `char * command_line()`
  -  Does not take any inputs, prints a shell prompt
  - will take in command line arguments from stdin and return them in an array made of char
- `char * parse_args()`
  - takes in inputs of char * line and char * limit
  - returns an array of strings/tokens separated based on delimiters
- `char * redirect_pipe()`
  - takes in input of char ** args and returns 0
  - given an array of strings, pipes arg[0], copies stdout into char array, pipes arg[1], copies the char array into input arg 1
- `char * find_redirect()`
  - takes in input char * args and will return int corresponding with special character
  - will return 1 if '|'
  - will return 2 if '>'
  - will return 3 if '<'
- `char * redirect_output()`
  - takes in input char * line and returns 0
  - takes a string and separates into the arguments, runs the first process and redirects stdout into the given file.
- `char * redirect_input()`
  - essentially the same as redirect_output except redirects towards stdin
- `char white_space()`
  - made to make testing WAY easier
  - takes in input of char * str and returns a string with unnecessary white space eliminated.

  main.c
  - contains the *drum roll please* main() function
  - handles everything you see after you run make run 

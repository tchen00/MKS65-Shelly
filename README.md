#Project 1: :shell:Shell[ing]:shell: out commands
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
- Handling white space

### Bugs In the Program
- None during testing

### Function Header

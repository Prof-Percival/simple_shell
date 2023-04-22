## Simple Shell Team Project

Project was completed using: <br/>
C language <br/>
Shell <br/>
Betty linter <br/>

General Requirement for project <br/>
All files are compiled on Ubuntu 20.04 LTS using gcc, using the options -Wall -Werror -Wextra -pedantic -std=gnu89<br/>
All files ends with a new line

A README.md file at the root of the folder of the project is mandatory<br/>
Used the Betty style to check using betty-style.pl and betty-doc.pl<br/>
Shell should not have any memory leaks<br/>
No more than 5 functions per file<br/>
All header files should be include guarded<br/>
Write a README with the description of the project<br/><br/>

Description<br/>
hsh is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them.

How hsh works<br/>
Prints a prompt and waits for a command from the user<br/>
It creates a child process in which the command is checked<br/>
Checks for built-ins, aliases in the PATH, and local executable programs<br/>
The child process is replaced by the command, which accepts arguments<br/>
When the command is done, the program returns to the parent process and prints the prompt<br/>
The program is ready to receive a new command<br/>
To exit: press Ctrl-D or enter "exit" (with or without a status)<br/>
Works also in non interactive mode<br/><br/>
Compilation<br/>
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

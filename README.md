# OS Assignment - 2
Written by Dheeraj Reddy Pailla and Anshul Gupta

## To run the shell, enter the following commands:
	1. make
	2. ./ash

MODULES:

1. main
This contains the driver program from which the program is executed.

2. ashLoop
This contains the infinite loop for the shell to run.

3. ashRead
This consists of the read function used continuously by ashLoop.

4. ashGetArgs
This tokenizes the input.

5. convertCWD
This converts the home directory to a '~'.

6. ash_ls
This implements ls command along with the flags -a and -l.

7. builtin
Implements built in commands cd, echo, pwd and calls ls function.

8. ash_pinfo
Implements pinfo command.

9. ashLaunch
Implements regular shell functions using exec*.

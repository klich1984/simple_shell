# SIMPLE SHELL
This program is a copy of the basic functions of a UNIX command line interpreter (shell).
It can run commands and builtins, handling errors and printing them.

## How to install?
It's really simple to install this simple shell (*wink wink*), you only need to clone this **repository** and compile all the *.c* files with the version 4.8.4 or up of gcc.

### Example:
`gcc *.c -o hsh`
That command would compile all the files that end in a *.c* to an executable called **hsh**
to run the shell it's as simple as running the executable with:
`./hsh`
And voilá, you have the Mini Shell up and running!

## How to use it?
It's the same as using the shell that you normally use. There's two modes on this shell **Interactive Mode** and **Non Interactive Mode**

### Interactive Mode
This mode is the most used, just open the executable (as showed before) and start typing commands, and thats it.
When you're done with the shell just use *Ctrl-D* or type *exit* and you will end the shell program.

### Non Interactive Mode
This mode is not so used, this mode consist in throwing files and text to the program without actually running it, *how it is done?*
You can send the program some text for it to execute using the command *echo* or giving it the contents of a file using *cat*, here are some examples:

### Examples:
**echo**
```
($) echo "ls -a" | ./hsh
(hsh$) . .. bin hello.c example.c
```
**cat**
```
($) cat example.txt
echo hello world
($) cat example.txt | ./hsh
(hsh$) hello world
```

**ps**
```
($) ps
  PID TTY          TIME CMD
10774 pts/3    00:00:01 bash
15211 pts/3    00:00:00 hsh
15230 pts/3    00:00:00 ps
```

**Made by:**
*Carlos Usuga Martinez*
*Juan Pablo Montoya*

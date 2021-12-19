# c_simple_pipe
A very simple implementation of a single pipe (2 processes)

This program (```src/pipe.c```) spawns two child processes connected with the pipe, created by the ```pipe()``` function from glibc. You need two pass two arguments in the command line - paths to executables for the first and the second child process in the pipe. The first process will be waiting for the input from ```stdin```, terminated with the ```\n``` char. The second process will write its output to ```stdout```.

For demonstration purposes I prepared two additional programs (```src/prog1.c``` and ```src/prog2.c```), automatically compiled by the Makefile and available under ```bin/prog1``` and ```bin/prog2```. The first one replaces every third char of the input string with ```b```, while the second one replaces all occurences of ```b``` with ```c```, so piping ```prog1``` with ```prog2``` will result with every third letter replaced by ```c```. There is also a sample input file ```data/input.txt``` containg only ```a``` letters, so you can clearly see that the pipe works.

Compilation: ```make``` and run ```./pipe <path_to_first_executable> <path_to_second_executable>```.

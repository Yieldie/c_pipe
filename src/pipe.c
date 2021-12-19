#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/**
 * Helper function - executes program under given path with stdin and stdout replaced by descriptors read_fd and write_fd 
 * respectively. Called from child process.
 */
void child_exec(char const *path, int read_fd, int write_fd);

int main(int argc, char **argv)
{
	int in_fd = 0, out_fd = 1;
	int pipefd[2];
	pid_t cpid;
	char const *executable[2];
	if(argc > 2) {
        	executable[0] = argv[1];
        	executable[1] = argv[2];
	} else {
		printf("Not enough arguments.");
		exit(EXIT_FAILURE);
	}

	if(pipe(pipefd) == -1) {
		perror("Failed to create a pipe.");
		exit(EXIT_FAILURE);
	}

	if((cpid = fork()) == -1) {
		perror("Failed to create a child process.");
		exit(EXIT_FAILURE);
	} else if(cpid == 0) {
		close(pipefd[0]); //close the unused end of pipe
		child_exec(executable[0], in_fd, pipefd[1]); //pass the writing end of the pipe as write_fd
	} 
	
	if((cpid = fork()) == -1) {
		perror("Failed to create a child process.");
		exit(EXIT_FAILURE);
	} else if(cpid == 0) {
		close(pipefd[1]); //close the unused end of pipe
		child_exec(executable[1], pipefd[0], out_fd); //pass the reading end of the pipe as read_fd 
	}

	close(pipefd[1]); //descriptors of the pipe are unused by parent
	close(pipefd[2]);
	waitpid(cpid, NULL, 0); //wait for the last child from the pipe
	return 0;
}

void child_exec(char const *path, int read_fd, int write_fd)
{
	//replace the descriptors
	if(read_fd != 0) {
		dup2(read_fd, 0);
		close(read_fd);
	}
	if(write_fd != 1) {
		dup2(write_fd, 1);
		close(write_fd);
	}
	execlp(path, (char *)NULL);
	//exec does not return, so the following lines will be reached only in case of error
	perror("Something went wrong.");
	exit(EXIT_FAILURE);
}

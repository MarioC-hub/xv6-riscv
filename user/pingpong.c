#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
	int i = 0;
 	char buf[1];
	buf[0] = '*';	

	int fds[2];
	int child_fds[2];
	pipe(fds); // initialize an array with 0 read, 1 write shared between child and parent process.
	pipe(child_fds);		

	int pid = fork(); // fork after creating the pipes, so we can share fds between child and parent process.
	if (pid == 0) {
		close(child_fds[0]);
		close(fds[1]);

		for(; i < 10; i++) {
			// child process
			int write_size = write(child_fds[1], buf, 1);

        	if (write_size <= 0) {
            	printf("child missed during write :'( \n");
        		return write_size;
			}

        	printf("pong %c \n", buf[0]);

        	int read_err = read(fds[0], buf, 1);

        	if (read_err <= 0) {
            	printf("child missed during read :'( \n");
        		return read_err;
			}
		}
	} else {
		// parent
		close(child_fds[1]);
		close(fds[0]);

		for(; i < 10; i++) {
		
			int read_size = read(child_fds[0], buf, 1);

			if (read_size <= 0) {
				printf("missed during read :'( \n");
				return read_size;
			}
			
			sleep(1); // forced preemption so printing comes out legible
			printf("ping %c \n", buf[0]);

			int write_err = write(fds[1], buf, 1);

			if (write_err <= 0) {
				printf("missed during write :'( \n");
				return write_err;
			}
		}
	}
}


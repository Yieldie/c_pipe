#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE	9
#define INTERVAL	3
#define NEW_CHAR	'b'

int main(void)
{
	int counter = 0;
	ssize_t bytes;
	char buf[BUF_SIZE];
	while((bytes = read(0, buf, BUF_SIZE)) > 0) {
		for(ssize_t i = 0; i < bytes; i++) {
			if(counter == INTERVAL - 1 && i < BUF_SIZE && buf[i] != '\n')
				buf[i] = NEW_CHAR;
			counter = (counter + 1) % INTERVAL;
		}
		write(1, buf, bytes);
		if(buf[bytes - 1] == '\n') {
			break;
		}
	}
	return 0;
}

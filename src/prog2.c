#include <stdio.h>
#include <unistd.h>

#define BUF_SIZE	10

int main(void)
{
	ssize_t bytes;
	char buf[BUF_SIZE];
	while((bytes = read(0, buf, BUF_SIZE)) > 0) {
		for(ssize_t i = 0; i < bytes; i++) {
			if(buf[i] == 'b')
				buf[i] = 'c';
		}
		write(1, buf, bytes);
		if(buf[bytes - 1] == '\n')
			break;
	}
	return 0;
}

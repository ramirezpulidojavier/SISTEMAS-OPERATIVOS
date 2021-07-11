#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
	

int main (int argc, char * argv[]) 
{

	struct flock cerrojo;
	int fd,i;

	for (i = 0 ; i < argc; i++){

		if((fd=open(argv[i], O_RDWR)) == -1){

			perror("open fails");
			continue;

		}
		
		cerrojo.l_type=F_WRLCK;
		cerrojo.l_whence=SEEK_SET;
		cerrojo.l_start=0;
		cerrojo.l_len=0;

		if((fcntl(fd, F_SETLKW, &cerrojo)) == -1){

			if(errno == EDEADLK){

				printf("interlocking\n");
			
			}

		}

		printf("join %d\n", getpid());
		sleep(10);
		printf("leave\n");

		cerrojo.l_type=F_WRLCK;
		cerrojo.l_whence=SEEK_SET;
		cerrojo.l_start=0;
		cerrojo.l_len=0;

	
	}	

	return 0;
}

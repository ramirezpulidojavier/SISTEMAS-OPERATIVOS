#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char * argv[]) 
{
	
	if(argc != 4 ){

		perror("Numero incorrecto de argumentos\n");
		exit(EXIT_FAILURE);

	}else{

		char *file = argv[3];
		char *command = argv[1];
		int fd;

		if(strcmp(argv[2], ">") == 0){

			fd=open(file,O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR);
			close(STDOUT_FILENO);
			fcntl(fd, F_DUPFD, STDOUT_FILENO );
		
		}else if(strcmp(argv[2] , "<") == 0){
		
			fd = open(file, O_RDONLY);
			close(STDIN_FILENO);
			fcntl(fd, F_DUPFD, STDIN_FILENO );				

		}

		execlp(command, "", NULL);
		close(fd);
		return 0;

	}
	
}

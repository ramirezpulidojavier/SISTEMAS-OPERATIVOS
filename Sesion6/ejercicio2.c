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

		char *command = argv[3];
		char *command2 = argv[1];

		if(strcmp(argv[2], "|") == 0){

			execlp(command2, command2, NULL);
			execlp(command, command, NULL);
			
		
		}
		
		return 0;

	}
	
}

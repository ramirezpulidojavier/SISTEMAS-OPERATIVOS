//tarea4.c
//Trabajo con llamadas al sistema del Subsistema de Procesos "POSIX 2.10 compliant"
//Prueba el programa tal y como está. Después, elimina los comentarios (1) y pruebalo de nuevo.

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{

	int i;
	pid_t pid=getpid();

	if(setvbuf(stdout,NULL,_IONBF,0)) {
		perror("\nError en setvbuf");
	}

	for (i=0; i < 5 && pid != 0; i++) {
	     	if ((pid= fork()) == -1) {
	     		printf("\nNo se pudo crear hijo %d",i);
	    		exit(-1);
		}
		
	} 

	if(pid==0){
		printf("Soy el hijo: %d \n",getpid());
		exit(0);
	}else{

		printf("Soy el padre: %d \n",getpid());
		while(i>0){

			pid=wait(NULL);
			i--;
			printf("Acaba de finalizar mi hijo con PID: %d \n",pid);
			printf("Solo me quedan %d hijos vivos\n",i);
		}		

	}

	exit(EXIT_SUCCESS);
}

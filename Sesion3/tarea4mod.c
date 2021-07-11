//tarea4.c
//Trabajo con llamadas al sistema del Subsistema de Procesos "POSIX 2.10 compliant"
//Prueba el programa tal y como está. Después, elimina los comentarios (1) y pruebalo de nuevo.

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int global=6;
char buf[]="cualquier mensaje de salida\n";


int main(int argc, char *argv[])
{

	if(argc<2){

		printf("Numero de argumentos incorrecto");
		exit(-1);
	
	}else{

		int var=atoi(argv[1]);
		pid_t pid;
		
		var=88;
		if(write(STDOUT_FILENO,buf,sizeof(buf)+1) != sizeof(buf)+1) {
			perror("\nError en write");
			exit(EXIT_FAILURE);
		}
		if(setvbuf(stdout,NULL,_IONBF,0)) {
			perror("\nError en setvbuf");
		}
		printf("\nMensaje previo a la ejecución de fork");

		if( (pid=fork())<0) {
			perror("\nError en el fork");
			exit(EXIT_FAILURE);
		}
		else if(pid==0) {  
			//proceso hijo ejecutando el programa
			if(var%2==0){

				printf("\nEl numero pasado como argumento es par");
	
			}else{

				printf("\nEl numero pasado como argumento es impar");

			}
		} else { //proceso padre ejecutando el programa
			if(var%4==0){

				printf("\nEl numero pasado como argumento es multiplo de 4");
	
			}else{

				printf("\nEl numero pasado como argumento no es multiplo de 4");

			}
		}		
		printf("\npid= %d, var= %d\n", getpid(),var);
		exit(EXIT_SUCCESS);

	}

}

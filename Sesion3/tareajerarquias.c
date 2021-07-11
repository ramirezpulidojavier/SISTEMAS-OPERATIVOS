//tarea4.c
//Trabajo con llamadas al sistema del Subsistema de Procesos "POSIX 2.10 compliant"
//Prueba el programa tal y como está. Después, elimina los comentarios (1) y pruebalo de nuevo.

#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{


pid_t childpid;
for (int i=1; i < 20; i++) {
     	if ((childpid= fork()) == -1) {
     		printf("\nNo se pudo crear hijo %d",i);
    		exit(-1);
	}     

    	printf("\npid= %d\n", getpid());

	if (childpid)
       		break;

	
} 
exit(EXIT_SUCCESS);
}

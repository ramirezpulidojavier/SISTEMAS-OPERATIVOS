/*
tarea1.c
Trabajo con llamadas al sistema del Sistema de Archivos ''POSIX 2.10 compliant''
Probar tras la ejecución del programa: $>cat archivo y $> od -c archivo
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
			*/
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>


int main(int argc, char *argv[])
{
int fd_origen,fd_salida;
int num_bloques=0;
char buffer[80];
int numbytes;

char str[500];

if(argc<2){

	fd_origen= STDIN_FILENO;

}else{
	fd_origen=open(argv[1], O_RDONLY);
	
	
}

if( (fd_salida=open("salida.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
		printf("\nError %d en open",errno);
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}

while((numbytes=read(fd_origen,buffer,80))>0){
		
		num_bloques++;

		sprintf(str, "\nAqui van los siguientes 80 Bytes del archivo pasado como argumento en el bloque %d\n", num_bloques);

		if(write(fd_salida, str , strlen(str)) != strlen(str) ) {
			perror("\nError al escribir el texto");
			exit(EXIT_FAILURE);
		}
		
		if(write(fd_salida, buffer , numbytes) != numbytes) {
			perror("\nError en primer write");
			exit(EXIT_FAILURE);
		}

	

	

}

}

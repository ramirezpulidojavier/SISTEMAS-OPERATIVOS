#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>




int main(void)
{

	//ABRE DOS CAUCES FIFO CON NOMBRE

	int fd;
	char buffer[80];// Almacenamiento del mensaje del cliente.
	int leidos, escritos;

	//Crear el cauce con nombre (FIFO) si no existe
	umask(0);
	mknod(ARCHIVO_FIFO,S_IFIFO|0666,0);
	//también vale: mkfifo(ARCHIVO_FIFO,0666);

	//Abrir el cauce para lectura-escritura
	if ( (fd=open(ARCHIVO_FIFO,O_RDWR)) <0) {
	perror("open");
	exit(EXIT_FAILURE);
	}

	//Aceptar datos a consumir hasta que se envíe la cadena fin
	while(1) {
		leidos=read(fd,buffer,80);
		if(strcmp(buffer,"fin")==0) {
		
			close(fd);
		
		}
		printf("\nMensaje recibido: %s\n", buffer);
	}


	//Intentar abrir para escritura el cauce FIFO
	if( (fd=open(ARCHIVO_FIFO,O_WRONLY)) <0) {
		perror("\nError en open");
		exit(EXIT_FAILURE);
	}

	//Escribir en el cauce FIFO el mensaje introducido como argumento
	if( (write(fd,argv[1],strlen(argv[1])+1)) != strlen(argv[1])+1) {
		perror("\nError al escribir en el FIFO");
		exit(EXIT_FAILURE);
	}

	close(fd);

	//ABRE DOS CAUCES FIFO CON NOMBRE



	

	return EXIT_SUCCESS;

}





























SERVIDOR.C

SE EJECUTA: ./SERVIDOR "FILEFIFO" & 

1º SE CREA FIFO DE ENTRADA Y DE SALIDA :
	mkfifo(argv[1] + "e") entrada
	mkfifo(argv[1] + "s") salida

crear archivo de bloqueo: open(archivo_bloqueo, O_CREAT...);
fde=open
fds=open

while(read(fde)){

	//me llega una peticion de un cliente que quiere imprimir algo por pantalla
	pid = fork(); //es el proxy (pid devuelve un 0)
	if(pid == 0){

		getpid(); //da su pid y lo escribe aqui: mkfifo(argv[1] + "s") salida
		execlp(); //ejecuta el archivo proxy.c

	}
	
	

}





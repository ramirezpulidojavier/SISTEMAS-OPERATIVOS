//servidor.c 

#include <fcntl.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 

int main(int argc, char *argv[]){ 

	if (argc < 2) { 
		printf ("Server: Formato: server <nombre_fifo>\n");
		exit(1); 
	} 
	int FIFO_entrada,FIFO_salida,FIFO_proxy; 
	pid_t pid; //Buffer para nombres FIFO cliente­servidor y servidor­cliente 
	char nombrefifoe[50], nombrefifos[50]; 
	char nombre_fifo_proxy[80]; //Buffer para nombres FIFO cliente­proxy 

	int leidos,pidCliente; 
	
	sprintf(nombrefifoe,"%se",argv[1]);
	sprintf(nombrefifos,"%ss",argv[1]); 

	//Crear dos cauces FIFO para comunicar el servidor con los clientes 
	//Se crea uno para salida y otro para entrada 
	umask(0); 

	mknod(nombrefifoe,S_IFIFO|0666,0); //Cauce entrada
	mknod(nombrefifos,S_IFIFO|0666,0); //Cauce salida 



	//Abrir los cauces para lectura­escritura 
	if ( (FIFO_entrada=open(nombrefifoe,O_RDWR)) <0){ 
		printf("Error al abrir FIFO_entrada: %s",nombrefifoe);
		exit(-1);
	} 

	if ( (FIFO_salida=open(nombrefifos,O_RDWR)) <0) { 
		printf("Error al abrir FIFO_salida: %s",nombrefifos);
		exit(-1); 
	} 

	//Bloque de lectura de datos por parte de los proxys

	//El servidor esta continuamente comprobando que haya nuevos mensajes en el 

	//FIFO_entrada, que es por donde los clientes envian sus pid's 
	//Cuando el servidor lee un pid muestra un mensaje en pantalla: 
	//"Mensaje recibido: <pidCliente>" 
	//Y lanza un hijo para atender a dicho cliente. (El hijo ejecuta el proxy) 
	while(1) { 
		leidos=read(FIFO_entrada,&pidCliente,sizeof(int));
		printf("\nRecibido cliente con PID: %d\n", pidCliente); 
		if ((pid = fork()) == -1) { 
			perror ("Lanzar Proxy"); 
			exit(1); 
		} 
		
		if (pid == 0 ) { //Codigo del hijo 
			
			pid_t pid_proxy = getpid(); 
	
			//Indicamos al cliente cual es el pid del proxy para que sepa como se 
	
			//llama el FIFO por el que tiene que comunicarse con el proxy 

			//a saber el FIFO se llama: "fifo.<pid_proxy>" 
			
			write(FIFO_salida,&pid_proxy,sizeof(int)); 
		
			//Creamos el FIFO "fifo.<pid_proxy>" 
	
			sprintf(nombre_fifo_proxy,"fifo.%d",getpid()); 

			umask(0);
			mknod(nombre_fifo_proxy,S_IFIFO|0666,0);  //Aqui creamos el FIFO 

			//Ejecutamos el codigo del proxy 
			execlp("./proxy","proxy",NULL); 

			exit(0); 
		}

	} 

}

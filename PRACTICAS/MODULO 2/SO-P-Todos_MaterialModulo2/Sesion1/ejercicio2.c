//PRÁCTICA1 Módulo II Ejercicio 2
//María Aguado

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main (int argc, const char *argv[]){
	int fd1, fd2;

	char buf[80];
	int num=0;
	char frase[100];


	if (argc!=1 && argc!=2){
		printf ("\nError %d en el número de argumentos", errno);
		perror("\nError en argumentos");
		exit(-1);
	}


		
	if (argc==1)
		fd1=STDIN_FILENO;
		
		
	else if ((fd1=open(argv[1], O_RDONLY))<0){
				printf ("\nError %d en el open1", errno);
				perror("\nError en open");
				exit(-1);
		}



	if ((fd2 = open("salida.txt", O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR))<0){
		printf ("\nError %d en el open de salida\n", errno);
		perror("\nError en open");
		exit(-1);
		}

	int leidos;
	while ((leidos=read (fd1, buf, 80))!= 0){
		
		sprintf( frase, "\nBloque: %d\n", num);
		if (write (fd2, frase, strlen(frase)*sizeof(char) )!=strlen(frase)*sizeof(char)){
			perror("\nError en  write\n");        
			exit(-1);
		}
		
		if (write(fd2, buf, leidos)!=leidos){
			
			perror("\nError en  write");        
			exit(-1);
		}
		printf("%s", buf);
		

		num++;
	}


		if (fd1!=STDIN_FILENO)
			close(fd1);
		close(fd2);

		return 0;
	}























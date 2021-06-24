/**
 * @file ejercicio4.c
 */

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    struct flock cerrojo;
    int fd;

    // Este archivo será el que usemos para comprobar bloqueos
    //           vvvvvvvvvvvvvvvvvvvvv
    if ((fd = open("./peaso_demonio.pid", O_RDWR | O_CREAT)) == -1)
    { //abrimos el archivo para escritura
        perror("Error al crear el archivo temporal");
        return 1;
    }
    //creamos la estructura del cerrojo
    cerrojo.l_type = F_WRLCK; //cerrojo para escritura
    cerrojo.l_whence = SEEK_SET;
    cerrojo.l_start = 0; //archivo completo
    cerrojo.l_len = 0;

    // Comprobamos que no está activo el archivo
    if ((fcntl(fd, F_SETLK, &cerrojo)) == -1)
    {
        printf("Se ha detectado otra instancia en ejecución. Cerrando...\n");
        sleep(1);
        return 1;
    }

    // printf as fast as possible
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("El programa se estará ejecutando durante 15 segundos. Intenta abrir otra instancia");
    sleep(15);

    // Tras los 15 segundos, procedemos a desbloquear
    cerrojo.l_type = F_UNLCK;
    cerrojo.l_whence = SEEK_SET;
    cerrojo.l_start = 0;
    cerrojo.l_len = 0;

    if (fcntl(fd, F_SETLKW, &cerrojo) == -1)
        perror("Error al desbloquear");

    return 0;
}

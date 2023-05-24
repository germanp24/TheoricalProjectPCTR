#include <iostream>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "Puente.h"
#include "Coche.h"

#define NUM_COCHES 10 /* Numero de coches para la simulación */

static void *coche_func (void *arg); /* Puntero a la función que ejecutará cada hilo/thread */

int main (int argc, char *argv[]){

    srand((int) getpid()); /* "Semilla plantada" para generar números aleatorios*/
    
    /**** POR HACER ****/
    // Puente *puente = new Puente(...);/* Monitor que controla el puente, recibe la cadena de caracteres "N->S" o bien "S->N" como sentido del "turno inicial" que empezará atravesando el puente */
    Puente *puente = new Puente("N->S");
    					 
    pthread_t hilosCoches[NUM_COCHES];  /* Array para los NUM_COCHES hilos que se crearán después*/

    int r=rand() % 2; /* Genera tiempo aleatorio para ir creando hilos "coche" */ 
    int i;
    /* Creacion de los hilos para los coches*/
    for (i=0; i<NUM_COCHES; i++){   
        sleep(r+1); /* Tiempo de espera hasta crear el próximo hilo */
        
        /**** POR HACER ****/
        // pthread_create(...); /* Crear hilo que ejecute concurrentemente la función coche_func()*/
        /* pthread_create debe recibir como parámetro el puntero de función void *coche_func() */
        pthread_create(&hilosCoches[i], NULL, coche_func, (void *) puente);

    }

    /* Esperar terminación de los hilos "coche" */
    for (i=0; i<NUM_COCHES; i++) 
        pthread_join(hilosCoches[i], NULL);

    delete puente; /* Destruye el monitor */

    return EXIT_SUCCESS;
}

/* Función que ejecuta cada hilo... */
static void *coche_func (void *arg){

    /**** POR HACER ****/	
    // Puente *puente = ... /* Obtener una referencia del puente a partir del puntero void *arg */
    Puente *puente = static_cast<Puente *>(arg);
    
    /* Desde la función coche_func() que ejecuta cada hilo se declara e inicializa un objeto de clase coche (Coche *coche) que recibe tres atributos:
       i)un identificador entero (por ejemplo el propio id del thread);
       ii)una referencia/puntero al monitor (Puente *puente); y, por último,
       iii)se asigna un sentido al coche mediante la cadena de caracteres "N->S" ó "S->N" dependiendo de si su identificador es par o impar */
    const char *sentido = (gettid()%2==0) ? N_S : S_N;
    Coche *coche = new Coche ((int)gettid(), puente, sentido);
    coche->circula(); /* Desde este hilo/thread se invoca el método circula() del objeto de clase Coche */
    
    /* Cuando ya el objeto coche (Coche *coche) termina de circular (y ha atravesado el puente) es borrado de memoria con delete() */
    delete coche;
    return (void *) true;
}
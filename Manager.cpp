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
    
    Puente *puente = new Puente("N->S");
    					 
    pthread_t hilosCoches[NUM_COCHES];  /* Array para los NUM_COCHES hilos que se crearán después*/

    int r=rand() % 2; /* Genera tiempo aleatorio para ir creando hilos "coche" */ 
    int i;
    
    /* Creacion de los hilos para los coches*/
    for (i=0; i<NUM_COCHES; i++){   
        sleep(r+1); /* Tiempo de espera hasta crear el próximo hilo */
        
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

    Puente *puente = static_cast<Puente *>(arg);
    
    const char *sentido = (gettid()%2==0) ? N_S : S_N;
    Coche *coche = new Coche ((int)gettid(), puente, sentido);
    coche->circula(); /* Desde este hilo/thread se invoca el método circula() del objeto de clase Coche */
    
    delete coche;
    return (void *) true;
}
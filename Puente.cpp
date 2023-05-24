#include "Puente.h"

/* Definición de los miembros de la clase Puente que implementa el monitor */

Puente::Puente(char * turnoInicial): /* Constructor */
    _numCochesCruzandoEnTurno(0), /* Número de coches que están cruzando el puente en un momento dado. Se inicializa a 0 */
    _numCochesEsperandoTurno(0)   /* Números de coches bloqueados en el otro extremo del puente en un momento dado, esperando su turno */
{
    this->_turno = turnoInicial; /* turno "N->S" ó "S->N" */
    pthread_mutex_init(&_mutex, NULL); /* Se inicializan el mutex y las variables de condición */
    pthread_cond_init(&_synchroN_S, NULL); 
    pthread_cond_init(&_synchroS_N, NULL); 
}

Puente::~Puente(){ 	/* Destructor */
    pthread_mutex_destroy(&_mutex); /* Se destruye el mutex y las variables de condición */
    pthread_cond_destroy(&_synchroN_S); 
    pthread_cond_destroy(&_synchroS_N); 
}

void Puente::printPuente(char *cadena) {
    printf("Puente: -> %s\n", cadena);
}

void Puente::darPasoCochesN_S() { 

   pthread_mutex_lock(&_mutex); // Block mutex to enter critical section
   // START OF THE CRITICAL SECTION

   // Compare turn with N_S, if not equal then wait
    while(strcmp(_turno, N_S) != 0) {
         _numCochesEsperandoTurno++;    // Increment waiting cars
         pthread_cond_wait(&_synchroN_S, &_mutex);  // Block thread until condition is true
    }

    // The thread receives the turn and starts crossing the bridge
    _numCochesCruzandoEnTurno++;    // Increment cars crossing the bridge

    // END OF THE CRITICAL SECTION
    pthread_mutex_unlock(&_mutex); // Unlock mutex to exit critical section
} 

void Puente::darPasoCochesS_N(){

 /* Esta función es el caso opuesto/contrario a la función anterior darPasoCochesN_S() */
    pthread_mutex_lock(&_mutex); /* Poner cerrojo/lock */
        while( strcmp(_turno,S_N) !=0 ){/* Todavía no se le puede dar el paso...*/

            numCochesEsperandoTurno++; // Increment waiting cars
            pthread_cond_wait(&_synchroS_N, &_mutex); // Block thread until condition is true

        }
        
    _numCochesCruzandoEnTurno++; // Increment cars crossing the bridge
    pthread_mutex_unlock(&_mutex); /* Quitar cerrojo/lock */
}

void Puente::descontarYComprobarSiCerrarPasoN_S(){
    pthread_mutex_lock(&_mutex); /* Poner cerrojo/lock */
        /* Descontar el coche que abandona el puente y comprobar si es el último*/
        if( --_numCochesCruzandoEnTurno == 0 ){
            _turno=(char *) S_N; /* Turno para el otro sentido ("S->N") */
            while(_numCochesEsperandoTurno > 0){             	
                _numCochesEsperandoTurno--;
                /* Hacer, al menos tantos signals como coches hay bloqueados esperando su turno 
            	en sentido contrario */
                pthread_cond_signal(&_synchroS_N); 
            }
        }
    pthread_mutex_unlock(&_mutex); /* Quitar cerrojo/lock */
}

void Puente::descontarYComprobarSiCerrarPasoS_N(){
    pthread_mutex_lock(&_mutex); /* Poner cerrojo/lock */
        /* Descontar el coche que abandona el puente y comprobar si es el último*/
        if( --_numCochesCruzandoEnTurno == 0 ){
            _turno=(char *) N_S; /* Turno para el otro sentido ("N->S") */
            while(_numCochesEsperandoTurno > 0){ 
                _numCochesEsperandoTurno--;
                pthread_cond_signal(&_synchroN_S);
            }
        }
    pthread_mutex_unlock(&_mutex); /* Quitar cerrojo/lock */
}
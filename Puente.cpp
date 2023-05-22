#include "Puente.h"

/* Definición de los miembros de la clase Puente que implementa el monitor */

Puente::Puente(char * turnoInicial): /* Constructor */
    _numCochesCruzandoEnTurno(0), /* Número de coches que están cruzando el puente en un momento dado. Se 					  inicializa a 0 */
    _numCochesEsperandoTurno(0)   /* Números de coches bloqueados en el otro extremo del puente en un momento, 					  dado, esperando su turno */
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
    
    /**** POR HACER ****/
    /* 1) Se debe crear una zona que garantice la exclusión mutua haciendo uso de las primitivas de lock/unlock 	del mutex. Dentro de esa zona de exclusión mutua:
    *     2) Mientras la cadena _turno NO sea igual al sentido "N->S":
    *	    2.1) Se incrementa en uno _numCochesEsperandoTurno (esto significa que hay un nuevo coche esperando el
    *	         turno para cruzar desde el otro extremo)
    *	    2.2) Se bloquea el hilo que representa el coche con la primitiva pthread_cond_wait() y, en este caso,
    *	         con el puntero de la variable de condición _synchroN_S y el puntero del _mutex.
    *  3) Fuera del bucle while, este punto se alcanza, bien si no se cumple la condición del bucle anterior,
    *     esto es: el turno del coche que pide paso coincide con el actual del Puente ("N->S"); o bien si el hilo
    *	  que representa el coche que, permanecía bloqueado por el wait y la variable de condición _synchroN_S
    *     (punto 2.2), ahora "recibe paso" porque el puente se ha quedado vacio, dejando circular a los coches 
    * 	  en el sentido contrario (esto es de "S->N"). Lo anterior implica la realización de llamadas a la primitiva
    *     pthread_cond_signal(&_synchroN_S) desde otra parte/operación del monitor Puente.
    *	  El coche "empieza a cruzar" de modo que antes de hacer el unlock al mutex hay que incrementar en
    *     uno la variable que representa el "número de coches cruzando en turno"		  
    */
} 

void Puente::darPasoCochesS_N(){
 /* Esta función es el caso opuesto/contrario a la función anterior darPasoCochesN_S() */
    
 // pthread_mutex_lock(&_mutex); /* Poner cerrojo/lock */
        while( strcmp(_turno,S_N)!=0 ){/* Todavía no se le puede dar el paso...*/
             /**** POR HACER ****/
             // ... (una sentencia aquí en base a lo indicado en 2.1)
             pthread_cond_wait(&_synchroS_N,&_mutex);
        } /* Fin while */
        /**** POR HACER ****/
        // Aquí falta sentencia para incrementar en uno el "número de coches cruzando en turno"
 // pthread_mutex_unlock(&_mutex); /* Quitar cerrojo/lock */
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
                /* Hacer, al menos tantos signals como coches hay bloqueados esperando su turno 
                en el sentido contrario */
                pthread_cond_signal(&_synchroN_S);
            }
        }
    pthread_mutex_unlock(&_mutex); /* Quitar cerrojo/lock */
}

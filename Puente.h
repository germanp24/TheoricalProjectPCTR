#ifndef __PUENTE_H__
#define __PUENTE_H__

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <math.h>
#include <unistd.h>

#define N_S "N->S"
#define S_N "S->N"

class Puente {
    public:
    	
    	/* Constructor */
    	/* Monitor que controla el puente, recibirá la cadena de caracteres "N->S" o bien "S->N" como sentido 
    	del "turno inicial" que empezará atravesando el puente */
        Puente( char *turnoInicial);

    	/* Destructor */
        ~Puente ();

	/* Operaciones del monitor. Programadas para ejecutarse en términos de exlusión mutua*/
        void printPuente(char *cadena);
        void darPasoCochesN_S(); 
        void darPasoCochesS_N();
        void descontarYComprobarSiCerrarPasoN_S();
        void descontarYComprobarSiCerrarPasoS_N();

    private:
    	/* Variables del monitor */
        char *_turno; /* turno "N->S" ó "S->N" */
        int _numCochesCruzandoEnTurno;
        int _numCochesEsperandoTurno;
        
        /* Mutex para garantizar el acceso en términos de exclusión mutua en las operaciones del monitor Puente */
        pthread_mutex_t _mutex; 
        
        /* Variables de condición necesarias para sincronizar los hilos "Coche" y "detenerlos/bloquearlos", si están 		cruzando coches en sentido contrario o "darles paso", si el último coche en sentido contrario ya atravesó
        el puente */
        pthread_cond_t _synchroN_S;
        pthread_cond_t _synchroS_N;
};

#endif

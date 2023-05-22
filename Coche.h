#ifndef __COCHE_H__
#define __COCHE_H__

#include "Puente.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#define N_S "N->S"   /* Constante */
#define S_N "S->N"
#define MAX_TIME 10  /* Constante que define un "tiempo máximo" utilizado durante la simulación de 				circulación de un coche */

class Coche {
    public:

        Coche (int id, Puente* puente, const char *sentido); /* Constructor */

        ~Coche (); /* Destructor */

        void printCoche(const char *cadena);

        void circula(); /* Simula todo la actividad de circulación que realiza el coche. Desde su 				llegada al puente, su espera para "obtener paso" (y poder atravesarlo), el
        		tiempo cruzando el puente, así como cuando lo abandona. Internamente
        		realiza llamadas al monitor Puente */

    private:
        int _id;	/* Identicador del objeto Coche */
        Puente *_puente; /* Un objeto Coche tiene una referencia al monitor "Puente" */ 
        const char *_sentido;  /* "N->S" ó "S->N" */    
};
#endif

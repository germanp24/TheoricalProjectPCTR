#include "Coche.h"

/* Constructor */
Coche::Coche(int id, Puente* puente , const char *sentido){
    this->_id=id;
    this->_puente = puente;
    this->_sentido = sentido;
    srand( (int) getpid() ); /* "Semilla plantada" para generar números aleatorios */
}

/* Destructor */
Coche::~Coche(){}

void Coche::printCoche(const char *cadena) {
    printf("Coche: %d -> %s para atravesarlo de %s\n", _id, cadena, _sentido);
}

void Coche::circula(){
    sleep( 1 + rand()%MAX_TIME ); /* Tiempo aleatorio entre 1 y MAX_TIME segundos para llegar al puente */
    printCoche("llega al puente");
    
    /* Invocar operación específica del monitor Puente con la que el coche "solicita paso" según el sentido con el 	que desea atraversarlo. Esta operación es bloqueante si ya están atravesando coches en sentido contrario */
    if( strcmp(_sentido, N_S) == 0 ) /* Si el sentido con el que desea atravesar el puente este coche es N->S */
	/**** POR HACER ****/
        // _puente->... ; 
    else if( strcmp(_sentido, S_N) == 0 )
    	/**** POR HACER ****/
        // _puente->... ; 
    
    /* Si se alcanza este punto del código el coche atravesará el puente en el sentido deseado */
    printCoche("esta cruzando el puente al que llegó");
    sleep( 1 + rand()%MAX_TIME ); /* Tiempo aleatorio entre 1 y MAX_TIME segundos para cruzar/atravesar al puente */
    
    printCoche("terminó de cruzar el puente al que llegó");

    /* Invocar la operación específica del monitor Puente con la que el coche indica al monitor que ya ha cruzado 
     el puente en un determinado sentido, además, en esa operación del monitor Puente se actualiza el número de
     coches restantes atravesando el puente y, si es el último coche cruzando en ese sentido, se permite que los 
     que están esperando en sentido contrario comiencen a cruzar ... */
    if( strcmp(_sentido, N_S) == 0 ) 
    	/**** POR HACER ****/
        // _puente->... ; 
    else if( strcmp(_sentido, S_N) == 0 )
        /**** POR HACER ****/
        // _puente->... ; 
}

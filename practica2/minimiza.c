#include <stdio.h>
#include <stdlib.h>

#include "minimiza.h"
#include "transforma.h"

AFND * AFNDMinimiza(AFND * afnd){
    AFND * afd;

    /* Hacemos el automata determinista por si acaso
     * y eliminamos los estados no accesibles y no productivos */
    afd = AFNDTransforma(afnd);

    return afd
}


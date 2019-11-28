#include <stdio.h>
#include <stdlib.h>

#include "minimiza.h"
#include "transforma.h"

int id = 0;
int num_creados = 0;

/* Compprueba si un subestado esta dentro de un estado (clase)
 * Devuelve 1 si true y 0 si false */
int subestado_en_estado(Estado estado, int subestado){
    int i;

    for(i = 0; i < estado.num_estados; i++){
        if(estado.estados[i] == subestado){
            return 1;
        }
    }
    return 0;
}

AFND * AFNDMinimiza(AFND * afnd){
    AFND * afd;
    Estado nuevos_estados[MAX_ESTADOS];
    int i;
    int num_estados, tipo_estado;

    /* Hacemos el automata determinista por si acaso
     * y eliminamos los estados no accesibles y no productivos */
    afd = AFNDTransforma(afnd);
    num_estados = AFNDNumEstados(afd);

    /* Separamos en dos estados indistiguibles los estados finales y no finales */
    inicializar_estado(nuevos_estados[num_creados])
    inicializar_estado(nuevos_estados[num_creados])
    for(i = 0; i < num_estados; i++){
        tipo_estado = AFNDTipoEstadoEn(afd, i);
        if(tipo_estado == 1 || tipo_estado == 2){
            /* Clase con los estados finales */
            insertar_estado(nuevos_estados[0], i);
        } else {
            /* Clase con los estados no finales */
            insertar_estado(nuevos_estados[1], i);
        }
    }


    return afd;
}


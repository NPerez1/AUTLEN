#include <stdio.h>
#include <stdlib.h>

#include "transforma.h"

#define COMPLETO 1
#define NO_COMPLETO 0

typedef struct trans {
    int state;
    int status;
};


AFND * AFNDTransforma(AFND * afnd){
    int afndEstados = AFNDNumEstados(afnd);
    int afndNumSim = AFNDNumSimbolos(afnd); 
    int i , j, k;
    int lambda_states[afndEstados][afndEstados], table_states[afndEstados][afndEstados];
    struct trans * trans_table[afndNumSim];

    if(!afnd){
        return NULL;
    }

    for(i = 0; i < afndEstados; i++)
        for(j = 0; j < afndEstados; j++)
            lambda_states[i][j] = AFNDCierreLTransicionIJ(afnd, i, j);
    

    for(i = 0; i < afndEstados; i++)
        for(j = 0; j < afndEstados; j++)
            for(k = 0; k < AFNDNumSimbolos(afnd); k++)
                if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, i, k, j))    
                    table_states[i][k] = j;

}

int comprueba_fin(struct trans * trans_table[]){
    return -1;
}
#include <stdio.h>
#include <stdlib.h>

#include "transforma.h"
#include <string.h>

#define COMPLETO 1
#define NO_COMPLETO 0
#define MAX_NAME 40

typedef struct _Trans {
    char name[MAX_NAME];
    int id;
    int * trans;
    int * states;
    int status;
} Trans;

int id = 0;

Trans crearTrans(const AFND * afnd){
    Trans trans;
    int i, numSimbolos;

    trans.id = id;
    id++;
    numSimbolos = AFNDNumSimbolos(afnd);
    trans.trans = (int*)malloc(numSimbolos * sizeof(int));
    for(i = 0; i < numSimbolos; i++){
        trans.trans[i] = -1;
    }
    trans.status = NO_COMPLETO;
}

void anadirEstado(Trans* trans, int transId, int simbolo){
    trans->trans[simbolo] = transId;
}


AFND * AFNDTransforma(AFND * afnd){
    int afndEstados = AFNDNumEstados(afnd);
    int afndNumSim = AFNDNumSimbolos(afnd); 
    char name[MAX_NAME], temp;
    int i , j, k, st, index, flag;
    char name[MAX_NAME] = "";
    int estados_tmp[afndEstados];
    int lambda_states[afndEstados][afndEstados], table_states[afndEstados][afndEstados];
    Trans trans_table[afndNumSim];

    if(!afnd){
        return NULL;
    }

    /* Extraemos todas las transiciones lambdas en una tabla */
    for(i = 0; i < afndEstados; i++)
        for(j = 0; j < afndEstados; j++)
            lambda_states[i][j] = AFNDCierreLTransicionIJ(afnd, i, j);

    /* Creamos la primera transición partiendo del estado final */
    st = AFNDIndiceEstadoInicial(afnd);
    index == 0;
    trans_table[index] = crearTrans(afnd);

    /* Inicializamos tabla de estamos temporales */
    for(i = 0; i < afndEstados; i++){
        estados_tmp[i] = -1;
    }

    /* Recorremos iterativamente las transiciones dentro de la tabla de transiciones */
    while(comprueba_fin(trans_table)){
        /* Recorremos todos los simbolos del lenguaje */
        for(j = 0; j < AFNDNumSimbolos(afnd); j++)
        {
            /* Comprobamos si hay transiciones  */
            for(k = 0, i = 0; k < afndEstados; k++)
            {
                if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, st, j, k)){
                    estados_tmp[i]= k;
                    i++;
                }
            }
            if(i>0)
            {
                strcpy(name, "");
                for(; i>=0; i--){
                    sprintf(temp, "q%d", estados_tmp[i]);
                    strcat(name, temp);
                }
                flag = -1;
                for(i = 0; i <= index; i++){
                    if(strcmp(trans_table[i].name, name)){
                        flag = i;
                        break;
                    }
                }
            }
            for(i = 0; i < afndEstados; i++){
                estados_tmp[i] = -1;
            }
        }
    }
    

}

int comprueba_fin(Trans trans_table[]){
    return -1;
}

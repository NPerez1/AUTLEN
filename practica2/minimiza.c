#include <stdio.h>
#include <stdlib.h>

#include "minimiza.h"
#include "transforma.h"

int id = 0;
int num_creados = 0;

/* Busca a donde transiciona un estado con un simbolo dado
 * Devuelve id del estado o -1 */
int buscar_trans(int estado, int simb, AFND * afd){
    int j;

    for(j = 0; j < AFNDNumEstados(afd); j++){
        if(AFNDTransicionIndicesEstadoiSimboloEstadof(afd, estado, simb, j) == 1){
            return j;
        }
    }
    return -1;
}

AFND * AFNDMinimiza(AFND * afd){
    int i, j, k, tipo1, tipo2, changed=1;
    int num_estados, num_simbolos, salida1, salida2;
    int tabla_distinguibles[20][20];

    /* Hacemos el automata determinista por si acaso
     * y eliminamos los estados no accesibles y no productivos */
    num_estados = AFNDNumEstados(afd);
    num_simbolos = AFNDNumSimbolos(afd);

    /*
     * TABLA
     */

    for(i=1; i < num_estados; i++){
        for(j=0; j < i; j++){
            tipo1 = AFNDTipoEstadoEn(afd, i);
            tipo2 = AFNDTipoEstadoEn(afd, j);
            if(tipo1 == FINAL || tipo1 == INICIAL_Y_FINAL){
                if(tipo2 == FINAL || tipo2 == INICIAL_Y_FINAL){
                    tabla_distinguibles[i][j] = 0;
                }
                else{
                    tabla_distinguibles[i][j] = 1;
                }
            }
            else{
                if(tipo2 == FINAL || tipo2 == INICIAL_Y_FINAL){
                    tabla_distinguibles[i][j] = 1;
                }
                else{
                    tabla_distinguibles[i][j] = 0;
                }
            }
        }
    }

    while(changed==1){
        changed=0;
        for(i=1; i < num_estados; i++){
            for(j=0; j < i; j++){
                if(tabla_distinguibles[i][j] == 0){
                    for(k=0; k < num_simbolos; k++){
                        salida1 = buscar_trans(i, k, afd);
                        salida2 = buscar_trans(j, k, afd);
                        if(salida1 < salida2){
                            if(tabla_distinguibles[salida2][salida1] == 1){
                                tabla_distinguibles[i][j] = 1;
                                changed=1;
                                break;
                            }
                        }
                        else if(salida1 > salida2){
                            if(tabla_distinguibles[salida1][salida2] == 1){
                                tabla_distinguibles[i][j] = 1;
                                changed=1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }

    for(i=1; i < num_estados; i++){
        for(j=0; j < i; j++){
            printf("[%d]", tabla_distinguibles[i][j]);
        }
        printf("\n");
    }

    for(i=1; i < num_estados; i++){
        for(j=0; j < i; j++){
            if(tabla_distinguibles[i][j] == 0){
                AFNDInsertaLTransicion(afd, AFNDNombreEstadoEn(afd, j), AFNDNombreEstadoEn(afd, i));
                AFNDInsertaLTransicion(afd, AFNDNombreEstadoEn(afd, i), AFNDNombreEstadoEn(afd, j));
            }
        }
    }

    return AFNDTransforma(afd);
}


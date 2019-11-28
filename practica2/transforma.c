#include <stdio.h>
#include <stdlib.h>

#include "transforma.h"
#include <string.h>



/* Compara dos estados
 * Dos estamos son iguales si su subconjunto de subestados son iguales
 * Devuelve 1 si true y 0 si false */
int comparar_estados(Estado estado1, Estado estado2){
    int i = 0, j = 0;
    int estados_parejos = 0;

    if(estado1.num_estados == estado2.num_estados){
        for(; i < estado1.num_estados; i++){
            for(j=0; j < estado2.num_estados; j++){
                if(estado1.estados[i] == estado2.estados[j]){
                    estados_parejos++;
                }
            }
        }

        if(estados_parejos == estado1.num_estados){
            return 1;
        }
    }

    return 0;
}

/* Inicializa un estado y lo anade al conjunto de estados del programa 
 * Devuelve -1 si error o 0 si funciona correctamente */
int inicializar_estado(Estado * estado){
    if(!estado){
        fprintf(stderr, "No se ha introducido ningun estado\n");
        return -1;
    }

    estado->id = id;
    id++;
    num_creados++;
    estado->num_estados = 0;

    return 0;
}

/* Inserta un subestado en nuestra estructura de estado
 * Comprueba que el estado no este ya incluido y aumenta
 * el numero interno de subestado
 * Devuelve -1 si error o 0 si funciona correctamente */
int insertar_estado(Estado * estado, int estado_insertado){
    int i;

    if(!estado){
        fprintf(stderr, "No se ha introducido ningun estado\n");
        return -1;
    } else if(estado->num_estados == MAX_ESTADOS){
        fprintf(stderr, "No caben más estados\n");
    }

    /* Comprobamos si el estado está en el array de estados */
    for(i = 0; i < estado->num_estados; i++){
        /* El estado ya está insertado */
        if(estado_insertado == estado->estados[i]){
            /* El estado se encuentra ya introducido */
            return 0;
        }
    }

    estado->estados[estado->num_estados] = estado_insertado;
    estado->num_estados ++;

    return 0;
}

/* Imprime la informacion almacenada en nuestros estados */
void imprimir_estado(Estado estado){
    int i;

    printf("Id: %d\n", estado.id);
    printf("Num subestados: %d\n", estado.num_estados);
    printf("Contiene los estados:\n");
    for(i = 0; i < estado.num_estados; i++){
        printf("%d, ", estado.estados[i]);
    }
}

/* Anade todos los subestados al que se puede transitar
 * con una transion lambda desde este estado
 * Devuelve -1 si error o 0 si funciona correctamente */
int anyadir_lambdas(Estado * estado, AFND * afnd){
    int i, j;

    for(i = 0; i < estado->num_estados; i++){
        for(j = 0; j < AFNDNumEstados(afnd); j++){
            if(AFNDCierreLTransicionIJ(afnd, estado->estados[i], j) == 1){
                if(insertar_estado(estado, j) == -1){
                    return -1;
                }
            }
        }
    }
    return 0;
} 

/* Anade todos los subestados al que se puede transitar
 * con una transion del simbolo simb desde este estado 
 * en un estado nuevo
 * Devuelve -1 si error o 0 si funciona correctamente */
int transitar(Estado * estado, Estado * insertar, int simb, AFND * afnd){
    int i, j;

    for(i = 0; i < estado->num_estados; i++){
        for(j = 0; j < AFNDNumEstados(afnd); j++){
            if(AFNDTransicionIndicesEstadoiSimboloEstadof(afnd, estado->estados[i], simb, j) == 1){
                if(insertar_estado(insertar, j) == -1){
                    return -1;
                }
            }
        }
    }
    return 0;
} 

/* Funcion que comprueba si el estado insertado es final o no
 * Devuelve 1 si true, 0 si false
 */
int comprobar_si_final(Estado estado, AFND * afnd){
    int i, j, indice;

    for(i = 0; i < estado.num_estados; i++){
        for(j = 0; j < AFNDNumEstados(afnd); j++){
            if(estado.estados[i] == j){
                indice = AFNDTipoEstadoEn(afnd, j);
                if(indice == 1 || indice == 2){
                    return 1;
                }
            }
        }
    }

    return 0;
}

AFND * AFNDTransforma(AFND * afnd){
    Estado nuevos_estados[MAX_ESTADOS];
    const int afndNumSim = AFNDNumSimbolos(afnd);
    int i, j, iter_nuevosestados = 0;
    int trans_table[MAX_ESTADOS][MAX_SIMBOLOS];
    int transiciona;
    AFND * afd;

    if(!afnd){
        return NULL;
    }

    id = 0;
    num_creados = 0;

    /* Calculo del estado inicial:
     * Son los estados a los que se puede acceder desde q0 sin consumir símbolos de entrada
     */
    inicializar_estado(&nuevos_estados[num_creados]);
    insertar_estado(&nuevos_estados[0], AFNDIndiceEstadoInicial(afnd));

    /* Extraemos todas las transiciones lambdas del estado inicial */
    if(anyadir_lambdas(&nuevos_estados[0], afnd) == -1){
        return NULL;
    }

    /* Inicializamos la tabla de estados */
    for(i=0; i < MAX_ESTADOS; i++){
        for(j=0; j<afndNumSim; j++){
            trans_table[i][j] = -1;
        }
    }

    /* Buscamos a que estados nos llevan nuestros estados secuencialmente */
    while(iter_nuevosestados < num_creados){

        for(i = 0; i < afndNumSim; i++){
            /* Creamos un nuevo estado por cada simbolo donde anadiremos los subestados a los que transita */
            inicializar_estado(&nuevos_estados[num_creados]);
            if(transitar(&nuevos_estados[iter_nuevosestados],&nuevos_estados[num_creados - 1], i, afnd) == -1){
                return NULL;
            }

            /* Si es no lleva a ningun estado se borra el estado creado */
            if(nuevos_estados[num_creados - 1].num_estados == 0){
                num_creados--;
                id--;
                continue;
            }

            /* Anadimos las transiciones por lambdas al estado creado */
            anyadir_lambdas(&nuevos_estados[num_creados - 1], afnd);

            /* Comprobamos que ese estado no lo hubiesemos creado ya.
             * Si se ha creado ya se borra
             */
            for(j = 0; j < num_creados - 1; j++){
                if(comparar_estados(nuevos_estados[j], nuevos_estados[num_creados-1]) == 1){
                    num_creados--;
                    id--;
                    break;
                }
            }
            /* Guardamos la transicion del estado con el simbolo al siguiente estado */
            trans_table[nuevos_estados[iter_nuevosestados].id][i] = nuevos_estados[j].id;
        }
        iter_nuevosestados++;
    }
   
	/* Creamos el nuevo automata determinista */
	afd = AFNDNuevo("Respuesta", num_creados, afndNumSim);

    /* Insertamos los simbolos del automata no determinista */
    for(i = 0; i < afndNumSim; i++){
        AFNDInsertaSimbolo(afd, AFNDSimboloEn(afnd, i));
    }

    /* Insertamos los estado creados identificandolos como
     * INICIAL, INICIAL_Y_FINAL, FINAL o NORMAL
     */
    for(i = 0; i < num_creados; i++){
        char nombre_nuevo[TAM_NOMBRE] = "", aux[TAM_NOMBRE] = "";

        for(j = 0; j < nuevos_estados[i].num_estados; j++ ){
            sprintf(aux, "q%d", nuevos_estados[i].estados[j]);
            strcat(nombre_nuevo, aux);
        }
        if (comprobar_si_final(nuevos_estados[i], afnd) == 1){
            if(i == 0){
                AFNDInsertaEstado(afd, nombre_nuevo, INICIAL_Y_FINAL);
            } else {
                AFNDInsertaEstado(afd, nombre_nuevo, FINAL);
            }
        } else if(i == 0) {
            AFNDInsertaEstado(afd, nombre_nuevo, INICIAL);
        } else {
            AFNDInsertaEstado(afd, nombre_nuevo, NORMAL);
        }
        
    }

    /* Insertamos las transiciones sacandolas 
     * de la trans_table que creamos anteriormente
     */
    for(i = 0; i < num_creados; i++){
        for(j = 0; j < afndNumSim; j++){
            transiciona = trans_table[i][j];
            if(transiciona != -1){
                /* Insertamos si la transicion existe */
                AFNDInsertaTransicion(afd, 
                                      AFNDNombreEstadoEn(afd, i), 
                                      AFNDSimboloEn(afd, j), 
                                      AFNDNombreEstadoEn(afd, transiciona));
            }
        }
    }

    return afd;    
}


#ifndef TRANS_H
#define TRANS_H

#include "afnd.h"

#define MAX_ESTADOS 200
#define TAM_NOMBRE 50
#define MAX_SIMBOLOS 20

typedef struct {
    int id;
    int estados[MAX_ESTADOS];
    int num_estados;
} Estado;

int id;
int num_creados;

int comparar_estados(Estado estado1, Estado estado2);
int inicializar_estado(Estado * estado);
int insertar_estado(Estado * estado, int estado_insertado);
void imprimir_estado(Estado estado);


AFND * AFNDTransforma(AFND * afnd);

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "afnd.h"
#include "transforma.h"

int main(int argc, char ** argv)
{

	AFND * p_afnd;
	AFND * afd;
	
	p_afnd= AFNDNuevo("af11", 3, 2);
	
	AFNDInsertaSimbolo(p_afnd,"a");
	AFNDInsertaSimbolo(p_afnd, "b");
	
	AFNDInsertaEstado(p_afnd, "q0", INICIAL_Y_FINAL);
	AFNDInsertaEstado(p_afnd, "q1", NORMAL);
	AFNDInsertaEstado(p_afnd, "q2", NORMAL);
	
	AFNDInsertaTransicion(p_afnd, "q0", "b", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "a", "q1");
	AFNDInsertaTransicion(p_afnd, "q1", "a", "q2");
	AFNDInsertaTransicion(p_afnd, "q1", "b", "q2");
	AFNDInsertaTransicion(p_afnd, "q2", "a", "q0");
	
	AFNDInsertaLTransicion(p_afnd, "q0", "q2");
	AFNDCierraLTransicion(p_afnd);

	afd  = AFNDTransforma(p_afnd);
	AFNDImprime(stdout,afd);
	AFNDADot(afd);
	
	AFNDElimina(afd);
	AFNDElimina(p_afnd);

	return 0;
}



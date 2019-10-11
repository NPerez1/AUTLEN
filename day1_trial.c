#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TRANS 128
#define MAX_FIN 2

int trans_number;

typedef enum bool{
    true,
    false
} bool;

typedef struct Estado
{
    int id;
}Estado;

typedef struct Transicion
{
    Estado trans[2]; /* 0: inicial 1: final*/
    char symbol;
}Transicion;

typedef struct Automata
{
    char symbols[20];
    Estado estado_actual;
    Estado estado_inicial;
    Estado estado_final[MAX_FIN];
    Transicion trans[MAX_TRANS];
}Automata;

void print_aut(Automata * aut){
    int i;

    printf("Automata,\n Símbolos: \n");
    for(i = 0; i < strlen(aut->symbols) - 1; i++){
        printf(" %c,", aut->symbols[i]);
    }
    printf(" %c\n", aut->symbols[strlen(aut->symbols) - 1]);
    printf("Estado Inicial: q%d\n", (aut->estado_inicial).id);
    printf("Estado Actual: q%d\n", (aut->estado_actual).id);
    printf("Estado Final: q%d\n", (aut->estado_final[0]).id);
    printf("Estado Final 2: q%d\n", (aut->estado_final[1]).id);

    printf("Transiciones:\n");
    for(i = 0; i < trans_number; i++){
        printf("(q%d, q%d, '%c')\n", (aut->trans[i]).trans[0].id, (aut->trans[i]).trans[1].id, (aut->trans[i]).symbol);
    }
}

bool parse(Automata *aut, char* s){
    int i = 0, j, k, flag;
    int arr[MAX_TRANS] = {-1};

    aut->estado_actual = aut->estado_inicial; /*Reseteamos el autómata*/

    while(i < strlen(s)){
        flag = 0;
        /*Buscamos las transiciones que tienen como estado 0 nuestro estado actual*/
        for(j = 0, k = 0; j < trans_number; j++){
            if((aut->trans[j]).trans[0].id == aut->estado_actual.id)
            {
                arr[k] = j;
                k++;
            }
        }
        if(k == 0){
            printf("Hmm\n");
            return false;
        }
        
        j = 0;
        while(j < k){
            if(aut->trans[arr[j]].symbol == s[i]){
                aut->estado_actual = aut->trans[arr[j]].trans[1];
                flag = 1;
                break;
            }
            j++;
        }
        if(flag != 1)
            return false;
        
        i++;
    }

    if(aut->estado_actual.id == aut->estado_final[0].id || aut->estado_actual.id == aut->estado_final[1].id){
        return true;
    }
}

int main(){
    Automata *autom;
    struct Estado estados[4];
    struct Transicion trans_table[8];
    int i;

    autom = calloc(sizeof(Automata), 1);

    strcpy(autom->symbols, "ab");
    
    estados[0].id = 0;
    estados[1].id = 1;
    estados[2].id = 2;
    estados[3].id = 3;

    trans_table[0].symbol = 'a';
    trans_table[0].trans[0] = estados[0];
    trans_table[0].trans[1] = estados[3];

    trans_table[1].symbol = 'b';
    trans_table[1].trans[0] = estados[0];
    trans_table[1].trans[1] = estados[1];

    trans_table[2].symbol = 'a';
    trans_table[2].trans[0] = estados[3];
    trans_table[2].trans[1] = estados[3];

    trans_table[3].symbol = 'b';
    trans_table[3].trans[0] = estados[3];
    trans_table[3].trans[1] = estados[3];

    trans_table[4].symbol = 'a';
    trans_table[4].trans[0] = estados[1];
    trans_table[4].trans[1] = estados[2];

    trans_table[5].symbol = 'b';
    trans_table[5].trans[0] = estados[1];
    trans_table[5].trans[1] = estados[1];

    trans_table[6].symbol = 'a';
    trans_table[6].trans[0] = estados[2];
    trans_table[6].trans[1] = estados[2];

    trans_table[7].symbol = 'b';
    trans_table[7].trans[0] = estados[2];
    trans_table[7].trans[1] = estados[1];

    trans_number = 8;

    autom->estado_inicial = estados[0];
    autom->estado_final[0] = estados[2];
    autom->estado_final[1] = estados[1];
    for(i = 0; i < trans_number; i++)
        autom->trans[i] = trans_table[i];

    print_aut(autom);

    if(parse(autom, "abaaab") == true)
        printf("It works!\n");
    else
        printf("It doesn't work\n");

    free(autom);

    return 0;
}
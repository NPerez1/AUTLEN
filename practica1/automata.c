#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TRANS 128
#define MAX_FIN 5
#define MAX_STA 10

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
    Estado estado_actual[MAX_STA];
    Estado estado_inicial;
    Estado estado_final[MAX_FIN];
    Transicion trans[MAX_TRANS];
    int num_trans;
    int num_estados;
}Automata;

bool check(Estado key, Estado *array){
    int i, num_items = sizeof(array)/sizeof(int);

    for(i = 0; i < num_items; i++){
        if(key.id == array[i].id)
            return true;
    }

    return false;
}


bool checkEnd(Automata* aut){
    int i;
    
    if(!aut){
        printf("Fallo en instruccion checkEnd");
        return false;
    }

    for(i = 0; i < aut->num_estados; i++){
       if(check(aut->estado_actual[i], aut->estado_final) == true){
           return true;
       }
    }

    return false; 
}




void print_aut(Automata * aut){
    int i;

    printf("Automata,\n Símbolos: \n");
    for(i = 0; i < strlen(aut->symbols) - 1; i++){
        printf(" %c,", aut->symbols[i]);
    }
    printf(" %c\n", aut->symbols[strlen(aut->symbols) - 1]);
    printf("Estado Inicial: q%d\n", (aut->estado_inicial).id);
    for(i = 0; i < aut->num_estados; i++){
        if((aut->estado_actual[i]).id != -1){
            printf("Estado Actual %d: q%d\n", i, (aut->estado_actual[i]).id);
        }
    }
    printf("Estado Final: q%d\n", (aut->estado_final[0]).id);
    printf("Estado Final 2: q%d\n", (aut->estado_final[1]).id);

    printf("Transiciones:\n");
    for(i = 0; i < aut->num_trans; i++){
        printf("(q%d, q%d, '%c')\n", (aut->trans[i]).trans[0].id, (aut->trans[i]).trans[1].id, (aut->trans[i]).symbol);
    }
}

bool parse(Automata *aut, char* s){
    int i = 0, j, k, m;
    int arr[MAX_TRANS] = {-1};

    for(i = 0; i < aut->num_estados; i++){
        aut->estado_actual[i].id = -1;
    }
    aut->estado_actual[0] = aut->estado_inicial; /*Reseteamos el autómata*/

    while(i < strlen(s)){
        /*Buscamos las transiciones que tienen como estado 0 nuestro estado actual*/
        for(j = 0, k = 0; j < aut->num_trans; j++){
            for(m = 0; m < aut->num_estados; m++){
                if((aut->trans[j]).trans[0].id == aut->estado_actual[m].id)
                {
                    arr[k] = j;
                    k++;
                }
            }
        }
        if(k == 0){
            printf("Ninguna transición encontrada\n");
            return false;
        }

        for(i = 0; i < aut->num_estados; i++){
            aut->estado_actual[i].id = -1;
        }
        aut->num_estados = 0;
        m = 0;
        
        j = 0;
        while(j < k){
            if(aut->trans[arr[j]].symbol == s[i]){
                if(check(aut->trans[arr[j]].trans[1], aut->estado_actual) == false){
                    aut->estado_actual[m] = aut->trans[arr[j]].trans[1];
                    m++;
                    aut->num_estados++;
                }
            }
            j++;
        }
        if(aut->num_estados == 0){
            print_aut(aut);
            printf("Simbolo no tiene transiciones.\n");
            return false;
        }
        
        i++;
    }

    return checkEnd(aut);
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

    trans_table[0].symbol = 'a';
    trans_table[0].trans[0] = estados[0];
    trans_table[0].trans[1] = estados[1];

    trans_table[1].symbol = 'a';
    trans_table[1].trans[0] = estados[0];
    trans_table[1].trans[1] = estados[2];

    trans_table[2].symbol = 'b';
    trans_table[2].trans[0] = estados[1];
    trans_table[2].trans[1] = estados[0];

    trans_table[3].symbol = 'a';
    trans_table[3].trans[0] = estados[1];
    trans_table[3].trans[1] = estados[1];

    trans_table[4].symbol = 'b';
    trans_table[4].trans[0] = estados[1];
    trans_table[4].trans[1] = estados[2];

    trans_table[5].symbol = 'c';
    trans_table[5].trans[0] = estados[2];
    trans_table[5].trans[1] = estados[1];
    
    autom->num_trans = 6;
    autom->estado_inicial = estados[0];
    autom->estado_final[0] = estados[1];
    autom->num_estados = 1;
    for(i = 0; i < autom->num_trans; i++)
        autom->trans[i] = trans_table[i];

    print_aut(autom);

    if(parse(autom, "abaaabac") == true)
        printf("It works!\n");
    else
        printf("It doesn't work\n");

    free(autom);

    return 0;
}
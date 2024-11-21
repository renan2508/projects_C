#include <stdio.h>
#include <stdbool.h>

void list_candidates(char candidatos[100][255], int candidatos_codigo[], int todos_votos[]){
    for(int i = 0;i<5;i++){
        printf("%s [%d]\nVotos Totais: %d\n", candidatos[i], candidatos_codigo[i], todos_votos[i]);
    }
}

void vote_candidate(char candidatos[100][255], int candidatos_codigo[], int todos_votos[], int voto){
    list_candidates(candidatos, candidatos_codigo, todos_votos);
    voto = 0;
    int found = 0;
    bool stop_check = false;
    int canditato_index;
    do{
        printf("\nVoto: ");
        scanf("%d", &voto);
        for(int i = 0;i<5;i++){
            if(voto == candidatos_codigo[i]){
                stop_check = true;
                canditato_index = i;
                found = 1;
                todos_votos[canditato_index]++;
                break;
            }
        
        }
        if(found == 0){
            printf("Insira um codigo valido.\n");
        }
    }while(stop_check == false);
}

int main(){

    char candidatos[100][255] = {"Bolsonaro", "Pablo Marcal", "Tabata Amaral" , "Dapena", "Boules", "Lula"};
    int candidatos_codigo[100] = {22, 28, 33, 10, 11, 13};
    bool vote_condition = false;
    int voto, todos_votos[100], opcao;
    for(int i = 0;i<5;i++){
        todos_votos[i] = 0;
    }
    do{
        printf("---- Votacao ----\n\n[1] Analisar candidatos\n[2] Votar!\nEscolha: ");
        scanf("%d", &opcao);
        if(opcao != 1 && opcao != 2 && opcao == 3){
            printf("A opcao precisa ser 1, 2 ou 3 .\n\n");
        }
        if(opcao == 1){
            list_candidates(candidatos, candidatos_codigo, todos_votos);
        } else if(opcao == 2){
            vote_candidate(candidatos, candidatos_codigo, todos_votos, voto);
        } else if(opcao == 3){
            vote_condition = true;
        }
    }while(vote_condition == false);
    return 0;
}
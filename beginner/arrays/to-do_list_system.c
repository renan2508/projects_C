#include <stdio.h>
#include <string.h>
#include <ctype.h>

int menu(){
    int opcao_escolhida;
    do{
        printf("---- Menu To-do ----\n");
        printf("[1] Adicionar Tarefa \n[2] Remover tarefa \n[3] Marcar tarefa como concluida\n[4] Listar tarefas \n[5] Ordenar tarefas \n[6] Fechar o programa\n");
        printf("Input: ");
        scanf("%d", &opcao_escolhida);
        if(opcao_escolhida < 1 || opcao_escolhida > 7){
            printf("A input deve ser ente 1 e 7.");
        }
    }while(opcao_escolhida < 1 || opcao_escolhida > 7);
    return opcao_escolhida;
}

void Lista_Tarefas(int tarefas_unicas, char nome_tarefa[100][255], int nivel_prioridade[], int status[]){
    if(tarefas_unicas == 0){
        printf("\n\nNao a tarefas na lista.\n\n");
        return;
    }
    printf("\n\n ---- Lista de Tarefas ----\n\n");
    for(int i = 0;i<tarefas_unicas;i++){
        printf("Tarefa %d\n\n", i+1);
        printf("%s", nome_tarefa[i]);
        switch(nivel_prioridade[i]){
            case 1:
                printf("Prioridade: baixa\n");
                break;
            case 2:
                printf("Prioridade: media\n");
                break;
            case 3:
                printf("Prioridade: alta\n");
                break;
            case 4:
                printf("Prioridade: extrema\n");
                break;
        }
        if(status[i] == 0){
            printf("Status: pendente.\n\n\n");
        } else{
            printf("Status: concluida.\n\n\n");
        }
    }
}

void TaskConcluder(int tarefas_unicas, int status[], char nome_tarefa[100][255], int nivel_prioridade[]){
    int conclude_index;
    Lista_Tarefas(tarefas_unicas, nome_tarefa, nivel_prioridade, status);
    do{
        printf("Insira a tarefa para marcar como concluida: ");
        scanf("%d", &conclude_index);
        if(conclude_index < 0 || conclude_index > tarefas_unicas){
            printf("Por favor, insira um valor entre 1 e %d\n", tarefas_unicas);
        }
    }while(conclude_index < 0 || conclude_index > tarefas_unicas);
    conclude_index--;
    status[conclude_index] = 1;
    printf("Tarefa concluida com sucesso! Parabens!\n");
}

void Sorters(int tarefas_unicas, char nome_tarefa[100][255], int nivel_prioridade[], int status[]){
    printf("---- Ordenador ----\n");
    int sorter, tempPrioridade, tempStatus;
    char tempNome[255];
    do{
        printf("Organizar por prioridade ou status? \n[1] Prioridade\n[2] Status\nOpcao:");
        scanf("%d", &sorter);
        if(sorter < 1 || sorter > 2){
            printf("Escolha uma opcao viavel.");
        }
    }while(sorter < 1 || sorter > 2);
    if(sorter == 1){
        for(int i = 0;i<tarefas_unicas-1;i++){
            for(int j = 0;j<tarefas_unicas-i-1;j++){
                if(nivel_prioridade[j]  < nivel_prioridade[j+1]){
                    tempPrioridade = nivel_prioridade[j];
                    nivel_prioridade[j] = nivel_prioridade[j+1];
                    nivel_prioridade[j+1] = tempPrioridade;
                    tempStatus = status[j];
                    status[j] = status[j+1];
                    status[j+1] = tempStatus;
                    strcpy(tempNome, nome_tarefa[j]);
                    strcpy(nome_tarefa[j], nome_tarefa[j+1]);
                    strcpy(nome_tarefa[j+1], tempNome);
                }
            }
        }
    } else{
        for(int i = 0;i<tarefas_unicas-1;i++){
            for(int j = 0;j<tarefas_unicas-1-i;j++){
                if(status[j] > status[j+1]){
                    tempPrioridade = nivel_prioridade[j];
                    nivel_prioridade[j] = nivel_prioridade[j+1];
                    nivel_prioridade[j+1] = tempPrioridade;
                    tempStatus = status[j];
                    status[j] = status[j+1];
                    status[j+1] = tempStatus;
                    strcpy(tempNome, nome_tarefa[j]);
                    strcpy(nome_tarefa[j], nome_tarefa[j+1]);
                    strcpy(nome_tarefa[j+1], tempNome);
                }
            }
        }
    }
    printf("Tarefas organizadas com sucesso!");
    Lista_Tarefas(tarefas_unicas, nome_tarefa, nivel_prioridade, status);
}

void Task_Remover(int *tarefas_unicas, char nome_tarefa[100][255], int nivel_prioridade[], int status[]){
    
    int remover;
    if(*tarefas_unicas == 0){
        printf("Nao a items na lista.\n\n");
        return;
    }
    
    do{
        printf("Qual tarefa da lista remover? ");
        scanf("%d", &remover);
        if(remover > *tarefas_unicas || remover<1){
            printf("Nao a essa tarefa na lista. Por favor, digite um numero entre 0 e %d.\n", *tarefas_unicas);
        }
    }while(remover>*tarefas_unicas || remover<1);
    for(int i = remover-1;i<*tarefas_unicas-1;i++){
        strcpy(nome_tarefa[i], nome_tarefa[i+1]);
        nivel_prioridade[i] = nivel_prioridade[i+1];
        status[i] = status[i+1];
    }
    (*tarefas_unicas)--;
    printf("Tarefa removida com sucesso.\n");
}

int main(){
    int i = 0, opcao;
    int tarefas_unicas = 0;
    int status[100];
    int nivel_prioridade[100];
    char nome_tarefa[100][255];

    do{
        opcao = menu();
        switch(opcao){
            case 1:
                getchar();
                printf("Nome da tarefa: ");
                fgets(nome_tarefa[i], 255, stdin);
                printf("Prioridade: \n[1] Baixa\n[2] Media\n[3] Alta\n[4] Extrema\n");
                do{
                    printf("Input: ");
                    scanf("%d", &nivel_prioridade[i]);
                    if(nivel_prioridade[i] < 1 || nivel_prioridade[i] > 4){
                        printf("Insira uma opcao viavel.\n");
                    }
                }while(nivel_prioridade[i] < 1 || nivel_prioridade[i] > 4);
                status[i] = 0;
                tarefas_unicas++;
                i++;
                break;
            case 2:
                Task_Remover(&tarefas_unicas, nome_tarefa, nivel_prioridade, status);
                break;
            case 3:
                TaskConcluder(tarefas_unicas, status, nome_tarefa, nivel_prioridade);
                break;
            case 4:
                Lista_Tarefas(tarefas_unicas, nome_tarefa, nivel_prioridade, status);
                break;
            case 5:
                Sorters(tarefas_unicas, nome_tarefa, nivel_prioridade, status);
        }
    }while(opcao != 6);
    printf("Fechando programa...");
    return 0;
}
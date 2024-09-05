#include <stdio.h>

int menu(){
    int current_option;
    do{
        printf("Menu\n\n[1] Adicionar item ao estoque\n[2] Analisar itens do estoque\n[3] Calcular preco total\n[4] Ordenar estoque\n[5] Sair do programa\n");
        printf("Opcao: ");
        scanf("%d", &current_option);
        if(current_option < 1 || current_option > 5){
            printf("Precisa ser entre os numeros possiveis.\n");
        }
    }while(current_option < 1 || current_option > 5);
    return current_option;
}

int printStatus(char* NomeProdutos[], float ProdutoQtd[], float ProdutoPreco[], int quantidade_produtos_unicos){
    if(quantidade_produtos_unicos == 0){
        printf("Nao a dados no estoque.");
        menu();
        return menu();
    }  else{
            printf("\n\nDados do estoque:\n\n");
            for(int i =0;i<quantidade_produtos_unicos;i++){
                printf("Nome: ");
                printf("%s ", NomeProdutos[i]);
                printf("\n");
                printf("Quantidade: ");
                printf("%f", ProdutoQtd[i]);
                printf("\nPreco: ");
                printf("%f", ProdutoPreco[i]);
                }
        }
        return 0;
}

float TotalCalculator(int ProdutoQtd[], float ProdutoPreco[], int quantidade_produtos_unicos){
    int i, soma = 0;
    int Total[100];
    for(i=0;i<quantidade_produtos_unicos;i++){
        soma = soma + ProdutoPreco[i] * ProdutoQtd[i];
        Total[i] = soma;
    }
    soma=0;
    for(i=0;i<quantidade_produtos_unicos;i++){
        soma = soma + Total[i];
    }
    return soma;
}

int main(){

    int quantidade_produtos_unicos = 0;
    char* NomeProdutos[100];
    float ProdutoQtd[100];
    float ProdutoPreco[100];
    printf("\n\nSistema de gerenciamento de estoque\n\n");

    while(menu() != 5){
        if(menu() == 1){
            printf("Nome do produto: ");
            fgets(NomeProdutos[quantidade_produtos_unicos], 255, stdin);
            printf("Quantidade do produto: ");
            scanf("%f", &ProdutoQtd[quantidade_produtos_unicos]);
            printf("Preco do produto: ");
            scanf("%f", &ProdutoPreco[quantidade_produtos_unicos]);
            quantidade_produtos_unicos++;
            menu();
        } else if(menu() == 2){
            printStatus(NomeProdutos, ProdutoQtd, ProdutoPreco, quantidade_produtos_unicos);
        } else if(menu() == 3){

        }
        


    }
    return 0;
}
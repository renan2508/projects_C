#include <stdio.h>
#include <string.h>

int menu(){
    int current_option;
    do{
        printf("\n\nMenu\n\n[1] Adicionar item ao estoque\n[2] Analisar itens do estoque\n[3] Calcular preco total\n[4] Ordenar estoque\n[5] Sair do programa\n");
        printf("Opcao: ");
        scanf("%d", &current_option);
        if(current_option < 1 || current_option > 5){
            printf("Precisa ser entre os numeros possiveis.\n");
        }
    }while(current_option < 1 || current_option > 5);
    return current_option;
}

int printStatus(char NomeProdutos[][255], float ProdutoQtd[], float ProdutoPreco[], int quantidade_produtos_unicos){
    if(quantidade_produtos_unicos == 0){
        printf("Nao a dados no estoque a serem analisados.\n\n");
        menu();
        return menu();
    }  else{
            printf("\n\n----Dados do estoque----\n\n");
            for(int i =0;i<quantidade_produtos_unicos;i++){
                printf("Nome: %s", NomeProdutos[i]);
                printf("Quantidade: %.0f", ProdutoQtd[i]);
                printf("\nPreco: R$%.2f\n\n", ProdutoPreco[i]);
                
                }
        }
        return 0;
}

void Sorter(float ProdutoPreco[], char NomeProdutos[][255], float ProdutoQtd[], int quantidade_produtos_unicos){
    for(int i=0;i<quantidade_produtos_unicos-1;i++){
        for(int j=0;j<quantidade_produtos_unicos-1-i;j++){
            if(ProdutoPreco[j] > ProdutoPreco[j+1]){
                
                float temppreco = ProdutoPreco[j];
                ProdutoPreco[j] = ProdutoPreco[j+1];
                ProdutoPreco[j+1] = temppreco;

                float tempQtd = ProdutoQtd[j];
                ProdutoQtd[j] = ProdutoQtd[j+1];
                ProdutoQtd[j+1] = tempQtd;

                char tempNome[255];
                strcpy(tempNome, NomeProdutos[j]);
                strcpy(NomeProdutos[j], NomeProdutos[j+1]);
                strcpy(NomeProdutos[j+1], tempNome);
                
            }
        }
    }
    printStatus(NomeProdutos, ProdutoQtd, ProdutoPreco, quantidade_produtos_unicos);   
}
float TotalCalculator(float ProdutoQtd[], float ProdutoPreco[], int quantidade_produtos_unicos){
    int i, soma = 0;
    for(i=0;i<quantidade_produtos_unicos;i++){
        soma = soma + ProdutoPreco[i] * ProdutoQtd[i];
    }
    return soma;
    }

int main(){

    int quantidade_produtos_unicos = 0;
    char NomeProdutos[100][255];
    float ProdutoQtd[100];
    float ProdutoPreco[100];
    int opcao;
    do{
        opcao = menu();
        switch(opcao){
            case 1:
                getchar();
                printf("Nome do produto: ");
                fgets(NomeProdutos[quantidade_produtos_unicos], 255, stdin);
                printf("Quantidade do produto: ");
                scanf("%f", &ProdutoQtd[quantidade_produtos_unicos]);
                printf("Preco do produto: ");
                scanf("%f", &ProdutoPreco[quantidade_produtos_unicos]);
                quantidade_produtos_unicos++;
                break;
            case 2:
                printStatus(NomeProdutos, ProdutoQtd, ProdutoPreco, quantidade_produtos_unicos);
                break;
            case 3:
                printf("\n\nPreco total do estoque: R$%.2f\n\n", TotalCalculator(ProdutoQtd, ProdutoPreco, quantidade_produtos_unicos));
                break;
            case 4:
                Sorter(ProdutoPreco, NomeProdutos, ProdutoQtd, quantidade_produtos_unicos);
                break;
            case 5:
                printf("Saindo...");
                break;
        }
    }while(opcao != 5);

    return 0;
}
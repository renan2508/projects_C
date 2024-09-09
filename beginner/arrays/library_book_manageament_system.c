#include <stdio.h>
#include <string.h>

int menu(){
    int opcao_escolhida;
    do{
        printf("[1] Cadastrar livros\n[2] Emprestar livro\n[3] Devolver livro\n[4] Buscar livro \n[5] Todos os livros\n[6] Fechar programa\nInput:");
        scanf("%d", &opcao_escolhida);
        if(opcao_escolhida < 1 || opcao_escolhida > 5){
            printf("Escolha uma opcao valida.");
        }
    }while(opcao_escolhida < 1 || opcao_escolhida > 5);
    return opcao_escolhida;
}

void list_books(char NomeLivros[100][255], char NomeAutor[100][255], int status[], int quantidade_livros_unicos){
    if(quantidade_livros_unicos == 0){
        printf("Nao a livros na estante\n\n");
        return;
    }
    printf("\n\n---- Estante ----\n\n");
    for(int i = 0;i<quantidade_livros_unicos; i++){
        printf("Livro: %s", NomeLivros[i]);
        printf("Autor: %s", NomeAutor[i]);
        if(status[i] == 0){
            printf("Status: em estoque.\n");
        } else{
            printf("Status: emprestado.\n");
        }
    }
}


int main(){
    char NomeLivros[100][255];
    char NomeAutor[100][255];
    int status[100], opcao, i=0;
    int quantidade_livros_unicos = 0;
    
    do{
        printf("---- Estante ----\n");
        opcao = menu();
        switch(opcao){
            case 1:
                getchar();
                printf("Nome do livro: ");
                fgets(NomeLivros[i], 255, stdin);
                printf("Autor: ");
                fgets(NomeAutor[i], 255, stdin);
                quantidade_livros_unicos++;
                status[i] = 0;
                i++;
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                list_books(NomeLivros, NomeAutor, status, quantidade_livros_unicos);
                break;
            case 5:
                break;
        }
    }while(opcao != 6);
    
    return 0;
}
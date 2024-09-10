#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int menu(){
    int opcao_escolhida;
    do{
        printf("[1] Cadastrar livros\n[2] Emprestar livro\n[3] Devolver livro\n[4] Buscar livro \n[5] Todos os livros\n[6] Fechar programa\nInput:");
        scanf("%d", &opcao_escolhida);
        if(opcao_escolhida < 1 || opcao_escolhida > 6){
            printf("Escolha uma opcao valida.");
        }
    }while(opcao_escolhida < 1 || opcao_escolhida > 6);
    return opcao_escolhida;
}

void no_books(){
    printf("Nao a livros na estante.\n\n");
}

void list_books(char NomeLivros[100][255], char NomeAutor[100][255], int status[], int quantidade_livros_unicos){
    if(quantidade_livros_unicos == 0){
        no_books();
    }
    printf("\n\n---- Estante ----\n\n");
    for(int i = 0;i<quantidade_livros_unicos; i++){
        printf("Codigo: %d\n", i+1);
        printf("Livro: %s", NomeLivros[i]);
        printf("Autor: %s", NomeAutor[i]);
        if(status[i] == 0){
            printf("Status: em estoque.\n\n\n");
        } else{
            printf("Status: emprestado.\n\n\n");
        }
    }
}

void borrow_book(int quantidade_livros_unicos, int status[], char NomeLivros[100][255], char NomeAutor[100][255]){
    int option;
    list_books(NomeLivros, NomeAutor, status, quantidade_livros_unicos);
    if(quantidade_livros_unicos == 0){
        no_books();
        return;
    }
    do{
        printf("Qual livro escolher?\n");
        scanf("%d", &option);
        if(option < 0 || option > quantidade_livros_unicos || status[option-1] == 1){
            printf("Insira um valor entre 1 e %d.\n", quantidade_livros_unicos);
        }
    }while(option < 1 || option > quantidade_livros_unicos || status[option-1] == 1);
    status[option-1] = 1;
    printf("Livro emprestado com sucesso, boa leitura!\n\n");
}

void return_book(int quantidade_livros_unicos, int status[], char NomeLivros[100][255], char NomeAutor[100][255]){
    if(quantidade_livros_unicos == 0){
        no_books();
        return;
    }
    int option = -1;
    int counter = 0;
    int index[100];
    
    list_books(NomeLivros, NomeAutor, status, quantidade_livros_unicos);
    for(int i = 0;i<quantidade_livros_unicos;i++){
        if(status[i] == 1){
            index[counter] = i+1;
            counter++;
        }
    }
    if(counter > 0){
        for(int i = 0;i<counter;i++){
            printf("Livros disponiveis para devolucao: \n");
            printf("Codigo: %d\nNome: %sAutor: %s", index[i], NomeLivros[index[i]-1], NomeAutor[index[i]-1]);
        }
    }   else{
            printf("Nao a livros para devolver.\n\n");
        }
    
    
    int check = 0;
    while(check == 0){
        printf("Digite o codigo: ");
        scanf("%d", &option);
        for(int i = 0;i<counter;i++){
            if(index[i] == option){
                check = 1;
                break;
            }
        }
    }
    status[option-1] = 0;
    printf("Livro devolvido com sucesso!\n\n");
}

void search_by_name(char NomeLivros[100][255], char NomeAutor[100][255], int quantidade_livros_unicos, int status[], bool stop_namesearch){
    char name[255];
    getchar();
    int found;
    int option;
    printf("Nome do livro: ");
    fgets(name, 255, stdin);
    for(int i = 0;i<quantidade_livros_unicos;i++){
        if(strstr(NomeLivros[i], name) != NULL){
            found = 1;
            printf("Codigo: %d\nNome: %s\nAutor: %s", i+1, NomeLivros[i], NomeAutor[i]);
            if(status[i] == 0){
                printf("Em estoque.\n");
            } else{
                printf("Emprestado.\n");
            }
        }
    }
    if(found != 1){
        printf("Nao a resultados a pesquisa.");
    }
    printf("Pesquisar outro nome ou sair? \n[1] Pesquisar outro nome \n[2] Sair\n");
    scanf("%d", &option);
    if(option == 2){
        stop_namesearch = true;
    }
}

/*oid search_by_author(){

}*/

int main(){
    char NomeLivros[100][255];
    char NomeAutor[100][255];
    int status[100], opcao, i=0;
    int quantidade_livros_unicos = 0;
    int busca_opcao;
    bool stopSearch=false, stop_namesearch = false, stop_authorsearch = false;
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
                borrow_book(quantidade_livros_unicos, status, NomeLivros, NomeAutor);
                break;
            case 3:
                return_book(quantidade_livros_unicos, status, NomeLivros, NomeAutor);
                break;
            case 4:
                do{
                    printf("\n\n[1] Buscar pelo nome do livro\n\n[2] Buscar pelo autor \n\n[3] Parar busca");
                    scanf("%d", &busca_opcao);
                    if(busca_opcao == 1){
                        do{
                            search_by_name(NomeLivros, NomeAutor, quantidade_livros_unicos, status, stop_namesearch);
                        }while(stop_namesearch == false);
                    } else{
                        stopSearch = true;
                        printf("Saindo...\n\n");
                        break;
                    }
                }while(stopSearch == false);
                break;
            case 5:
                list_books(NomeLivros, NomeAutor, status, quantidade_livros_unicos);
                break;
        }
    }while(opcao != 6);
    
    return 0;
}
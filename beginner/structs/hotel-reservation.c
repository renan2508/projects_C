#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
    char name[100];
    int phone_number;
    int cpf;
} Client;

typedef struct{
    int number;
    int type;
    bool status;
    bool set;
} Bedroom;

// types
// 0 = solo
// 1 = married
// 2 = suit
// 4 = to define

typedef struct{
    Client client;
    Bedroom bedroom;
    int check_in_date;
    int check_out_date;
} Reservation;




int menu(){
    int choosen_option;
    do{
        printf("--- Menu ---\n\n[1] Adicionar quarto\n[2] Cadastrar hospede\n[3] Reservar quarto\n[4] Listagem\n[5] Cancelar reserva\n[6] Pesquisar reservas\n[7] Sair\nOpcao: ");
        scanf("%d", &choosen_option);
        if(choosen_option < 0 || choosen_option > 7){
            printf("\nInsira um dos numeros validos.");
        }
    } while(choosen_option < 0 || choosen_option > 7);
    return choosen_option;
}

/*void add_bedroom(Bedroom *bed_arra[], int *quartos_unicos){
    
}*/

int list_bedrooms(Bedroom bed_arr[], int quartos_unicos){
    if(quartos_unicos == 0){
        printf("\n\nNo bedrooms have been set.\n\n");
        return 0;
    }
    printf("\nBedrooms Information\n\n");
    for(int i = 0;i < quartos_unicos; i++){
        if(bed_arr[i].set == true){
            printf("Bedroom %d\n", i+1);
            printf("Number: %d", bed_arr[i].number);
            if(bed_arr[i].type == 4){
                printf("Type: To Define\n");
            } else if(bed_arr[i].type == 2){
                printf("Suite\n");
            } else if(bed_arr[i].type == 1){
                printf("Couple\n");
            } else{
                printf("Single\n");
            }
            if(bed_arr[i].status == false){
                printf("Status: Free.\n");
            } else{
                printf("Status: Reserved.\n");
            }
        } else{
            printf("Bedroom %d has not been configured.\n", i+1);
            continue;
        }
    }
    return 0;
}

int main(){

    Bedroom bedroom1, bedroom2, bedroom3, bedroom4, bedroom5;
    Bedroom bed_arr[] = {bedroom1, bedroom2, bedroom3, bedroom4, bedroom5};
    int size_arr = sizeof(bed_arr) / sizeof(bed_arr[0]);
    for(int i = 0;i<size_arr;i++){
        bed_arr[i].type = 4;
        bed_arr[i].status = false;
        bed_arr[i].set = false;
    }
    int quartos_unicos = 5;
    int option;
    do{
        option = menu();
        switch(option){
            case 4:
                    list_bedrooms(bed_arr, quartos_unicos);
                    break;
            case 7:
                printf("Leaving program....");
        }
    }while(option != 7);
    return 0;
}
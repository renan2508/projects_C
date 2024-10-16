#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct{
    char name[100];
    long long int phone_number;
    long long int cpf;
    bool signed_up;
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
        printf("\n--- Menu ---\n\n[1] Add Bedroom\n[2] Sign-Up\n[3] Reserve\n[4] Lists\n[5] Cancel Reserve\n[6] Search Reserves\n[7] Quit Program\nOpcao: ");
        scanf("%d", &choosen_option);
        if(choosen_option < 0 || choosen_option > 7){
            printf("\nInsira um dos numeros validos.");
        }
    } while(choosen_option < 0 || choosen_option > 7);
    return choosen_option;
}



int list_everything(Bedroom bed_arr[], int quartos_unicos, int signed_up_clients, Client *client_array){
    printf("\nBedrooms Information\n\n");
    for(int i = 0;i < quartos_unicos; i++){
        if(bed_arr[i].set == true){
            printf("\nBedroom %d\n", i+1);
            printf("Number: %d\n", bed_arr[i].number);
            if(bed_arr[i].type == 4){
                printf("Type: To Define\n");
            } else if(bed_arr[i].type == 2){
                printf("Type: Suite\n");
            } else if(bed_arr[i].type == 1){
                printf("Type: Couple\n");
            } else{
                printf("Type: Single\n");
            }
            if(bed_arr[i].status == false){
                printf("Status: Free.\n\n");
            } else{
                printf("Status: Reserved.\n\n");
            }
        } else{
            printf("Bedroom %d has not been configured.\n", i+1);
            continue;
        }
    }
    if(signed_up_clients != 0){
        printf("\n\n---- Clients Information ----\n\n");
        for(int i = 0;i<signed_up_clients;i++){
            printf("Name: %s", client_array[i].name);
            printf("CPF: %lld\n", client_array[i].cpf);
            printf("Phone-Number: %lld\n", client_array[i].phone_number);
        }
    } else{
        printf("\n\nNo signed-up clients yet :(\n\n");
    }
    return 0;
}

void sign_up(Client **client_arr, int *signed_up_clients){
    *client_arr = realloc(*client_arr, (*signed_up_clients + 1) * sizeof(Client));
    if (*client_arr == NULL) {
        printf("Error.\n");
        exit(1);
    }
    
    Client *new_client = &(*client_arr)[*signed_up_clients];
    printf("Client Sign-Up\n");
    getchar();
    printf("Name: ");
    fgets(new_client->name, 255, stdin);
    //scanf(" %[^\n]", new_client->name);
    printf("Phone-Number (Full): ");
    scanf("%lld", &new_client->phone_number);
    printf("CPF: ");
    scanf("%lld", &new_client->cpf);
    new_client->signed_up = true;
    (*signed_up_clients)++;

    printf("Congrats! You're now signed up.\n");
}

void add_bedroom(Bedroom bed_arra[], int *quartos_unicos, int signed_up_clients, Client *client_array){
    list_everything(bed_arra, *quartos_unicos, signed_up_clients, client_array);
    int option;
    do{
        printf("\nChoose which bedroom to modify, between 1 and %d: ", *quartos_unicos); 
        scanf("%d", &option);
        if(option < 1 || option > *quartos_unicos){
            printf("Insira um valor entre 1 e %d.\n\n", *quartos_unicos);
        }
    }while(option < 1 || option > *quartos_unicos);
    option--;
    printf("Modify Bedroom %d\n\n", option+1);
    printf("Number: ");
    scanf("%d", &bed_arra[option].number);
    do{
        printf("[1] Single\n[2] Couple\n[3] Suite\nType: ");
        scanf("%d", &bed_arra[option].type);
        if(bed_arra[option].type < 1 || bed_arra[option].type > 3){
            printf("Insert a possible value. (1-3)\n\n");
        }
    }while(bed_arra[option].type < 1 || bed_arra[option].type > 3);
    bed_arra[option].set = true;
}
//vai fazer array dinamica kkkk sfd
void make_reserve(Bedroom bed_arr[], int size_arr){
    int option;
    printf("\n\n----Available Reserves ----\n\n");
    for(int i = 0;i<size_arr;i++){
        if(bed_arr[i].status == false && bed_arr[i].set == true){
            int type = bed_arr[i].type;
            printf("\n\nBedroom %d\n", i+1);
            printf("Number: %d\n", bed_arr[i].number);
            type--;
            if(type == 2){
                printf("Type: Suit\n");
            } else if(type == 1){
                printf("Type: Couple\n");
            } else if(type == 0){
                printf("Type: Single\n");
            }
        }
    }
    bool check=false;
    do{
        printf("Option to reserve: ");
        scanf("%d", &option);
        option--;
        if(option < 0 || option > size_arr){
            printf("Choose a number correctly.\n\n");
        }
        if(bed_arr[option].set == true && bed_arr[option].status == false){
            printf("Your reservation for bedroom %d was a sucess!\n\n", option+1);
            check=true;
        } else{
            printf("Use another number and choose one that's available.\n\n");
        }
    }while(check == false);
    bed_arr[option].status = true;
}
//aqui tbm vai puxar a array
void cancel_reserve(Bedroom bed_arr[], int size_arr){
    int option;
    int set_bedrooms=0;
    printf("---- Reservation Cancelation ----");
    for(int i = 0;i<size_arr;i++){
        if(bed_arr[i].status == true){
            set_bedrooms++;
            printf("\n\nBedroom %d\n", i+1);
            printf("Number: %d\n", bed_arr[i].number);
            switch(bed_arr[i].type){
                case 2:
                    printf("Suit.\n");
                    break;
                case 1:
                    printf("Couple.\n");
                    break;
                case 0:
                    printf("Single.\n");
                    break;
                default:
                    printf("\n\n---- Error. Report to developers. ----\n");
                    break;
            }
            printf("Type this code to cancel this reservation: %d\n", i+1);
        }
    }
    if(!set_bedrooms){
        printf("\n\nThere are no bedrooms configured. Try setting some!\n\n");
    } else{
        bool leave = false;
        do{
            printf("\nOption to cancel reservation: ");
            scanf("%d", &option);
            if(option < 1 || option > 5){
                printf("Choose an option between 1 and 5.\n");
            } else{
                option--;
                if(!bed_arr[option].set){
                    printf("This bedroom is not set.\n");
                } else{
                    if(!bed_arr[option].status){
                        printf("This bedroom is not reserved.\n");
                    } else{
                        bed_arr[option].status = false;
                        leave = true;
                        printf("\n\nThe reserve cancelation for bedroom %d was a sucess! ", option);
                    }
                }
            }
        }while(!leave);
    }
}

void search_by(){

}

int main(){

    Bedroom bedroom1, bedroom2, bedroom3, bedroom4, bedroom5;
    Bedroom bed_arr[] = {bedroom1, bedroom2, bedroom3, bedroom4, bedroom5};
    int size_arr = sizeof(bed_arr) / sizeof(bed_arr[0]);

    Client *client_arr = malloc(sizeof(Client));
    int signed_up_clients=0;

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
            case 1:
                add_bedroom(bed_arr, &quartos_unicos, signed_up_clients, client_arr);
                break;
            case 2:
                sign_up(&client_arr, &signed_up_clients);
                break;
            case 3:
                make_reserve(bed_arr, size_arr);
                break;
            case 4:
                list_everything(bed_arr, quartos_unicos, signed_up_clients, client_arr);
                break;
            case 5:
                cancel_reserve(bed_arr, size_arr);
                break;
            case 7:
                printf("Leaving program....");
                break;
        }
    }while(option != 7);
    free(client_arr);
    return 0;
}
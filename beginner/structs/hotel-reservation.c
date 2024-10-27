#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct{
    char name[100];
    char phone_number[100];
    char cpf[100];
    bool signed_up;
} Client;

typedef struct{
    int number;
    int type; // [4] to define - [2] suit - [1] couple - [0] single
    bool status;
    bool set;
} Bedroom;

typedef struct{
    Client client;                              
    Bedroom bedroom;
    int check_in_date[3]; //[0] day [1] month [2] year
    int check_out_date[3];
} Reservation;

int menu(){
    int choosen_option;
    do{
        printf("\n--- Menu ---\n\n[1] Add Bedroom\n[2] Sign-Up\n[3] Reserve\n[4] Lists\n[5] Cancel Reserve\n[6] Search\n[7] Quit Program\nOpcao: ");
        scanf("%d", &choosen_option);
        if(choosen_option < 0 || choosen_option > 7){
            printf("\nInsira um dos numeros validos.");
        }
    } while(choosen_option < 0 || choosen_option > 7);
    return choosen_option;
}



int list_everything(Bedroom bed_arr[], int quartos_unicos, int signed_up_clients, Client *client_array){
    printf("\n\n---- Bedrooms Information ---- \n\n");
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
            printf("\nName: %s", client_array[i].name);
            printf("CPF: %s", client_array[i].cpf);
            printf("Phone-Number: %s", client_array[i].phone_number);
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
    printf("\n\nClient Sign-Up\n");
    getchar();
    printf("Name: ");
    fgets(new_client->name, 100, stdin);
    //scanf(" %[^\n]", new_client->name);
    printf("Phone-Number (Full): ");
    fgets(new_client->phone_number, 100, stdin);
    printf("CPF: ");
    fgets(new_client->cpf, 100, stdin);
    new_client->signed_up = true;
    (*signed_up_clients)++;
    printf("Congrats! You're now signed up.\n");
}

void add_bedroom(Bedroom bed_arra[], int *quartos_unicos, int signed_up_clients, Client *client_array, int *set_bedrooms){
    list_everything(bed_arra, *quartos_unicos, signed_up_clients, client_array);
    int choose;
    if(*set_bedrooms == 5){
        printf("\n\nAll bedrooms have been signed. Do you want to rewrite?\n\n[1] Yes\n[2] No\n\n");
        do{
            printf("Option: ");
            scanf("%d", &choose);
            if(choose == 2){
                return;
            } else if(choose == 1){
                printf("\n\nLeaving option...\n\n");
            } else{
                printf("\n\nInvalid input.\n\n");
            }
        }while(choose != 1 || choose != 2);
    }
    
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
    bed_arra[option].type--;
    bed_arra[option].set = true;
    (*set_bedrooms)++;
}

bool leep_year(int year){
    if(year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)){
        return true;
    } else{
        return false;
    }
}

bool check_date(int year, int month, int day){
    bool is_leep = leep_year(year);
    if((year < 2024 || year > 2026) || (month<=0 || month > 12) || (day <= 0 || day > 29)){
        return false;   
    } else{
        if(is_leep && month == 2){
            if(day <= 0 || day > 29){
            return false;
            }
        }
        else if(month == 4 || month == 6 || month == 9 || month == 11){
            if(day > 30){
                return false;
            }
        } else{
            if(day > 31){
                return false;
            }
        }
    }
    return true;
}

int count_checkin_days(int year, int month, int day){
    while(year != 0){
        year--;
        month += 12;
    }
    day += 30*month;
    return day;
}
int count_checkout_days(int years, int month, int day){
    while(years != 0){
        years--;
        month +=12;
    }
    day += 30*month;
    return day;
}
   

void make_reserve(Reservation **reserves_arr, int *reserves_count, Bedroom bed_arr[], int size_arr, Client client_arr[], int signed_up_clients, int *set_bedrooms, int *available_bedrooms){
    if(*set_bedrooms == 0 || signed_up_clients == 0){
        printf("\n\nNo Bedrooms or clients have been set/signed to make a reservation.\n\n");
        return;
    }
    *reserves_arr = realloc(*reserves_arr, (*reserves_count+1) * sizeof(Reservation));
    if (*reserves_arr == NULL) {
        printf("Error.\n");
        exit(1);
    }
    if(*available_bedrooms == 0){
        printf("\n\nThere are no free rooms for reservations. Try setting one.\n\n");
    } else{
        (*available_bedrooms)--;
    }
    int option;
    printf("\n\n----Available Reserves ----\n\n");
    for(int i = 0;i<size_arr;i++){
        if(bed_arr[i].status == false && bed_arr[i].set == true){
            printf("\n\nBedroom %d\n", i+1);
            printf("Number: %d\n", bed_arr[i].number);
            int type = bed_arr[i].type;
            switch(type){
                case 0: printf("Type: Single\n"); break;
                case 1: printf("Type: Couple.\n"); break;
                case 2: printf("Type: Suite.\n"); break;
            }
        }
    }
    bool valid_bedroom=false;
    do{
        printf("\n\nOption to reserve: ");
        scanf("%d", &option);
        option--;
        if(option < 0 || option > size_arr){
            printf("Choose a number correctly.\n\n");
        }
        if(bed_arr[option].set == true && bed_arr[option].status == false){
            valid_bedroom = true;

            printf("\n\nYou're almost there!\n\nSelecting Bedroom %d:\n\n", option+1);
            bed_arr[option].status = true;
        } else{
            printf("Use another number and choose one that's available.\n\n");
        }
    }while(!valid_bedroom);
    
    for(int i = 0;i<signed_up_clients;i++){
        printf("Client %d: %s", i+1, client_arr[i].name);
    }

    int client_choosing_option;
    bool valid_client = false;
    do{
        printf("\n\nChoose a client from the list (code): ");
        scanf("%d", &client_choosing_option);
        client_choosing_option--;
        if(client_choosing_option < 0 || client_choosing_option >= signed_up_clients){
            printf("Choose a client that's it's code is from 0 to %d", signed_up_clients);
        } else{
            valid_client = true;
        }
    }while(!valid_client);
    Reservation *new_reservation = &(*reserves_arr)[*reserves_count];
    //passar todos os dados
    strcpy(new_reservation->client.name, client_arr[client_choosing_option].name);
    strcpy(new_reservation->client.phone_number, client_arr[client_choosing_option].phone_number);
    strcpy(new_reservation->client.cpf, client_arr[client_choosing_option].cpf);

    new_reservation->bedroom.number = bed_arr[option].number;
    new_reservation->bedroom.type = bed_arr[option].type;

    printf("\n\n---- Check-in Date ----\n\n");
    int year, month, day;
    bool valid_check_in_date = false;
    bool valid_check_out_date = false;
    int count_days_ci = 0, count_days_co = 0;

    do{
        printf("\nYear: ");
        scanf("%d", &year);
        printf("\nMonth: ");
        scanf("%d", &month);
        printf("\nDay: ");
        scanf("%d", &day);

        valid_check_in_date = check_date(year, month, day);
        count_days_ci = count_checkin_days(year, month, day);

        if(!valid_check_in_date){
            printf("Invalid date.");
        } else{
            new_reservation->check_in_date[0] = day, new_reservation->check_in_date[1] = month, new_reservation->check_in_date[2] = year;
        }
        
    }while(!valid_check_in_date);

    printf("\n\n---- Check-out Date ----\n\n");
    do{
        printf("Year: ");
        scanf("%d", &year);
        printf("Month: ");
        scanf("%d", &month);
        printf("Day: ");
        scanf("%d", &day);

        valid_check_out_date = check_date(year, month, day);
        count_days_co = count_checkout_days(year, month, day);

        if(!valid_check_out_date || (count_days_co <= count_days_ci)){
            printf("\n\nInvalid Check-Out Date.\n\n");
        } else{
            new_reservation->check_out_date[0] = day, new_reservation->check_out_date[1] = month, new_reservation->check_out_date[2] = year;
            valid_check_out_date = true;
        }
        
    }while(!valid_check_out_date);
    (*reserves_count)++;
    printf("Validation for reservation was a sucess!\n\n");
}

void cancel_reservation(Reservation *reserves_arr, int *reserves_count, Bedroom bed_arr[], int size_array, int *available_bedrooms){
    if(*reserves_count == 0){
        printf("\n\nThere are no reservations to cancel.\n\n");
        return;
    }
    printf("%s", reserves_arr[0].client.name);
    
    int option;
        printf("\n\n---- Current Reservations ----\n\n");
        for(int i = 0;i < *reserves_count;i++){
            printf("\n\nReservation %d\n", i+1);
            printf("Bedroom number: %d\n", reserves_arr[i].bedroom.number);
            switch(reserves_arr[i].bedroom.type-1){
                case 2:
                    printf("Suite.");
                    break;
                case 1: 
                    printf("Couple.");
                    break;
                case 0:
                    printf("Single.");
                    break;
                default:
                    printf("Error. Report to developers.");
                    break;
            }
            printf("\nClient's name: %s", reserves_arr[i].client.name);
            printf("\nClient's phone-number: %s", reserves_arr[i].client.phone_number);
            printf("\nCPF: %s\n", reserves_arr[i].client.cpf);
            printf("\nCheck-in Date: %d/%d/%d", reserves_arr[i].check_in_date[0], reserves_arr[i].check_in_date[1], reserves_arr[i].check_in_date[2]);
            printf("\nCheck-out Date: %d/%d/%d", reserves_arr[i].check_out_date[0], reserves_arr[i].check_out_date[1], reserves_arr[i].check_out_date[2]);
        }
        bool valid_reserv_cancel_op;
        do{
            printf("\n\nType the reservation code to leave: ");
            scanf("%d", &option);
            option--;

            if(option < 0 || option >= *reserves_count){
                printf("\nInvalid number. \n\n");
            } else{ 
                printf("The cancelation for the reservation on bedroom %d was a sucess.\n", reserves_arr[option].bedroom.number);

                for(int i = 0;i < size_array;i++){
                    if(reserves_arr[option].bedroom.number == bed_arr[i].number){
                        bed_arr[i].status = false;
                        break;
                    }
                }
                for(int i = option;i < *reserves_count-1;i++){
                    reserves_arr[i] = reserves_arr[i+1];
                }
                (*reserves_count)--;
                valid_reserv_cancel_op = true;
            }
        }while(!valid_reserv_cancel_op);
        (*available_bedrooms)++;
}

void search_client(Client client_arr[], int signed_up_clients){
    char name_input[255];
    bool leave_search = false;
    char answer;
    do{
        printf("Name: ");
        getchar();
        fgets(name_input, 255, stdin);
        for(int i = 0;i < signed_up_clients;i++){
            if(strstr(client_arr[i].name, name_input) != NULL){
                printf("Client Name: %s", client_arr[i].name);
                printf("\nPhone-Number: %s", client_arr[i].phone_number);
                printf("\nCPF: %s\n", client_arr[i].cpf);
            }
        }
        printf("\n\nLeave? [Y/N]");
        scanf(" %c", &answer);
        if(tolower(answer) == 'y'){
            leave_search = true;
        }
        printf("\n\n");
    }while(!leave_search);
}

void search_bed_num(Bedroom bed_arr[], int size_arr){
    int number;
    char answer;

    bool valid_input = false;
    bool continue_search = false;
    bool item_not_found = false;
    do{
        printf("Number: ");
        scanf("%d", &number);
        item_not_found = false;
        for(int i = 0;i < size_arr;i++){
            if(bed_arr[i].number == number){
                item_not_found = true;
                printf("\n\nBedroom %d\n", i+1);
                printf("Number: %d\n", bed_arr[i].number);
                printf("Status: ");
                if(bed_arr[i].status){
                    printf("Reserved.\n");
                } else{
                    printf("Free.\n");
                }
                printf("Type: ");
                switch(bed_arr[i].type){
                    case 0:
                        printf("Single.\n");
                        break;
                    case 1:
                        printf("Couple.\n");
                        break;
                    case 2:
                        printf("Suite.\n");
                        break;
                    default:    
                        printf("\n\nEROR. REPORT TO DEVELOPERS.\n\n");
                        break;
                }
            }
        }
        if(!item_not_found){
            printf("\n\nNothing was found.\n\n");
        }
        printf("\n\nContinue Search? [Y/N]\n");
        do{
            printf("Answer: ");
            scanf(" %c", &answer);
            answer = tolower(answer);

            if(answer == 'y'){
                printf("\n\nContinuing...\n\n");
                continue_search = true;
                valid_input = true;
            } else if(answer == 'n'){
                continue_search = false;
                valid_input = true;
                printf("\nLeaving...\n");
            } else{
                printf("\n\nInvalid input.\n\n");
            }
            
        }while(!valid_input);
    }while(continue_search);
}

void search_resv(Reservation reserves_arr[], int reserves_count){
    for(int i = 0;i < reserves_count; i++){
        printf("\n\n---- Reservation %d Information ----\n\n", i+1);
        // listar bedrooms, listar clientes, listar check-in e checkout
        printf("Bedroom: %d\n", reserves_arr[i].bedroom.number); 
        printf("Type: ");
        switch(reserves_arr[i].bedroom.type){
            case 0:
                printf("Single.\n\n");
                break;
            case 1:
                printf("Couple.\n\n");
                break;
            case 2:
                printf("Suite.\n\n");
                break;
            default:
                printf("\n\n\n\n\nERROR. REPORT TO DEVELOPERS.\n\n\n\n");
                break;
        }
        printf("\nClient Information\n");
        printf("Name: %s", reserves_arr[i].client.name);
        printf("CPF: %s", reserves_arr[i].client.cpf);
        printf("Phone-Number: %s", reserves_arr[i].client.phone_number);
        printf("\n\nCheck-in & Check-out\n\n");
        printf("Check-in : %d/%d/%d\n", reserves_arr[i].check_in_date[0], reserves_arr[i].check_in_date[1], reserves_arr[i].check_in_date[2]);
        printf("Check-out: %d/%d/%d\n\n", reserves_arr[i].check_out_date[0], reserves_arr[i].check_out_date[1], reserves_arr[i].check_out_date[2]);
    }
}


void search(Client client_arr[], int signed_up_clients, Bedroom bed_arr[], int size_arr, int set_bedroom, Reservation reserves_arr[], int reserves_count){
    int option;
    do{
        printf("\n\n---- Search Menu ----\n\n[1] Search Clients\n[2] Search Bedrooms\n[3] Search Reserves\n[4] Leave Search\n\nOption: ");
        scanf("%d", &option);
        if(option <= 0 || option > 3){
            printf("\n\nInvalid input. Try again.\n\n");
        }
        switch(option){
            case 1:
                if(signed_up_clients){
                    search_client(client_arr, signed_up_clients);
                } else{
                    printf("\n\nNo clients to search.\n\n");
                }
                break;
            case 2:
                if(set_bedroom){
                    search_bed_num(bed_arr, size_arr);
                } else{
                    printf("\n\nNo bedrooms have been configured.\n\n");
                }
                break;
            case 3:
                if(reserves_count){
                    search_resv(reserves_arr, reserves_count);
                } else{
                    printf("\n\nThere are no reservations to search for.\n\n");
                }
                break;
            case 4:
                printf("\n\nLeaving....\n\n");
                break;
            default:
                printf("Bye.");
        }
    }while(option != 4);
}

int main(){

    Bedroom bedroom1, bedroom2, bedroom3, bedroom4, bedroom5;
    Bedroom bed_arr[] = {bedroom1, bedroom2, bedroom3, bedroom4, bedroom5};
    int size_arr = sizeof(bed_arr) / sizeof(bed_arr[0]);

    Client *client_arr = malloc(sizeof(Client));
    Reservation *reserves_arr = malloc(sizeof(Reservation));

    int signed_up_clients = 0;
    int reserves_count = 0;
    int available_bedrooms = 0;
    int quartos_unicos = 5;
    int set_bedrooms = 0;
    int option;

    for(int i = 0;i<size_arr;i++){
        bed_arr[i].type = 4;
        bed_arr[i].status = false;
        bed_arr[i].set = false;
    }

    do{
        option = menu();
        switch(option){
            case 1:
                add_bedroom(bed_arr, &quartos_unicos, signed_up_clients, client_arr, &set_bedrooms);
                break;
            case 2:
                sign_up(&client_arr, &signed_up_clients);
                break;
            case 3:
                make_reserve(&reserves_arr, &reserves_count, bed_arr, size_arr, client_arr, signed_up_clients, &set_bedrooms, &available_bedrooms);
                break;
            case 4:
                list_everything(bed_arr, quartos_unicos, signed_up_clients, client_arr);
                break;
            case 5:
                cancel_reservation(reserves_arr, &reserves_count, bed_arr, size_arr, &available_bedrooms);
                break;
            case 6:
                search(client_arr, signed_up_clients, bed_arr, size_arr, set_bedrooms, reserves_arr, reserves_count);
                break;
            case 7:
                printf("Leaving program....");
                break;
        }
    }while(option != 7);
    free(client_arr);
    free(reserves_arr);
    return 0;
}
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

void printBoard(char board[3][3]){
    int i = 0, j = 0;
    printf("\n\n");
    for(i = 0;i<3;i++){
        for(j = 0;j<3;j++){
            if(j != 2){
                printf("%c|", board[i][j]);
            } else{
                printf("%c", board[i][j]);
            }   
        }
        printf("\n");
    }
    printf("\n\n");
}

bool valid_position(char board[3][3], int position){
    if(position < 1 || position > 9){
        return false;
    }
    switch(position){
        case 1:
            if(board[0][0] != '-'){
                return false;
            } break;
        case 2:
            if(board[0][1] != '-'){
                return false;
            } break;
        case 3:
            if(board[0][2] != '-'){
                return false;
            } break;
        case 4:
            if(board[1][0] != '-'){
                return false;
            } break;
        case 5:
            if(board[1][1] != '-'){
                return false;
            } break;
        case 6:
            if(board[1][2] != '-'){
                return false;   
            } break;
        case 7:
            if(board[2][0] != '-'){
                return false;
            } break;
        case 8:
            if(board[2][1] != '-'){
                return false;
            } break;
        case 9:
            if(board[2][2] != '-'){
                return false;
            } break;
        default:
            return true;
    }
    return true;
}

void placeInput(char board[3][3], int *turn, int position){
    if(*turn == 1){
        switch(position){
            case 1: board[0][0] = 'X'; break;
            case 2: board[0][1] = 'X'; break;
            case 3: board[0][2] = 'X'; break;
            case 4: board[1][0] = 'X'; break;
            case 5: board[1][1] = 'X'; break;
            case 6: board[1][2] = 'X'; break;
            case 7: board[2][0] = 'X'; break;
            case 8: board[2][1] = 'X'; break;
            case 9: board[2][2] = 'X'; break;
        }
    } else{
        switch(position){
            case 1: board[0][0] = 'O'; break;
            case 2: board[0][1] = 'O'; break;
            case 3: board[0][2] = 'O'; break;
            case 4: board[1][0] = 'O'; break;
            case 5: board[1][1] = 'O'; break;
            case 6: board[1][2] = 'O'; break;
            case 7: board[2][0] = 'O'; break;
            case 8: board[2][1] = 'O'; break;
            case 9: board[2][2] = 'O'; break;
        }
    }
}


void playBoard(char board[3][3], int *turn, int *plays){
    int position;
    bool valid_play = false;
    
    do{
        if(*turn == 1){
            printf("\n\nPlayer 1 Turn");
        } else{
            printf("\n\nPlayer 2 Turn");
        }

        printBoard(board);
        printf("Position: ");
        scanf("%d", &position);
        valid_play = valid_position(board, position);
        if(!valid_play){
            printf("\n\nInvalid position!\n\n");
        } else{
            placeInput(board, turn, position);
            (*plays)++;
            valid_play = true;
            if(*turn == 1){
                *turn = 2;
            } else{
                *turn = 1;
            }
        }
    }while(!valid_play);
}

bool check_win(char board[3][3]){
    int i = 0;
    //check for p1 & p2 win through for-loops

    //straight lines
    for(i = 0; i < 3; i++){
        if(board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '-'){
            return true;
        }
    }
    //collumns
    for(i = 0;i<3;i++){
        if(board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '-'){
            return true;
        }
    }

    //diagonals
    if((board[1][1] == board[0][2] && board[0][2] == board[2][0] && board[1][1] != '-') || (board[1][1] == board[0][0] && board[0][0] == board[2][2] && board[1][1] != '-')){
        return true;
    }
    return false;
}

int main(){
    bool game_won = false;
    int turn = 1; // 1 -> p1; 2 -> p2;
    int plays = 0; //plays > 3 -> check for win idk
    char board[3][3] = {
        {'-', '-', '-'},
        {'-', '-', '-'},
        {'-', '-', '-'}
    };

    
    printf("Player 1: X\n");
    printf("Player 2: O\n\n");

    while(!game_won){

        //check_draw();
        if(plays >= 5){
            game_won = check_win(board);
        }
        if(game_won){
            printBoard(board);
            printf("Someone won!\n\n");
        } else{
            playBoard(board, &turn, &plays);
        }
    }


    return 0;
}
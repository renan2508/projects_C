#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define SUM (a+b)
#define SUB (a-b)
#define MULTI (a*b)
#define DIV (a/b)

bool is_number(char number1[], char number2[], int number_turn){
    int size = strlen(number1);
    int size2= strlen(number2);

    if(number1[size-1] == '\n'){
        number1[size-1] = '\0';
        size--;
    }

    if(number2[size2-1] == '\n'){
        number2[size2-1] = '\0';
        size2--;
    }

    int count = 0;

    if(number_turn == 1){
        count = 0;
        for(int i = 0;i<size;i++){
            if(isdigit(number1[i]) != 0){
                count++;
            }
        }
        if(count == size){
            return true;
        }
    }
    if(number_turn == 2){
        count = 0;
        for(int i = 0;i<size2;i++){
            if(isdigit(number2[i]) != 0){
                count++;
            }
        }
        if(count == size2){
            return true;
        }
    }
    return false;
}

int main(){
    bool valid_input = false;
    char number1[255], number2[255];
    int n1, n2;
    int number_turn = 1; // 1-> n1, 2-> n2
    do{

        printf("Value of number 1: ");
        fgets(number1, 255, stdin);
        valid_input = is_number(number1, number2, number_turn);
        if(!valid_input){
            printf("\n\nThat's... not a number.\n\n");
        } else{
            valid_input = true;
            number_turn = 2;
            n1 = atoi(number1);
        }

    }while(!valid_input);

    do{

        printf("Value of number 2: ");
        fgets(number2, 255, stdin);
        valid_input = is_number(number1, number2, number_turn);
        if(!valid_input){
            printf("\n\nThat's... not a number.\n\n");
        } else{
            valid_input = true;
            number_turn = 1;
            n2 = atoi(number2);
        }
    }while(!valid_input);
    
    char op;
    
    do{
        printf("\nCalculator \n\n[1] Sum (+) \n[2] Subtraction (-)\n[3] Multiplication\n[4] Division\n[5] Squareroot\n[6] Log\nOption:  ");
        scanf(" %c", &op);
        if(isdigit(op) == 0){
            printf("\n\nThats an invalid operator.");
        } 
        else{
            switch(op){
                case '1': printf("\n\nThe sum between %d and %d is %d\n\n", n1, n2, SUM(n1, n2)); break;
                case '2': printf("\n\nSubtracting %d from %d: \n Or... subtracting %d from %d: %d\n", n1, n2, SUB(n2, n1), n2,n1, SUB(n1, n2)); break;
                case '3': printf("\n\nMultiplying %d with %d is %d", n1, n2, MULTI(n1, n2));
                case '4': printf("\n\nDividing %d by %d: %d.\nOr... dividing %d by %d: %d", n1, n2, DIV(n1,n2), n2, n1, DIV(n2, n1));

                case '5': printf("\n\n")
            }
        }
    }while(op != 7);


    return 0;
}
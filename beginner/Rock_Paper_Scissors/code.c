#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void win(){
    printf("You won!");
}
void tie(){
    printf("That was a tie!");
}
void lose(){
    printf("You lost!");
}
int main(){

    int choice, PCNumberGuess;
    //gera um numero aleatório
    srand(time(NULL));
    PCNumberGuess = rand() % 3 +1;
    
    printf("Choose your fighter:\n [1] Rock\n [2] Paper\n [3] Scissors\n");
    scanf("%d", &choice);
    printf("%d\n", PCNumberGuess);

    if(choice == PCNumberGuess){
        tie();
    }
    else if(choice == 1 && PCNumberGuess == 2){
        lose();
    }
    else if(choice == 1 && PCNumberGuess == 3){
        win();
    }
    else if(choice == 2 && PCNumberGuess == 1){
        win();
    }
    else if(choice == 2 && PCNumberGuess == 3){
        lose();
    }
    else if(choice == 3 && PCNumberGuess == 2){
        win();
    }
    else if(choice == 3 && PCNumberGuess == 1){
        lose();
    }
    else{
        printf("Kaboom");
    }
    return 0;
}
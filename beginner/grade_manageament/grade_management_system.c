#include <stdio.h>

void PrintArray(int Qtd_Alunos, int ArrayNotas[]){
    printf("\nStudent's grades: \n[ ");
    for(int i=0;i<Qtd_Alunos;i++){
        printf("%d ", ArrayNotas[i]);
    }
    printf("]\n\n");
}

float AverageCalculator(int Qtd_Alunos, int ArrayNotas[]){
    int Total=0;

    for(int i=0;i<Qtd_Alunos;i++){
        Total = Total + ArrayNotas[i];
    }
    return (float)Total/Qtd_Alunos;
}

int MaxFinder(int Qtd_Alunos,  int ArrayNotas[]){
    int Highest = ArrayNotas[0];

    for(int i=0;i<Qtd_Alunos;i++){
        if(ArrayNotas[i] > Highest){
            Highest = ArrayNotas[i];
        }
    }
    return Highest;
}

int LowFinder(int Qtd_Alunos, int ArrayNotas[]){
    int Lowest = ArrayNotas[0];

    for(int i=0;i<Qtd_Alunos;i++){
        if(ArrayNotas[i] < Lowest){
            Lowest = ArrayNotas[i];
        }
    }
    return Lowest;
}

void Sorter(int Qtd_Alunos, int ArrayNotas[]){
    int option;
    do{
        printf("Decrescent or increasing: \n[1] Decrescent\n[2] Increasing\n ");
        scanf("%d", &option);
        if(option != 1 && option != 2){
            printf("It needs to be either 1 or 2.");
        }
    }while(option != 1 && option != 2);
    if(option == 1){
        for(int i=0;i<Qtd_Alunos-1;i++){
            for(int j=0;j<Qtd_Alunos-1-i;j++){
                if(ArrayNotas[j] < ArrayNotas[j+1]){
                    int temp = ArrayNotas[j];
                    ArrayNotas[j] = ArrayNotas[j+1];
                    ArrayNotas[j+1] = temp;
                }
            }
        }
        for(int i=0;i<Qtd_Alunos;i++){
            printf("%d ", ArrayNotas[i]);
        }
    } else if(option == 2){
        for(int i=0;i<Qtd_Alunos-1;i++){
            for(int j=0;j<Qtd_Alunos-1-i;j++){
                if(ArrayNotas[j] > ArrayNotas[j+1]){
                    int temp = ArrayNotas[j];
                    ArrayNotas[j] = ArrayNotas[j+1];
                    ArrayNotas[j+1] = temp;
                }
            }
        }
        printf("[ ");
        for(int i=0;i<Qtd_Alunos;i++){
            printf("%d ", ArrayNotas[i]);
        }
        printf("]");
    }
}

int main(){
    int Qtd_Alunos;
    do{
        printf("Amount of students: ");
        scanf("%d", &Qtd_Alunos);
        if(Qtd_Alunos < 0 || Qtd_Alunos >= 99){
            printf("\nIt needs to be higher than 0, and lower than 99.\n\n");
        }
    }while(Qtd_Alunos < 0 || Qtd_Alunos >= 99);

    int ArrayNotas[Qtd_Alunos], i;

    for(i=0;i<Qtd_Alunos;i++){
        printf("Student %d: ", i);
        scanf("%d", &ArrayNotas[i]);
    }

    PrintArray(Qtd_Alunos, ArrayNotas);
    printf("\nAverage of all the grades: %.2f\n\n", AverageCalculator(Qtd_Alunos, ArrayNotas));
    printf("Highest grade: %d\n", MaxFinder(Qtd_Alunos, ArrayNotas));
    printf("Lowest grade: %d\n\n", LowFinder(Qtd_Alunos, ArrayNotas));
    Sorter(Qtd_Alunos, ArrayNotas);


    return 0;
}
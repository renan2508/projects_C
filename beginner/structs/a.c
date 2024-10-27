#include <stdio.h>


int main(){

    int idk[3];
    int post[3];
    int day_count_date1;
    int day_count_date2;
    idk[0] = 2;
    idk[1] = 11;
    idk[2] = 2023;
    post[0] = 3;
    post[1] = 11;
    post[2] = 2023;
    while(idk[2] != 0){
        idk[2]--;
        idk[1] += 12;
    }
    day_count_date1 = idk[0] + (30*idk[1]);
    while(post[2] != 0){
        post[2]--;
        post[1] += 12;
    }
    day_count_date2 = post[0] + (30*post[1]);
    printf("%d\n", day_count_date1);
    printf("%d\n", day_count_date2);
    if(day_count_date2 > day_count_date1){
        printf("Tudo certo.\n");
    } else{
        printf("Tudo errado.\n\n");
    }


    return 0;
}
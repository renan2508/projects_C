#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(){

    char palavra[100] = "BANANA";
    char used_chars[100];
    int used_chars_count = 0;
    char current[100];
    char user_answer;

    int size = strlen(palavra);

    for(int i = 0;i<size;i++){
        current[i] = '_';
    }
    current[size] = '\0';
    
    printf("\n\n%s\n\n", current);
    int mistakes=0;
    while(mistakes != 7){
        int found = 0;

        printf("\nCharacter: ");
        scanf(" %c", &user_answer);
        
        for(int i = 0; i < size;i++){
            if(tolower(user_answer) == tolower(palavra[i])){
                current[i] = toupper(user_answer);
                found = 1;
            }
        }
        if(!found){
            mistakes++;
            printf("Wrong character! %d of 7 mistakes.", mistakes);
        }
        used_chars[used_chars_count] = toupper(user_answer);
        used_chars_count++;

        printf("\n%s\n", current);
        if(used_chars_count){
            for(int i = 0; i < used_chars_count;i++){
                if(tolower(user_answer) == used_chars[i]){
                    printf("You already utilized this character.");
                }
                else{}
            }
            printf("\n\nUtilized characters: ");
                for(int i = 0 ; i < used_chars_count;i++){
                    if(i == used_chars_count-1){
                        printf("%c.\n", used_chars[i]);
                    } else{
                        printf("%c, ", used_chars[i]);
                    }
                }
        }
        if(mistakes == 7){
            printf("\n\nYou lost! The word was %s!\n\n", palavra);
        }
        if(strcmp(current, palavra) == 0){
            printf("\n\nYou won!\n\n");
            break;
        }
    }
    return 0;
}
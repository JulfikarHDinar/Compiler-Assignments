/*
                  Ahsanullah University of Science and Technology
                  Department of Computer Science and Engineering
                  CSE 4130 (FALL 2020)                       Exam: Online 1
                   Set:                                                        ID: 170204055
               */

#include <stdio.h>
void integerCount(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]);

int main(){
    char sourceFileName[30] = "TaskOne.txt";
    char targetFileName[30] = "final.txt";
    FILE *source, *target;

    source = fopen(sourceFileName, "r");
    target = fopen(targetFileName, "w");

    integerCount(source, target, sourceFileName, targetFileName);

    printf("\n\n");

    //removing the file after operation
    remove (targetFileName);
    return 0;
}

void integerCount(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]){
    char c;
    int count = 0;

    if(source == NULL){
        printf("\nFile cannot be opened");
    }
    else{
        while( (c = fgetc(source)) != EOF ){
            if( (c == '&') ){
                count ++;
                continue;
            }

        }
    }
    fclose(source);
    fclose(target);

    printf("No. of Integer Numbers read: %d", count);
    fclose(target);
}


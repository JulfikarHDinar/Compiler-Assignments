/*
    Write a program to print the header files used in a source program.
*/
#include <stdio.h>
#include <math.h>
void headerPrint(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]);

int main(){
    char sourceFileName[30] = "TaskOne.c";
    char targetFileName[30] = "TaskOne.txt";
    FILE *source, *target;

    source = fopen(sourceFileName, "r");
    target = fopen(targetFileName, "w");

    headerPrint(source, target, sourceFileName, targetFileName);

    printf("\n\n");

    //removing the file after operation
    remove (targetFileName);
    return 0;
}

void headerPrint(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]){
    char c;
    int check = 0;

    if(source == NULL){
        printf("\nFile cannot be opened");
    }
    else{
        while( (c = fgetc(source)) != '{' ){
            if( (c == 60) ){
                check = 1;
                continue;
            }
            else if( (c == 62) ){
                fputc(10,target);
                check = 0;
                continue;
            }

            if(check){
                fputc(c,target);
            }
        }
    }
    fclose(source);
    fclose(target);

    target = fopen (targetFileName,"r");
    while( (c = fgetc(target)) != EOF){
        printf("%c",c);
    }
    fclose(target);
}


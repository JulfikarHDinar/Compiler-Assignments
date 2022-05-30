#include <stdio.h>
void lineNumberPrint(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]);

int main(){
    char sourceFileName[30] = "TaskTwo.c";
    char targetFileName[30] = "TaskTwo.txt";
    FILE *source, *target;

    source = fopen(sourceFileName, "r");
    target = fopen(targetFileName, "w");

    lineNumberPrint(source, target, sourceFileName, targetFileName);

    printf("\n\n");
    //removing the file after operation
    remove (targetFileName);
    return 0;
}

void lineNumberPrint(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]){
    char c;
    int lineNo = 1;
    char lineNoBuffer[20];
    itoa(lineNo,lineNoBuffer,10);


    if(source == NULL){
        printf("\nFile cannot be opened");
    }
    else{
        itoa(lineNo, lineNoBuffer,10);
        fputs(lineNoBuffer,target);
        fputs(": ",target);
        while( (c = fgetc(source)) != EOF ){
            if( (c == 10) ){
                fputc(10,target);
                lineNo++;
                itoa(lineNo,lineNoBuffer,10);
                fputs(lineNoBuffer,target);
                fputs(": ",target);
                continue;
            }

            fputc(c,target);
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

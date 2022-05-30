#ifndef _STEPFOUR_H_
#define _STEPFOUR_H_
#include<stdio.h>
#include "StepFourCodeCleaning.h"
#include "StepFourLexemeOperation.h"
#include "StepFourErrorChecking.h"

void lineNumberPrint(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]);

void stepFourErrorCheck(FILE *source, char sourceFileName_0[30]){
    char targetFileName_1[30] = "170204055_Asm4_Out1.txt";  //removed comment output
    char targetFileName_2[30] = "170204055_Asm4_Out2.txt";  //removed space output
    char targetFileName_3[30] = "170204055_Asm4_Out3.txt";  //lexeme separator output
    char targetFileName_4[30] = "170204055_Asm4_Out4.txt";  //lexeme tokenized output
    char targetFileName_5[30] = "170204055_Asm4_Out5.txt";  //line number output
    char targetFileName_6[30] = "170204055_Asm4_Out6.txt";  //Error output
    FILE *target;

    ///removing comment
    source = fopen(sourceFileName_0, "r");
    target = fopen(targetFileName_1, "w");
    removeComments(source, target, sourceFileName_0, targetFileName_1);

    ///removing spaces
    source = fopen(targetFileName_1, "r");
    target = fopen(targetFileName_2, "w");
    removeSpaces(source, target, targetFileName_1, targetFileName_2);

    ///lexeme separator
    source = fopen(targetFileName_2, "r");
    target = fopen(targetFileName_3, "w");
    lexemeSeparator(source, target, targetFileName_2, targetFileName_3);

    ///lexeme tokenized
    source = fopen(targetFileName_3, "r");
    target = fopen(targetFileName_4, "w");
    lexemeTokenization(source, target, targetFileName_3, targetFileName_4);

    ///lexeme tokenized
    source = fopen(targetFileName_4, "r");
    target = fopen(targetFileName_5, "w");
    lineNumberPrint(source, target, targetFileName_4, targetFileName_5);

    ///  printing in console
    char c;
    target = fopen (targetFileName_5,"r");
    while( (c = fgetc(target)) != EOF){
        printf("%c",c);
    }
    fclose(target);
    printf("\n\n");

    printf("\n============== Errors ==============\n\n");
    ///Finding Errors
    source = fopen(targetFileName_5, "r");
    target = fopen(targetFileName_6, "w");
    findErrors(source, target, targetFileName_5, targetFileName_6);

    printf("\n\n");

    ///removing the file after operation
    remove (targetFileName_1);
    remove (targetFileName_2);
    remove (targetFileName_3);
    remove (targetFileName_4);
    remove (targetFileName_5);
    remove (targetFileName_6);
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
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
}

#endif

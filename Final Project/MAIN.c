#include<stdio.h>
#include<string.h>
#include"StepOne.h"
#include"StepTwo.h"
#include"StepThree.h"
#include"StepFour.h"

int main() {
    char c;
    int i;
    char inputString[2000];
    FILE *source, *target, *temp;

    printf("Type the Code:\n[Enter the tilde operator '~' to end of the code]\n\n");
    scanf("%[^~]s", inputString);

    char inputFileName[30] = "InputFile.txt";
    target = fopen(inputFileName, "w");

    for(i=0; i<strlen(inputString); i++){
        fputc(inputString[i],target);
    }
    fclose(target);
    printf("\n\n");

    /// -------------------------------------  Step One  ------------------------------------- ///
    char sourceFileName1[30] = "InputFile.txt";
    char tempFileName1_2[30] = "temp.txt";
    char targetFileName1_1[30] = "170204055_Asm1_1.txt";
    char targetFileName1_2[30] = "170204055_Asm1_2.txt";

    source = fopen(sourceFileName1, "r");
    temp = fopen(tempFileName1_2, "w");
    omitComments1(source, temp, sourceFileName1, tempFileName1_2);
    temp = fopen(tempFileName1_2, "r");
    target = fopen(targetFileName1_2, "w");
    omitSpaces1(temp, target, tempFileName1_2, targetFileName1_2);

    printf("||--------------------------------------------------------------------------------------||\n");
    printf("||-------------------------------------  Step One  -------------------------------------||\n");
    printf("\tThe code after removing the comments and white space (extra spaces, tabs and newline characters): \n\n");
    target = fopen (targetFileName1_2,"r");
    while( (c = fgetc(target)) != EOF){
        printf("%c",c);
    }
    fclose(target);
    remove(targetFileName1_1);
    //remove(targetFileName1_2);
    remove(tempFileName1_2);

    printf("\n\n\n");
    /// -------------------------------------  Step Two  ------------------------------------- ///
    char sourceFileName2[30] = "170204055_Asm1_2.txt";
    char tempFileName2[30] = "170204055_Asm2_O1.txt";
    char targetFileName2[30] = "170204055_Asm2_O2.txt";
    // Lexeme separator
    source = fopen(sourceFileName2, "r");
    temp = fopen(tempFileName2, "w");
    lexemeSeparator2(source, temp, sourceFileName2, tempFileName2);

    //  Lexeme Categorizer
    temp = fopen(tempFileName2, "r");
    target = fopen(targetFileName2, "w");
    lexemeTokenization2(temp, target, tempFileName2, targetFileName2);

    printf("||--------------------------------------------------------------------------------------||\n");
    printf("||-------------------------------------  Step Two  -------------------------------------||\n");
    printf("\tLexeme Tokenized: \n\n");
    //  printing in console
    target = fopen (targetFileName2,"r");
    while( (c = fgetc(target)) != EOF){
        printf("%c",c);
    }
    fclose(target);
    remove(targetFileName1_2);
    remove(tempFileName2);

    printf("\n\n\n");
    /// -------------------------------------  Step Three  ------------------------------------- ///
    char sourceFileName3[30] = "170204055_Asm2_O2.txt";
    char targetFileName3_1[30] = "170204055_Asm3_O1.txt";
    char targetFileName3_2[30] = "170204055_Asm3_T2.txt";

    printf("||----------------------------------------------------------------------------------------||\n");
    printf("||-------------------------------------  Step Three  -------------------------------------||\n\n");
    //////      Lexeme Simplify
    source = fopen(sourceFileName3, "r");
    target = fopen(targetFileName3_1, "w");
    lexemeSimplify3(source, target, sourceFileName3, targetFileName3_1);

    //////      Symbol Table
    source = fopen(targetFileName3_1, "r");
    target = fopen(targetFileName3_2, "w");
    symbolTableGenerate3(source, target, sourceFileName3, targetFileName3_1);

    remove(sourceFileName3);
    remove(targetFileName3_1);
    remove(targetFileName3_2);

    printf("\n");
    /// -------------------------------------  Step Four  ------------------------------------- ///
    printf("||---------------------------------------------------------------------------------------||\n");
    printf("||-------------------------------------  Step Four  -------------------------------------||\n\n");
    char sourceFileName4[30] = "InputFile.txt";
    source = fopen(sourceFileName4, "r");
    stepFourErrorCheck(source, sourceFileName4);

    fclose(source);
    remove(sourceFileName4);
    printf("\n\n\n\n\n");
    return 0;
}

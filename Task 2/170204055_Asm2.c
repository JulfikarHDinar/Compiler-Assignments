/*
    Suppose, we have a C source program scanned and filtered as it was done in Session 1. We now take
    that modified file as input, and separate the lexemes first. We further recognize and mark the
    lexemes as different types of tokens like keywords, identifiers, operators, separators, parenthesis,
    numbers, etc.
    Sample Input:
    char c; int x1, x_2; float y1, y2; x1=5; x_2= 10; y1=2.5+x1*45; y2=100.o5-x_2/3; if(y1<=y2) c='y'; else
    c='n';

    Step 1: Lexemes are separated. Mark that two-character relational operators are also distinguished
    beside separators, one-character operators, parenthesis, number constants and alphanumeric strings
    with or without underscore.
        char c ; int x1 , x_2 ; float y1 , y2 ; x1 = 5 ; x_2 = 10 ; y1 = 2.5 + x1 * 45 ; y2 = 100.o5 - x_2 / 3 ; if ( y1
        <= y2 ) c = ' y ' ; else c = ' n ' ;

    Step 2: Lexemes are categorized under the categories kw for keyword, id for identifier, etc. Some may
    be labeled unkn (unknown)
        [kw char] [id c] [sep ;] [kw int] [id x1] [sep ,] [id x_2] [sep ;] [kw float] [id y1] [sep ,] [id y2] [sep ;] [id
        x1] [op =] [num 5] [sep ;] [id x_2] [op =] [num 10] [sep ;] [id y1] [op =] [num 2.5] [op +] [id x1] [op *]
        [num 45] [sep ;] [id y2] [op =] [unkn 100.o5] [op -] [id x_2] [op /] [num 3] [sep ;] [kw if] [par (] [id y1]
        [op <=] [id y2] [par )] [id c] [op =] [sep '] [id y] [sep '] [sep ;] [kw else] [id c] [op =] [sep '] [id n] [sep ']
        [sep ;]
*/
#include <stdio.h>
#include <string.h>

void lexemeSeparator(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]);
void lexemeTokenization(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]);
int isNumerical(char *lex);
int isSeparator(char *lex);
int isParenthesis(char *lex);
int isOperator(char *lex);
int isIdentifier(char *lex);
int isKeyword(char *lex);

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    char c;
    char sourceFileName[30] = "170204055_Asm2_Input.txt";
    char tempFileName[30] = "LexemeSeparatedTemp.txt";
    char targetFileName[30] = "170204055_Asm2_Output.txt";
    FILE *source, *target, *temp;

    // Lexeme separator
    source = fopen(sourceFileName, "r");
    temp = fopen(tempFileName, "w");
    lexemeSeparator(source, temp, sourceFileName, tempFileName);

    //  Lexeme Categorizer
    temp = fopen(tempFileName, "r");
    target = fopen(targetFileName, "w");
    lexemeTokenization(temp, target, tempFileName, targetFileName);

    //  printing in console
    target = fopen (targetFileName,"r");
    while( (c = fgetc(target)) != EOF){
        printf("%c",c);
    }
    fclose(target);

    //removing text file after operation
    remove(tempFileName);
    remove(targetFileName);
    printf("\n\n");
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
void lexemeSeparator(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]){
    char c;
    int lexemeStart = 0;
    char tempFileName[30] = "temp1.txt";
    FILE *temp;
    temp = fopen(tempFileName, "w");
    if(source == NULL || target == NULL || temp == NULL){
        printf("\nFile cannot be opened");
    }
    else{
        while( (c = fgetc(source)) != EOF ){
            if(c == ' '){
                fputc(c,temp);
                lexemeStart = 0;
                continue;
            }
            if(c != ' ' && lexemeStart == 0){
                lexemeStart = 1;
            }
            if(lexemeStart == 1){
                if(c == ';' || c == ',' || c == 39 || c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '(' || c == ')'){    //apostrophe ascii = 39
                    fputc(' ',temp);      //leading space of the lexeme
                    fputc(c,temp);
                    lexemeStart = 0;
                    char cc = fgetc(source);
                    if (cc == '+' || cc == '-' ){
                        fputc(cc,temp);
                        fputc(' ',temp);  //trailing space of the lexeme
                    }
                    else if (cc == ';'){  //semicolon after apostrophe
                        fputc(' ',temp);  //leading space of the lexeme
                        fputc(cc,temp);
                        fputc(' ',temp);  //trailing space of the lexeme
                    }
                    else{
                        fputc(' ',temp);  //leading space of the lexeme
                        fputc(cc,temp);
                    }
                    continue;
                }
                else if(c == '>' || c == '<' || c == '!' || c == '|' || c == '&' || c == '='){
                    fputc(' ',temp);      //leading space of the lexeme
                    fputc(c,temp);
                    lexemeStart = 0;
                    char cc = fgetc(source);
                    if (cc == '=' || cc == '|' || cc == '&'){   //for checking  >=  <=  !=  &&  ||
                        fputc(cc,temp);
                        fputc(' ',temp);  //trailing space of the lexeme
                    }
                    else if (cc == 39){     //apostrophe ASCII = 39
                        fputc(' ',temp);  //leading space of the lexeme
                        fputc(cc,temp);
                        fputc(' ',temp);  //trailing space of the lexeme
                    }
                    else{
                        fputc(' ',temp);  //leading space of the lexeme
                        fputc(cc,temp);
                    }
                    continue;
                }
                fputc(c,temp);
            }
        }
    }
    fputc(' ',temp);
    fclose(source);
    fclose(temp);

    //Removing more than one spaces
    int syntaxSpace = 0;
    int codeStart = 0;
    source = fopen(tempFileName, "r");

    while( (c = fgetc(source)) != EOF ){
        if(c == 32 && syntaxSpace == 0 && codeStart == 1){          //one space between syntaxes
            fputc(32,target);
            syntaxSpace = 1;
            continue;
        }
        else if(c == 32 && syntaxSpace == 1 && codeStart == 1){     //more than one space between syntaxes
            continue;
        }
        else if(c != 32){                                           //any character other than space
            fputc(c,target);
            codeStart = 1;
            syntaxSpace = 0;
        }
    }
    fclose(source);
    fclose(target);
    remove(tempFileName);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
void lexemeTokenization(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]){
    char c, lex[50];
    if(source == NULL || target == NULL){
        printf("\nFile cannot be opened");
    }
    else{
        int i = 0;
        while( (c = fgetc(source)) != EOF ){
            if(c == ' '){       //checking each lexeme separately and putting them in target file
                lex[i] = '\0';
                i=0;
                if(isSeparator(lex)){
                    fputs("[sep ", target);
                    fputs(lex, target);
                    fputs("] ", target);
                }
                else if(isParenthesis(lex)){
                    fputs("[par ", target);
                    fputs(lex, target);
                    fputs("] ", target);
                }
                else if(isOperator(lex)){
                    fputs("[op ", target);
                    fputs(lex, target);
                    fputs("] ", target);
                }
                else if(isNumerical(lex)){
                    fputs("[num ", target);
                    fputs(lex, target);
                    fputs("] ", target);
                }
                else if(isKeyword(lex)){
                    fputs("[kw ", target);
                    fputs(lex, target);
                    fputs("] ", target);
                }
                else if(isIdentifier(lex)){
                    fputs("[id ", target);
                    fputs(lex, target);
                    fputs("] ", target);
                }
                else {
                    fputs("[unkn ", target);
                    fputs(lex, target);
                    fputs("] ", target);
                }

                continue;
            }
            else{
                lex[i] = c;
                i++;
            }
        }
    }
    fclose(source);
    fclose(target);
}

//////////////////////////////////////////////
//////////////////////////////////////////////
int isNumerical(char *lex){
    int i, l, s;
    i=0;
    if(isdigit(lex[i])) {
        s=1; i++;
    }
    else if(lex[i]=='.') {
        s=2;
        i++;
    }
    else
        s=0;
    l=strlen(lex);
    if(s==1){
        for(;i<l;i++){
            if(isdigit(lex[i]))
                s=1;
            else if(lex[i]=='.') {
                s=2;
                i++;
                break;
            }
            else {
                s=0;
                break;
            }
        }
    }
    if(s==2){
        if(isdigit(lex[i])) {
            s=3; i++;
        }
        else
            s=0;
    }
    if(s==3){
        for(;i<l;i++) {
            if(isdigit(lex[i]))
                s=3;
            else {
                s=0;
                break;
            }
        }
    }
    if(s==3){
        s=1;
    }
    return s;
}

//////////////////////////////////////////////
//////////////////////////////////////////////
int isSeparator(char *lex){
    int s = 0 ;

    if( lex[0] == ';' || lex[0] == ',' || lex[0] == 39 ){
        s = 1;
    }
   return s;
}

//////////////////////////////////////////////
//////////////////////////////////////////////
int isParenthesis(char *lex){
    int s = 0 ;

    if( lex[0] == '(' || lex[0] == ')' || lex[0] == '{' || lex[0] == '}' ){
        s = 1;
    }
   return s;
}

//////////////////////////////////////////////
//////////////////////////////////////////////
int isOperator(char *lex){
    int s = 0 ;

    if(strlen(lex) == 1){       //single operator
        if( lex[0] == '+' || lex[0] == '-' || lex[0] == '*' || lex[0] == '/' || lex[0] == '%' || lex[0] == '=' ||
           lex[0] == '<' || lex[0] == '>' || lex[0] == '!' || lex[0] == '&' || lex[0] == '|' || lex[0] == '~' || lex[0] == '^' ){
            s = 1;
        }
    }
    if(strlen(lex) == 2){       //double operator
        if( (lex[0] == '+' && lex[1] == '+') || (lex[0] == '-' && lex[1] == '-') || (lex[0] == '=' && lex[1] == '=') || (lex[0] == '!' && lex[1] == '=') ||
           (lex[0] == '|' && lex[1] == '|') || (lex[0] == '&' && lex[1] == '&') || (lex[0] == '>' && lex[1] == '=') || (lex[0] == '<' && lex[1] == '=') ){
            s = 1;
        }
    }
    return s;
}

//////////////////////////////////////////////
//////////////////////////////////////////////
int isIdentifier(char *lex){
    int s = 0 ;

    if((lex[0] >= 'a' && lex[0] <= 'z') || (lex[0] >= 'A' && lex[0] <= 'Z') || lex[0] == '_' ){
        s = 1;      //checking first character if it's valid or not (a-z) || (A-Z) || _
    }

    if (s==0)
        return s ;
    else{
        int i;
        for ( i = 1 ; i<strlen(lex); i++){
            if((lex[i] >= 'a' && lex[i] <= 'z') || (lex[i] >= 'A' && lex[i] <= 'Z') || lex[i] == '_' || (lex[i] >= '0' && lex[i] <= '9') ){
                continue;
            }
            else{
                s = 0;
            }
        }
    }
    return s ;
}

//////////////////////////////////////////////
//////////////////////////////////////////////
int isKeyword(char *lex){
    int s = 0 ;

    if(lex[0] == 'i' && lex[1] == 'n' && lex[2] == 't' ){
        s = 1;      //int
    }
    else if(lex[0] == 'c' && lex[1] == 'h' && lex[2] >= 'a' && lex[3] == 'r'){
        s = 1;      //char
    }
    else if(lex[0] == 'f' && lex[1] == 'l' && lex[2] >= 'o' && lex[3] == 'a' && lex[4] == 't'){
        s = 1;      //float
    }
    else if(lex[0] == 'd' && lex[1] == 'o' && lex[2] >= 'u' && lex[3] == 'b' && lex[4] == 'l' && lex[5] == 'e'){
        s = 1;      //double
    }
    else if(lex[0] == 'l' && lex[1] == 'o' && lex[2] >= 'n' && lex[3] == 'g'){
        s = 1;      //long
    }
    else if(lex[0] == 's' && lex[1] == 'h' && lex[2] >= 'o' && lex[3] == 'r' && lex[4] == 't'){
        s = 1;      //short
    }
    else if(lex[0] == 'w' && lex[1] == 'h' && lex[2] >= 'i' && lex[3] == 'l' && lex[4] == 'e'){
        s = 1;      //while
    }
    else if(lex[0] == 'f' && lex[1] == 'o' && lex[2] >= 'r'){
        s = 1;      //for
    }
    else if(lex[0] == 'd' && lex[1] == 'o'){
        s = 1;      //do
    }
    else if(lex[0] == 'i' && lex[1] == 'f'){
        s = 1;      //if
    }
    else if(lex[0] == 'e' && lex[1] == 'l' && lex[2] >= 's' && lex[3] == 'e'){
        s = 1;      //else
    }
    else if(lex[0] == 'v' && lex[1] == 'o' && lex[2] >= 'i' && lex[3] == 'd'){
        s = 1;      //void
    }
    else if(lex[0] == 's' && lex[1] == 't' && lex[2] >= 'a' && lex[3] == 't' && lex[4] == 'i' && lex[5] == 'c'){
        s = 1;      //static
    }
    else if(lex[0] == 'b' && lex[1] == 'r' && lex[2] >= 'e' && lex[3] == 'a' && lex[4] == 'k'){
        s = 1;      //break
    }
    else if(lex[0] == 'c' && lex[1] == 'o' && lex[2] >= 'n' && lex[3] == 't' && lex[4] == 'i' && lex[5] == 'n' && lex[6] == 'u' && lex[7] == 'e'){
        s = 1;      //continue
    }
    else if(lex[0] == 'd' && lex[1] == 'e' && lex[2] >= 'f' && lex[3] == 'a' && lex[4] == 'u' && lex[5] == 'l' && lex[6] == 't'){
        s = 1;      //default
    }
    else if(lex[0] == 'c' && lex[1] == 'o' && lex[2] >= 'n' && lex[3] == 's' && lex[4] == 't'){
        s = 1;      //const
    }
    else if(lex[0] == 's' && lex[1] == 'w' && lex[2] >= 'i' && lex[3] == 't' && lex[4] == 'c' && lex[5] == 'h'){
        s = 1;      //switch
    }
    else if(lex[0] == 'c' && lex[1] == 'a' && lex[2] >= 's' && lex[3] == 'e'){
        s = 1;      //case
    }
    else if(lex[0] == 's' && lex[1] == 'i' && lex[2] >= 'z' && lex[3] == 'e' && lex[4] == 'o' && lex[5] == 'f'){
        s = 1;      //sizeof
    }
    else if(lex[0] == 's' && lex[1] == 't' && lex[2] >= 'r' && lex[3] == 'u' && lex[4] == 'c' && lex[5] == 't'){
        s = 1;      //struct
    }
    else if(lex[0] == 's' && lex[1] == 'i' && lex[2] >= 'g' && lex[3] == 'n' && lex[4] == 'e' && lex[5] == 'd'){
        s = 1;      //signed
    }
    else if(lex[0] == 'u' && lex[1] == 'n' && lex[2] >= 's' && lex[3] == 'i' && lex[4] == 'g' && lex[5] == 'n' && lex[6] == 'e' && lex[7] == 'd'){
        s = 1;      //unsigned
    }
    else if(lex[0] == 'r' && lex[1] == 'e' && lex[2] >= 't' && lex[3] == 'u' && lex[4] == 'r' && lex[5] == 'n'){
        s = 1;      //return
    }

    return s ;
}

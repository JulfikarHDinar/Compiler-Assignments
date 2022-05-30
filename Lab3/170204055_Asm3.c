#include <stdio.h>
#include <string.h>
#include "TableManipulation.h"

void lexemeSimplify(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]);
void symbolTableGenerate(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]);
void modifiedTokenStream(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]);

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
    char c;
    char sourceFileName[30] = "170204055_Asm3_Input.txt";
    char targetFileName1[30] = "170204055_Asm3_O1.txt";
    char targetFileName2[30] = "170204055_Asm3_T2.txt";
    char targetFileName3[30] = "170204055_Asm3_O2.txt";
    FILE *source, *target;
    //////      Lexeme Simplify for step 1
    source = fopen(sourceFileName, "r");
    target = fopen(targetFileName1, "w");
    lexemeSimplify(source, target, sourceFileName, targetFileName1);

    //////      Symbol Table for step 2
    source = fopen(targetFileName1, "r");
    target = fopen(targetFileName2, "w");
    symbolTableGenerate(source, target, sourceFileName, targetFileName1);

    //////      Modified token stream for Syntax Analysis for step 4
    source = fopen(targetFileName1, "r");
    target = fopen(targetFileName3, "w");
    modifiedTokenStream(source, target, sourceFileName, targetFileName1);


    remove(targetFileName2);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
void lexemeSimplify(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]){
    char c;
    int bracketStarting = 0;

    if(source == NULL || target == NULL){
        printf("\nFile cannot be opened");
    }
    else{
        fputc(' ',target);
        while( (c = fgetc(source)) != EOF){
            if(bracketStarting == 0 && c == '['){   //checking first [ bracket of a lexeme
                bracketStarting = 1;
                fputc('[',target);
                continue;
            }
            if(bracketStarting == 1){               //comparing "id" token after bracket.
                if(c == 'i'){
                    c = fgetc(source);
                    if(c == 'd'){
                        fputs("id ",target);        //if "id" is found, putting in Output file
                        continue;
                    }
                }
                else if(c == ' '){                  //token checking complete
                    bracketStarting = 0;
                    continue;
                }
            }
            else{                                   //putting other characters in Output file
                fputc(c,target);
            }
        }
    }
    fclose(source);
    fclose(target);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
void symbolTableGenerate(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]){
    int count = 0;
    char c, str[100], name[100], dataType[100], scope[100], value[100];
    char previous[100], temp[100];                //previous is to store previously gotten token
    CopyStringToArray(scope,"global");      //In the beginning, default scope is global

    while( (c = fgetc(source)) != EOF){
        int i = 0;
        if(c=='['){                         //retrieving each token inside [] brackets and storing in str[] array
            while(1){
                c = fgetc(source);
                if(c==']')
                    break;
                str[i] = c;
                i++;
            }

            if(isDataType(str)){                                           ///if str token is a data type
               CopyStringToArray(dataType,str);
            }
            else if((str[0]=='i' && str[1]=='d' && str[2]==' ') && strlen(str)>3){   ///if str token is an id type
               CopyIdToArray(temp,str);

               if(Search(temp,scope) == -1 && strcmp(previous,"=")!=0 ){       //id is not present in the table
                   Insert(sl,temp,"var",dataType, scope);                   //id type is variable because previous token is "="
                   sl++;
               }
               else{                                                    //id is already present in the table
                   if(strcmp(previous,"=") == 0){       //previous token is "="
                      UpdateScope(name,temp,scope);
                   }
                   else if(strcmp(previous,"return") == 0){ //previous token is "return"
                      UpdateScope(scope,temp,scope);
                   }
               }
               CopyIdToArray(name,str);
            }
            else if(isNumerical(str)){                                          ///if str token is a numeric value
               if(strcmp(previous, "=") == 0){                  //if previously = is stored then scope will be previous id
                   if(Search(name, scope) != -1){
                       InsertStringInTable(Search(name,scope), 5, str);     //6th column is scope
                   }
                   else if(Search(name,"global") != -1 ){       //if previously "global" is stored then scope will be previous "global"
                       InsertStringInTable(Search(name,"global"), 5, str);
                   }
               }
               else if(strcmp(previous,"return") == 0){         //if previously "return" is stored then scope will be previous "global"
                   if(Search(scope,"global") != -1)
                       InsertStringInTable(Search(scope,"global"), 5, str);
               }
               CopyStringToArray(value,str);
            }
            else if(strlen(str)==1){                                            ///if str token is a bracket ( {
                if(str[0]=='('){
                    if(previous[0]=='i' && previous[1]=='d' && previous[2]==' ' && strlen(previous)>3) {     //if previously a id is got
                        if(count==0){
                            CopyStringToArray(scope,name);
                            UpdateId(name,"func","global");             //function because there is a opening paranthesis after token
                        }
                    }
                }
                else if(str[0]=='{'){
                    count++;
                }
                else if(str[0]=='}'){       //after closing bracket, scope will be global
                    count--;

                    if(count==0){
                        CopyStringToArray(scope,"global");
                    }
                }
            }

            CopyStringToArray(previous,str);                //will store previous string token
        }
        else{
            Delete(str);
            i = 0;
        }
    }
    DisplayTable();
    printTableInFile(target);
    fclose(source);
    fclose(target);
}
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
void modifiedTokenStream(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]){
    int i, count = 0;
    char c, str[100], name[100], dataType[100], scope[100], value[100];
    char previous[100], temp[100];                //previous is to store previously gotten token

    while( (c = fgetc(source)) != EOF){
        if(c=='['){                              //retrieving each token inside [] brackets and storing in str[] array
            while(1){
                c = fgetc(source);
                if(c==']')
                    break;
                str[i] = c; i++;
            }
            if((str[0]=='i' && str[1]=='d' && str[2]==' ') && strlen(str)>3){   ///if str token is an id type
                Delete(temp);
                CopyIdToArray(temp,str);
                fputs("[id",target);

                if(Search(temp,scope) != -1){                //get serial no of the id from the table and print
                    fprintf(target," %d", Search(temp, scope) + 1);
                }
                else{
                    fprintf(target," %d", Search(temp,"global") + 1);
                }

                fputc(']',target);
                CopyIdToArray(name,str);
            }

            else if(strlen(str)==1){                                            ///if str token is a bracket ( {
                if(str[0]=='('){
                    //for maintaining scope
                    if(previous[0]=='i' && previous[1]=='d' && previous[2]==' ' && strlen(previous)>3){     //if previously a id is got
                        if(count==0){
                            CopyStringToArray(scope,name);
                        }
                    }
                }
                else if(str[0]=='{'){       //after each { count increases by 1
                    count++;
                }
                else if(str[0]=='}'){       //after closing bracket, scope will be global
                    count--;
                    if(count==0){           //when count reaches 0, it means outside any functions. scope will be global
                        CopyStringToArray(scope,"global");
                    }
                }
                fputc('[',target);
                fputc(str[0],target);       //for putting single char token
                fputc(']',target);
            }
            else{
                fputc('[',target);
                fputs(str, target);         //for putting other string token
                fputc(']',target);
            }
            CopyStringToArray(previous,str);
        }
        else{
            fputc(c,target);
            Delete(str);
            i = 0;
        }
    }

    fclose(source);
    fclose(target);
}

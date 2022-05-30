#ifndef _STEPTHREE_H_
#define _STEPTHREE_H_
#include<stdio.h>

int sl = 0;
char table[100][100][100];

/// ////////////////////////    InsertSlNoInTable
void InsertSlNoInTable(int i, int j, int sl){
    int x = sl;
    int count = 0;

    while(sl != 0){
        sl = sl / 10;
        count++;
    }

    int k;
    for(k = count-1; k >= 0; k--){
        table[i][j][k] = (x % 10) + 48;
        x = x / 10;
    }
    table[i][j][count]  = '\0';
}
/// ////////////////////////    InsertStringInTable
void InsertStringInTable(int i, int j, char* str2){
    int k;
    for(k = 0;k<strlen(str2);k++){
        table[i][j][k] = str2[k];
    }
    table[i][j][k]  = '\0';
}
/// ////////////////////////    Insert
void Insert(int sl, char* name, char* idtype, char* dataType, char* scope){
    InsertSlNoInTable(sl,0,sl+1);
    InsertStringInTable(sl,1,name);
    InsertStringInTable(sl,2,idtype);
    InsertStringInTable(sl,3,dataType);
    InsertStringInTable(sl,4,scope);
}
/// ////////////////////////    UpdateScope
void UpdateScope(char* str1, char* str2, char* scope)
{
    int i;
    int a = Search(str1,scope);
    int b = Search(str2,scope);

    if(a == -1)
        a = Search(str1,"global");

    if(b == -1)
        b = Search(str2,"global");


    if(a != -1){
        for(i = 0; table[b][5][i] != '\0'; i++){   //updating scope if str1 not global
            table[a][5][i] = table[b][5][i];
        }
        table[a][5][i]  = '\0';
    }

}
/// ////////////////////////    UpdateId
void UpdateId(char* str1, char* str2, char* scope){
    int a = Search(str1,scope);
    int k;
    if(a!=-1){
        for(k = 0;k<strlen(str2);k++){    //updating id type
            table[a][2][k] = str2[k];
        }
        table[a][2][k]  = '\0';
    }
}
/// ////////////////////////    Delete
void Delete(char* str){
    int i;
    for(i = 0;i<50;i++){
        str[i] = '\0';
    }
}
/// ////////////////////////    Search
int Search(char* str, char* scope){
   int i,k;
   char str2[50], str3[50];

   for(i = 0; i < sl; i++){
       Delete(str2);
       Delete(str3);

       for(k = 0; table[i][1][k] != '\0'; k++){ //id name
           str2[k] =  table[i][1][k];
       }

       for(k = 0;table[i][4][k]!='\0';k++){     //data type
           str3[k] =  table[i][4][k];
       }

       if(strcmp(str,str2) == 0 && strcmp(scope,str3) == 0)
           return i;
   }
   return -1;
}
/// ////////////////////////    DisplayTable
void DisplayTable()
{
    int i,j;
    printf("-----------------------------------  Symbol Table  -----------------------------------\n");
    printf("Sl.No.\t\tName\t\tId Type\t\tData Type\tScope\t\tValue\n");
    printf("--------------------------------------------------------------------------------------\n");
    for(i = 0;i<sl;i++)
    {
        int bl = 0;
        int k;
        char s[50];
        Delete(s);
        for(k = 0;table[i][2][k]!='\0';k++)
        {
            s[k] = table[i][2][k];
        }
        if(strcmp("func",s)==0)
            bl = 1;
        for(j = 0;j<6;j++)
        {
            if(bl==1 && j==5)
                continue;
            printf("%s\t\t",table[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}
/// ////////////////////////    printTableInFile
void printTableInFile(FILE *target)
{
    int i,j;
    fputs("Sl.No.\t\tName\tId Type\t\t\tData Type\t\t\tScope\t\t\tValue", target);
    fputs("\n", target);
    for(i = 0;i<sl;i++){
        int bl = 0;
        int k;
        char s[50];
        Delete(s);
        for(k = 0;table[i][2][k]!='\0';k++){
            s[k] = table[i][2][k];
        }
        if(strcmp("func",s)==0)
            bl = 1;
        for(j = 0;j<6;j++){
            if(bl==1 && j==5)
                continue;
            fputs(table[i][j], target);
            fputs("\t\t\t", target);
        }
        fputs("\n", target);
    }
}
/// ///////////////////////////////////// ///

/// ////////////////////////    CopyIdToArray
void CopyIdToArray(char* str1, char* str2){
    int i, j;
    Delete(str1);

    for(i = 3,j = 0;i<strlen(str2);i++,j++){
        str1[j] = str2[i];
    }
}
/// ////////////////////////    CopyStringToArray
void CopyStringToArray(char* str1, char* str2){
    int i;
    Delete(str1);

    for(i = 0; i < strlen(str2); i++){
        str1[i] = str2[i];
    }
}
/// ////////////////////////    isDataType
int isDataType3(char* str1){
    int n = 5;
    char str2[5][20] = {"int","float","double","char", "void"};
    int i;
    for(i = 0;i<n;i++){
        if(strcmp(str1,str2[i])==0)
            return 1;
    }
    return 0;
}
/// ////////////////////////    isNumerical
int isNumerical3(char *lex){
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

////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////
void lexemeSimplify3(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]){
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
void symbolTableGenerate3(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]){
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

            if(isDataType3(str)){                                           ///if str token is a data type
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
            else if(isNumerical3(str)){                                          ///if str token is a numeric value
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

#endif

//      <Stat> -> <AsgnStat> | <DscnStat> | <LoopStat>
//      <asgn_stat>-> id=<expn>     <expn>-> <smpl_expn><extn>       <extn>-> <relop> <smpl_expn> | (eps)
//      <dcsn_stat>-> if(<expn>) <stat> <extn1>         <extn1>->else<stat>|(eps)
//      <loop_stat>-> while(<expn>) <stat>  |  for(<asgn_stat>;<expn>;<asgn_stat>)<stat>
#include <stdio.h>
#include <string.h>
#include "Expression.h"

int Stat(char *str, int i);
int AsgnStat(char *str, int i);
int DscnStat(char *str, int i);
int LoopStat(char *str, int i);
int Expn(char *str, int i);
int Extn(char *str, int i);

int main(){
    //loop input
    /*char str1[100] = "id=c";
    while(1){
        gets(str1);
        if(Stat(str1,0))
            printf("Accepted:  %s\n",str1);
        else
            printf("Rejected:  %s\n",str1);
    }*/

    //predefined input
    char str2[100] = "id=c*b+3/9";
    if(Stat(str2,0))
        printf("Accepted:  %s\n",str2);
    else
        printf("Rejected:  %s\n",str2);

    char str3[100] = "id=a+b+";
    if(Stat(str3,0))
        printf("Accepted:  %s\n",str3);
    else
        printf("Rejected:  %s\n",str3);

    char str4[100] = "if(b<7) id=5+b";
    if(Stat(str4,0))
        printf("Accepted:  %s\n",str4);
    else
        printf("Rejected:  %s\n",str4);

    char str5[100] = "if(a>) id=a+c";
    if(Stat(str5,0))
        printf("Accepted:  %s\n",str5);
    else
        printf("Rejected:  %s\n",str5);

    char str6[100] = "if(a+b<=c+3) id=b+d else id=a*c";
    if(Stat(str6,0))
        printf("Accepted:  %s\n",str6);
    else
        printf("Rejected:  %s\n",str6);

    char str7[100] = "if(a<3) id=a*2 else id=a++";
    if(Stat(str7,0))
        printf("Accepted:  %s\n",str7);
    else
        printf("Rejected:  %s\n",str7);

    char str8[100] = "while(a>) id=b-d";
    if(Stat(str8,0))
        printf("Accepted:  %s\n",str8);
    else
        printf("Rejected:  %s\n",str8);

    char str9[100] = "while(a+b<=c+d) id=b+d";
    if(Stat(str9,0))
        printf("Accepted:  %s\n",str9);
    else
        printf("Rejected:  %s\n",str9);

    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Stat(char *str, int i){
    if(AsgnStat(str,0) || DscnStat(str,0) || LoopStat(str,0)){    /// <Stat> -> <AsgnStat> | <DscnStat> | <LoopStat>
        return 1;
    }
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int AsgnStat(char *str, int i){
    if(str[0] == 'i' && str[1] == 'f' && str[2] == '('){    //DscnStat excluding
        return 0;
    }
    if(str[0] == 'w' && str[1] == 'h' && str[2] == 'i' && str[3] == 'l' && str[4] == 'e' && str[5] == '('){    //while excluding
        return 0;
    }

    char strTemp[100];
    int len = strlen(str);

    if(str[0] == 'i' && str[1] == 'd' && str[2] == '='){        ///  <asgn_stat>-> id=<expn>;
        for(i = 0; i < len-3 ; i++){
                strTemp[i] = str[i+3];      //removing 'id=' from str
        }
        strTemp[i]='\0';
        //printf("%s\t %d\n", strTemp, strlen(strTemp));
        if(Exp(strTemp)){                       /// <expn>-> <smpl_expn><extn>;   <extn>-> (eps)
            return 1;                           //something like: a | b | a+7 | a*9-3
        }
    }
    else{
        if(Expn(str,0)){
            return 1;
        }
    }

    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Expn(char *str, int i){
    if(str[0] == 'i' && str[1] == 'd' && str[2] == '='){    //id= excluding
        return 0;
    }
    if(str[0] == 'w' && str[1] == 'h' && str[2] == 'i' && str[3] == 'l' && str[4] == 'e' && str[5] == '('){    //while excluding
        return 0;
    }
    int j, symPos = -1;
    int len = strlen(str);
    int dSym = 0;   //double symbol
    int sSym = 0;   //single symbol
    i=0;
    while(i<len){       ///     <expn>-> <smpl_expn><extn>;     <extn>-><relop><smpl_expn>
        if(str[i] == '=' && str[i+1] == '='){       /// <relop>-> == | != | <= | >= | > | <
            symPos=i;
            dSym=1;
            i+=2;
        }
        else if(str[i] == '!' && str[i+1] == '='){
            symPos=i;
            dSym=1;
            i+=2;
        }
        else if(str[i] == '>' && str[i+1] == '='){
            symPos=i;
            dSym=1;
            i+=2;
        }
        else if(str[i] == '<' && str[i+1] == '='){
            symPos=i;
            dSym=1;
            i+=2;
        }
        else if(str[i] == '<'){
            symPos=i;
            sSym=1;
            i++;
        }
        else if(str[i] == '>'){
            symPos=i;
            sSym=1;
            i++;
        }
        else{
            i++;
        }
    }
    if(symPos != -1 && symPos != len-1){
        char str1[100], str2[100];
        for (i = 0; i < symPos; i++){                    //copying left side term of + or - symbol in str1
            str1[i] = str[i];
        }
        str1[i] ='\0';
        //printf("%s\t %d\n", str1, strlen(str1));

        if(sSym){   // single symbol '<' '>'
            for (i = symPos+1, j = 0; i<len; i++, j++){     //copying right side term of + or - symbol in str2
                str2[j] = str[i];
            }
        }
        if(dSym){    // double symbol '<=' '>=' '==' '!='
            for (i = symPos+2, j = 0; i<len; i++, j++){     //copying right side term of + or - symbol in str2
                str2[j] = str[i];
            }
        }
        str2[j] ='\0';
        //printf("%s\t %d\n", str2, strlen(str2));
        if(Exp(str1)){                                 //checking if both str1 & str2 are terms
            if(Exp(str2)){
                return 1;
            }
        }
    }

    else if(symPos == -1){     /// <expn>-> <smpl_expn><extn>;     <extn>-> (eps)
        if(Exp(str)){
            return 1;
        }
    }
    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int DscnStat(char *str, int i){
    if(str[0] == 'i' && str[1] == 'd' && str[2] == '='){    //id= excluding
        return 0;
    }
    if(str[0] == 'w' && str[1] == 'h' && str[2] == 'i' && str[3] == 'l' && str[4] == 'e' && str[5] == '('){    //while excluding
        return 0;
    }

    char strExpn[100];
    char strStat[100];
    char strExtn1[100];
    int len = strlen(str);
    int statPos = -1;
    int extn1Pos = -1;
    if(str[0] == 'i' && str[1] == 'f' && str[2] == '('){    ///copying <expn>
        for(i = 0; i<len ; i++){
            if(str[i+3] == ')')
                break;
            strExpn[i] = str[i+3];      //storing expn which is inside () into strExpn
        }
        strExpn[i] = '\0';
        //printf("%s\t %d\n", strExpn, strlen(strExpn));
    }

    i=0;
    while(i<len){
        if(str[i] == ')' && str[i+1] == ' '){              ///copying <stat>
            statPos=i+2;
            break;
        }
        i++;
    }
    //printf("%d\n", statPos);
    int j;
    if(statPos != -1){
        for(i = statPos, j=0; i<len ; i++,j++){
            if(str[i] == ' ')
                break;
            strStat[j] = str[i];      //storing Stat which is after if() into strStat
        }
        strStat[j] = '\0';
        //printf("%s\t %d\n", strStat, strlen(strStat));
    }

    i=0;
    while(i<len){
        if(str[i] == 'e' && str[i+1] == 'l' && str[i+2] == 's' && str[i+3] == 'e' && str[i+4] == ' '){              ///copying <extn1>
            extn1Pos=i+5;
            break;
        }
        i++;
    }
    //printf("%d\n", extn1Pos);
    if(extn1Pos != -1){
        for(i = extn1Pos, j=0; i<len ; i++,j++){
            if(str[i] == ' ')
                break;
            strExtn1[j] = str[i];      //storing Stat which is after if() into strExtn1
        }
        strExtn1[j] = '\0';
        //printf("%s\t %d\n", strExtn1, strlen(strExtn1));
    }

    if(Expn(strExpn,0) && Stat(strStat,0)){
        if(extn1Pos != -1){
            if(Stat(strExtn1,0)){
                return 1;
            }
            else{
                return 0;
            }
        }
        return 1;
    }

    return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LoopStat(char *str, int i){
    if(str[0] == 'i' && str[1] == 'd' && str[2] == '='){    //id= excluding
        return 0;
    }
    if(str[0] == 'i' && str[1] == 'f' && str[2] == '('){    //DscnStat excluding
        return 0;
    }

    char strExpn[100];
    char strStat[100];
    int len = strlen(str);
    int statPos = -1;
    if(str[0] == 'w' && str[1] == 'h' && str[2] == 'i' && str[3] == 'l' && str[4] == 'e' && str[5] == '('){    ///copying <expn>
        for(i = 0; i<len ; i++){
            if(str[i+6] == ')')
                break;
            strExpn[i] = str[i+6];      //storing expn which is inside () into strExpn
        }
        strExpn[i] = '\0';
        //printf("%s\t %d\n", strExpn, strlen(strExpn));
    }

    i=0;
    while(i<len){
        if(str[i] == ')' && str[i+1] == ' '){              ///copying <stat>
            statPos=i+2;
            break;
        }
        i++;
    }
    //printf("%d\n", statPos);
    int j;
    if(statPos != -1){
        for(i = statPos, j=0; i<len ; i++,j++){
            if(str[i] == ' ')
                break;
            strStat[j] = str[i];      //storing Stat which is after if() into strStat
        }
        strStat[j] = '\0';
        //printf("%s\t %d\n", strStat, strlen(strStat));
    }

    if(Expn(strExpn,0) && Stat(strStat,0)){
        return 1;
    }

    return 0;
}




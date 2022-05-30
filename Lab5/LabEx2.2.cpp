//      <Exp> -> <Term> + <Term> | <Term> - <Term> | <Term>
//      <Term> -> <Factor> * <Factor> | <Factor> / <Factor> | <Factor>
//      <Factor> -> (<Exp>) | ID | NUM

#include <stdio.h>
#include "Expression.h"

int main(){
    //////////////////////////////////////////////////////////////
    char str1[30];
    while(1){
        gets(str1);
        if(Exp(str1))
            printf("Accepted:  %s\n",str1);
        else
            printf("Rejected:  %s\n",str1);
    }
    /*Test:
    b+4**
    b+4
    (((((a+9)*5*)4+(b-c)
    a+(b+3)
    a+b+c
    a*b+c*d
    (a+9*8)*5+(4/(b+c))
    */
    return 0;
}

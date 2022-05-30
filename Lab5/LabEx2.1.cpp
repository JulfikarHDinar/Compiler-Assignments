//      S ->  b | AB
//      A -> a | aA
//      B -> b
//      b, ab, aab, aaab, ...
#include <stdio.h>
#include <string.h>
int S(char *str);
int A(char *str, int i);
int B(char *str, int i);

int main(){
    char str1[30];
    while(1){
        gets(str1);
        if(A(str1,0))
            printf("Accepted:  %s\n",str1);
        else
            printf("Rejected:  %s\n",str1);
    }
    return 0;
}
int S(char *str){
    int i = 0;
    int len = strlen(str);
    if(str[i] == 'b'){
        if(len == 1){   //b
            return 1;
        }
    }
    else if(str[i] == 'a'){  //a...
        i++;
        if( A(str,i) ){
            return 1;
        }
    }
    return 0;   //doesn't match
}

int A(char *str, int i){
    int len = strlen(str);

    if(i < len && str[i] == 'a'){   //aA...
        i++;
        return A(str, i);
    }
    else if(i == len-1){           //...AB
        return B(str, i);
    }
    return 0;   //doesn't match
}

int B(char *str, int i){
    if(str[i] == 'b'){          //...b
        return 1;
    }
    else{
       return 0;
    }
}

//      A -> aXd
//      X -> bbX | bcX | d
//      abbdd, abcdd, abbbbdd, abcbbdd, abbbcbbdd,  ...
#include <stdio.h>
#include <string.h>
int A(char *str);
int X(char *str, int i);

int main(){
    char str1[30] ;


    while(1){
        gets(str1);
        if(A(str1))
            printf("Accepted:  %s\n",str1);
        else
            printf("Rejected:  %s\n",str1);
    }
    return 0;
}

int A(char *str){
    int i = 0;
    int len = strlen(str);
    if(str[i] == 'a'){            //a...
        i++;
        if( X(str,i) ){             //aX...
            if( str[len-1] == 'd')    //aXd
                return 1;
        }
    }
    return 0;   //doesn't match
}

int X(char *str, int i){
    int len = strlen(str);

    if(i < len-1 && str[i] == 'b' && str[i+1] == 'b'){      //...bbX...
        i += 2;
        return X(str, i);
    }
    else if(i < len-1 && str[i] == 'b' && str[i+1] == 'c'){ //...bcX...
        i+=2;
        return X(str, i);
    }
    else if(i < len-1 && str[i] == 'd'){            //...d...
        i++;
        return 1;
    }

    return 0;
}

/*
 Name:         ID:        Lab Group:A2
 Course No: CSE4130
 Final Online Assessment
*/
#include<stdio.h>
#include<string.h>
int n,i;
char s[100];
int E();
int B();
int A();

int B(){
    if(s[i]=='a'){
        i++;
        return 1;
    }
    return 1;
}
int A()
{
    if(s[i]=='b')
    {
        i++;
        if(A()){
            return 1;
        }
        return 1;
    }
    return 0;
}
int E()
{
    if(s[i]=='a')
    {
        i++;
        if(A()){
            return 1;
        }
        return 0;
    }
    if(s[i]=='b'){
        i++;
        if(A()){
            if(B()){
                return 1;
            }
            return 0;
        }
        return 0;
    }
    return 0;
}

int main()
{
    while(1){
        printf("String: ");
        scanf("%s",&s);
        n = strlen(s);
        i = 0;
        int x = E();
        if( i==n && x)
            printf("String follows the grammar\n");
        else
            printf("String does not follow the grammar\n");
    }

    return 0;
}

/*
 Name:Sadia Tasnim ID:170104037 Lab Group:A2
 Course No: CSE4130
 Final Online Assessment, Spring 2020
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void give_line_number()
{
    FILE *p1,*p2;
    char c;
    int i = 1,check=1;
    p1 = fopen("input.txt", "r");
    p2 = fopen("give_line_number.txt","w");

    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
        while((c = fgetc(p1)) != EOF)
        {
            if (check==1)
            {
                fprintf(p2,"%d",i);
                fputc(' ', p2);
                check=0;
                i++;
            }
            if (c=='\n')
            {
                fputc('\n', p2);
                fprintf(p2,"%d",i);
                fputc(' ', p2);
                i++;
            }
            else
                fputc(c, p2);
        }
    }
    fclose(p1);
    fclose(p2);

}
int paranthesis(char c)
{
    if( c=='(' || c==')' || c == '{' || c== '}' )
        return 1;
    return 0;
}
int separator(char c)
{
    if( c==';' || c==',' )
        return 1;
    return 0;
}
int is_operator(char c)
{
    if( c=='+' || c=='-' || c=='*' || c=='/' || c=='%' || c =='=' || c == '>' || c == '<' || c=='!' || c=='|' || c=='^')
        return 1;
    return 0;
}
int identifier(char arr[])
{
    int check = 0 ;
    if((arr[0]>='a' && arr[0]<='z') || (arr[0]>='A' && arr[0]<='Z') || arr[0]=='_' )
        check = 1;
    if (check==0)
        return 0 ;
    else
    {
        int i ;
        for ( i = 1 ; i<strlen(arr); i++)
        {
            if((arr[i]>='a' && arr[i]<='z') || (arr[i]>='A' && arr[i]<='Z') || arr[i]=='_' || (arr[i]>='0' && arr[i]<='9') )
                continue;
            else
                return 0 ;
        }
    }

    return 1 ;
}
int keyword(char s[])
{
    int n = 35;
    char s2[35][20] = {"int","char","float","const", "short", "enum","if","else","for", "while", "do",
                       "return","double", "include", "auto", "break", "struct", "static", "continue", "default", "long",
                       "signed", "sizeof", "switch", "typedef", "unsigned", "void",
                       "case", "extern", "goto", "register", "volative","printf","scanf"
                      };
    int i, j;
    for(i=0; i<n; i++)
    {
        if(strcmp(s,s2[i])==0)
            return 1;
    }
    return 0;
}
void clear(char* s)
{
    int i;
    for(i = 0; i<50; i++)
    {
        s[i] = '\0';
    }
}
void modify()
{
    FILE *p1,*p2;
    char c;
    int space=0;
    p1 = fopen("give_line_number.txt", "r");
    p2 = fopen("modify.txt","w");
    if(!p1)
        printf("\nFile can't be opened!");
    else
    {
        while((c = fgetc(p1)) != EOF)
        {
            if (c=='/')
            {
                /*for
                multiple line
                comment */
                char a = fgetc(p1);
                if (a=='*')
                {
                    while(1)
                    {
                        c=fgetc(p1);
                        if (c=='*')
                        {
                            if ((c=fgetc(p1))=='/')
                                break;
                        }
                    }

                }
                else if (a=='/') //for single line comment
                {
                    while(1)
                    {
                        c=fgetc(p1);
                        if(c=='\n')
                        {
                            fputc(c,p2);
                            break;
                        }
                    }
                }
                else
                {
                    fputc(c,p2);
                    fputc(a,p2);

                }
            }
            //for removing space and tab
            else if (c==' ' && space >= 1)
            {
                continue;
            }
            else if (c==' ' && space < 1)
            {
                space++;
                fputc(' ',p2);
            }
            else if(separator(c)|| is_operator(c)|| paranthesis(c))
            {
                fputc(' ',p2);
                fputc(c,p2);
                fputc(' ',p2);
            }
            else
            {
                fputc(c,p2);
                space=0;
            }
        }
    }
    fclose(p1);
    fclose(p2);
}
void print_func()
{
    FILE *p1;
    char c,p;
    char s[100];
    int i = 0,line=1;
    p1 = fopen("modify.txt", "r");
    while( (c = fgetc(p1)) !=EOF)
    {
        if (c=='\n')line++;
        if (c!=' ')
        {
            s[i]=c;
            i++;
        }
        else
        {
            if(identifier(s) && keyword(s)==0 && strlen(s)>0)
            {
                p = fgetc(p1);
                if(p=='(')
                {
                    int j = 0 ;
                    for(j=0; j<strlen(s); j++)
                    {
                        printf("%c",s[j]);
                    }
                    printf(" : line no %d\n",line);
                }
            }
            clear(s);
            i=0;
        }
    }
    fclose(p1);
}
int main ()
{
    char c;
    give_line_number();
    modify();
    print_func();
    return 0;
}

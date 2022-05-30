#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100000
int itemCount = 0;

// Creating a stack
struct stack
{
    int items[MAX];
    int top;
};
typedef struct stack _stack;

void createEmptyStack(_stack *s)
{
    s->top = -1;
}

// Check if the stack is full
int isStackFull(_stack *s)
{
    if (s->top == MAX - 1)
        return 1;
    else
        return 0;
}

// Check if the stack is empty
int isempty(_stack *s)
{
    if (s->top == -1)
        return 1;
    else
        return 0;
}

// Add elements into stack
void push(_stack *s, int newitem)
{
    if (isStackFull(s))
    {
        printf("STACK FULL");
    }
    else
    {
        s->top++;
        s->items[s->top] = newitem;
    }
    itemCount++;
}

// Remove element from stack
int pop(_stack *s)
{
    if (isempty(s))
    {
        return -1;
    }
    else
    {
        //printf("Item popped= %d", s->items[s->top]);
        s->top--;
    }
    itemCount--;
}

// Print elements of stack
void printStack(_stack *s)
{
    int i;
    for (i = 0; i < itemCount; i++)
    {
        printf("%d, ", s->items[i]);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void removeComments(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30])
{
    char c;
    int slashStart = 0;
    int checkForCommentStop = 0;
    int singleLineComment = 0;
    int multipleLineComment = 0;

    if(source == NULL || target == NULL)
    {
        printf("\nFile cannot be opened");
    }
    else
    {
        while( (c = fgetc(source)) != EOF )
        {
            //////////////////////////////////      single line comment started       ///////////////////////////////////
            if(singleLineComment == 1)
            {
                //  stop when new line appears
                if(c == 10)
                {
                    fputc(10,target);
                    singleLineComment = 0;
                    continue;
                }
            }
            ///////////////////////////////////     multi line comment started        ////////////////////////////////////
            else if(multipleLineComment == 1)
            {
                //  ending star
                if(c == '*')
                {
                    checkForCommentStop = 1;
                    continue;
                }

                //  after getting star in multi line comment
                if(checkForCommentStop == 1)
                {
                    //  comment ends after getting slash
                    if(c == '/')
                    {
                        multipleLineComment = 0;
                        continue;
                    }
                    else
                    {
                        checkForCommentStop = 0;
                        continue;
                    }
                }
            }
            /////////////////////////////////       Checking for comment          ///////////////////////////////////////
            else if(singleLineComment == 0 && multipleLineComment == 0)
            {
                if(c == '/' && slashStart == 0)
                {
                    slashStart = 1;
                    continue;
                }
                //for single line
                else if(c == '/' && slashStart == 1)
                {
                    slashStart = 0;
                    singleLineComment = 1;
                    continue;
                }
                //for multi line
                else if(c == '*' && slashStart == 1)
                {
                    slashStart = 0;
                    multipleLineComment = 1;
                    continue;
                }
                //one slash, means there might be division sign
                else if(c != '/' && slashStart == 1)
                {
                    slashStart = 0;
                    fputc('/',target);
                    fputc(c,target);
                    continue;
                }
                //normal character, no comment possibility
                else
                {
                    fputc(c,target);
                }
            }
        }
    }
    fclose(source);
    fclose(target);
}

//////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////
void removeSpaces(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30])
{
    char c;
    int syntaxStart = 0;
    int syntaxSpace = 0;

    char tempFileName[30] = "temp1.txt";
    FILE *temp;
    temp = fopen(tempFileName, "w");

    if(source == NULL || temp == NULL)
    {
        printf("\nFile cannot be opened");
    }
    else
    {
        while( (c = fgetc(source)) != EOF )
        {
            //removing tab
            if(c == 9)
            {
                fputc(32,temp);
                continue;
            }
            //removing extra space from the beginning of a syntax
            else if(c == 32 && syntaxStart == 0)
            {
                continue;
            }
            else
            {
                syntaxStart = 1;
            }

            //syntax started in that line
            if(syntaxStart = 1)
            {
                //allowing first space between syntaxes
                if(c == 32 && syntaxSpace == 0)
                {
                    fputc(32,temp);
                    syntaxSpace = 1;
                    continue;
                }
                //removing more than 1 space between syntaxes
                else if(c == 32 && syntaxSpace == 1)
                {
                    continue;
                }
            }
            //normal character, no space tendency
            fputc(c,temp);
            syntaxSpace = 0;
        }
    }
    fputc(' ',temp);
    fclose(source);
    fclose(temp);

    //Removing more than one spaces (because of replacing tabs with spaces)
    syntaxSpace = 0;
    int codeStart = 0;
    source = fopen(tempFileName, "r");

    while( (c = fgetc(source)) != EOF )
    {
        if(c == 10)
        {
            fputc(c,target);
            codeStart = 0;  //setting codestart variable to zero after getting new line
            continue;
        }
        else if(c == 32 && syntaxSpace == 0 && codeStart == 1)           //one space between syntaxes
        {
            fputc(32,target);
            syntaxSpace = 1;
            continue;
        }
        else if(c == 32 && syntaxSpace == 1 && codeStart == 1)      //more than one space between syntaxes
        {
            continue;
        }
        else if(c != 32)                                            //any character other than space
        {
            fputc(c,target);
            codeStart = 1;
            syntaxSpace = 0;
        }
    }

    fclose(source);
    fclose(target);
    remove(tempFileName);
}

/// /////////////////////////////////////////////////////////////////////////////////////////////////
/// /////////////////////////////////////////////////////////////////////////////////////////////////
void lexemeSeparator(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30])
{
    char c;
    int lexemeStart = 0;
    char tempFileName[30] = "temp1.txt";
    FILE *temp;
    temp = fopen(tempFileName, "w");

    if(source == NULL || target == NULL || temp == NULL)
    {
        printf("\nFile cannot be opened");
    }

    else
    {
        while( (c = fgetc(source)) != EOF )
        {
            if(c == 10) 	//new line
            {
                fputc(c,temp);
                continue;
            }

            if(c == ' ')
            {
                fputc(c,temp);
                lexemeStart = 0;
                continue;
            }

            if(c != ' ' && lexemeStart == 0)
            {
                lexemeStart = 1;
            }

            if(lexemeStart == 1)
            {
                if (c == '(' || c == ')' || c == '{' || c == '}')
                {
                    fputc(' ',temp);      //leading space of the lexeme
                    fputc(c,temp);
                    fputc(' ',temp);      //trailing space of the lexeme
                    lexemeStart = 0;
                    continue;
                }
                if(c == ';' || c == ',' || c == 39 || c == '+' || c == '-' || c == '*' || c == '/' || c == '%')     //apostrophe ascii = 39
                {
                    fputc(' ',temp);      //leading space of the lexeme
                    fputc(c,temp);
                    lexemeStart = 0;

                    char cc = fgetc(source);    //checking next character
                    if (cc == '+' || cc == '-' )  //for  ++  --
                    {
                        fputc(cc,temp);
                        fputc(' ',temp);  //trailing space of the lexeme
                    }

                    else if (cc == ';')   //semicolon after apostrophe
                    {
                        fputc(' ',temp);  //leading space of the lexeme
                        fputc(cc,temp);
                        fputc(' ',temp);  //trailing space of the lexeme
                    }

                    else
                    {
                        fputc(' ',temp);  //leading space of the lexeme
                        fputc(cc,temp);
                    }

                    continue;
                }

                else if(c == '>' || c == '<' || c == '!' || c == '|' || c == '&' || c == '=')
                {
                    fputc(' ',temp);      //leading space of the lexeme
                    fputc(c,temp);
                    lexemeStart = 0;

                    char cc = fgetc(source);    //checking next character
                    if (cc == '=' || cc == '|' || cc == '&')    //for checking  >=  <=  !=  &&  ||
                    {
                        fputc(cc,temp);
                        fputc(' ',temp);  //trailing space of the lexeme
                    }

                    else if (cc == 39)      //apostrophe ASCII = 39
                    {
                        fputc(' ',temp);  //leading space of the lexeme
                        fputc(cc,temp);
                        fputc(' ',temp);  //trailing space of the lexeme
                    }

                    else
                    {
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
    int lineStart = 0;
    lexemeStart = 0;
    source = fopen(tempFileName, "r");

    while( (c = fgetc(source)) != EOF )
    {
        if(c != 32 && c != 10)      //normal character other then space(32) and new line(10)
        {
            fputc(c,target);
            lineStart = 1;
            syntaxSpace = 0;
        }

        else if(c == 10)
        {
            fputc(c,target);
            lineStart = 0;
        }

        else if(c == 32 && syntaxSpace == 0 && lineStart == 1)           //one space between syntaxes
        {
            fputc(32,target);
            syntaxSpace = 1;
        }

        else if(c == 32 && syntaxSpace == 1 && lineStart == 1)      //more than one space between syntaxes
        {
            continue;
        }
    }
    fclose(source);
    fclose(target);
    remove(tempFileName);
}

/// //////////////////////////////////////////////////////////////////////////////////////////////////
/// //////////////////////////////////////////////////////////////////////////////////////////////////
void lexemeTokenization(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30])
{
    char c, lex[50];
    if(source == NULL || target == NULL)
    {
        printf("\nFile cannot be opened");
    }

    else
    {
        int i = 0;

        while( (c = fgetc(source)) != EOF )
        {
            if(c == 10)
            {
                fputc(c, target);
                continue;
            }

            if(c == ' ')        //checking each lexeme separately and putting them in target file
            {
                lex[i] = '\0';
                i=0;

                if(isSeparator(lex))
                {
                    fputs("sep ", target);
                    fputs(lex, target);
                    fputs(" ", target);
                }

                else if(isParenthesis(lex))
                {
                    fputs("par ", target);
                    fputs(lex, target);
                    fputs(" ", target);
                }

                else if(isBracket(lex))
                {
                    fputs("brc ", target);
                    fputs(lex, target);
                    fputs(" ", target);
                }

                else if(isOperator(lex))
                {
                    fputs("op ", target);
                    fputs(lex, target);
                    fputs(" ", target);
                }

                else if(isNumerical(lex))
                {
                    fputs("num ", target);
                    fputs(lex, target);
                    fputs(" ", target);
                }

                else if(isKeyword(lex))
                {
                    fputs("kw ", target);
                    fputs(lex, target);
                    fputs(" ", target);
                }

                else if(isIdentifier(lex))
                {
                    fputs("id ", target);
                    fputs(lex, target);
                    fputs(" ", target);
                }

                else
                {
                    fputs("unkn ", target);
                    fputs(lex, target);
                    fputs(" ", target);
                }

                continue;
            }
            else
            {
                lex[i] = c;
                i++;
            }
        }
    }
    fclose(source);
    fclose(target);
}

/// ///////////////////////////////////////////
/// ///////////////////////////////////////////
int isNumerical(char *lex)
{
    int i, l, s;
    i=0;

    if(isdigit(lex[i]))
    {
        s=1;
        i++;
    }

    else if(lex[i]=='.')
    {
        s=2;
        i++;
    }

    else
    {
        s=0;
    }

    l=strlen(lex);

    if(s==1)
    {
        for(; i<l; i++)
        {
            if(isdigit(lex[i]))
            {
                s=1;
            }

            else if(lex[i]=='.')
            {
                s=2;
                i++;
                break;
            }

            else
            {
                s=0;
                break;
            }
        }
    }

    if(s==2)
    {
        if(isdigit(lex[i]))
        {
            s=3;
            i++;
        }

        else
            s=0;
    }

    if(s==3)
    {
        for(; i<l; i++)
        {
            if(isdigit(lex[i]))
            {
                s=3;
            }

            else
            {
                s=0;
                break;
            }
        }
    }

    if(s==3)
    {
        s=1;
    }

    return s;
}

/// ///////////////////////////////////////////
/// ///////////////////////////////////////////
int isSeparator(char *lex)
{
    int s = 0 ;

    if( strlen(lex) == 1 && (lex[0] == ';' || lex[0] == ',' || lex[0] == 39) )
    {
        s = 1;
    }
    return s;
}

/// ///////////////////////////////////////////
/// ///////////////////////////////////////////
int isParenthesis(char *lex)
{
    int s = 0 ;

    if( strlen(lex) == 1 && (lex[0] == '(' || lex[0] == ')') )
    {
        s = 1;
    }
    return s;
}

/// ///////////////////////////////////////////
/// ///////////////////////////////////////////
int isBracket(char *lex)
{
    int s = 0 ;

    if( strlen(lex) == 1 && (lex[0] == '{' || lex[0] == '}') )
    {
        s = 1;
    }
    return s;
}

/// ///////////////////////////////////////////
/// ///////////////////////////////////////////
int isOperator(char *lex)
{
    int s = 0 ;

    if(strlen(lex) == 1)        //single operator
    {
        if( lex[0] == '+' || lex[0] == '-' || lex[0] == '*' || lex[0] == '/' || lex[0] == '%' || lex[0] == '=' ||
                lex[0] == '<' || lex[0] == '>' || lex[0] == '!' || lex[0] == '&' || lex[0] == '|' || lex[0] == '~' || lex[0] == '^' )
        {
            s = 1;
        }
    }

    if(strlen(lex) == 2)        //double operator
    {
        if( (lex[0] == '+' && lex[1] == '+') || (lex[0] == '-' && lex[1] == '-') || (lex[0] == '=' && lex[1] == '=') || (lex[0] == '!' && lex[1] == '=') ||
                (lex[0] == '|' && lex[1] == '|') || (lex[0] == '&' && lex[1] == '&') || (lex[0] == '>' && lex[1] == '=') || (lex[0] == '<' && lex[1] == '=') )
        {
            s = 1;
        }
    }
    return s;
}

/// ///////////////////////////////////////////
/// ///////////////////////////////////////////
int isIdentifier(char *lex)
{
    int s = 0 ;

    if((lex[0] >= 'a' && lex[0] <= 'z') || (lex[0] >= 'A' && lex[0] <= 'Z') || lex[0] == '_' )
    {
        s = 1;      //checking first character if it's valid or not (a-z) || (A-Z) || _
    }

    if (s==0)
    {
        return s ;
    }

    else
    {
        int i;

        for ( i = 1 ; i<strlen(lex); i++)
        {
            if((lex[i] >= 'a' && lex[i] <= 'z') || (lex[i] >= 'A' && lex[i] <= 'Z') || lex[i] == '_' || (lex[i] >= '0' && lex[i] <= '9') )
            {
                continue;
            }

            else
            {
                s = 0;
            }
        }
    }
    return s ;
}

/// ///////////////////////////////////////////
/// ///////////////////////////////////////////
int isKeyword(char *lex)
{
    int s = 0 ;

    if(lex[0] == 'i' && lex[1] == 'n' && lex[2] == 't' && lex[3] == '\0' )
    {
        s = 1;      //int
    }

    else if(lex[0] == 'c' && lex[1] == 'h' && lex[2] >= 'a' && lex[3] == 'r' && lex[4] == '\0' )
    {
        s = 1;      //char
    }

    else if(lex[0] == 'f' && lex[1] == 'l' && lex[2] >= 'o' && lex[3] == 'a' && lex[4] == 't' && lex[5] == '\0' )
    {
        s = 1;      //float
    }

    else if(lex[0] == 'd' && lex[1] == 'o' && lex[2] >= 'u' && lex[3] == 'b' && lex[4] == 'l' && lex[5] == 'e' && lex[6] == '\0' )
    {
        s = 1;      //double
    }

    else if(lex[0] == 'l' && lex[1] == 'o' && lex[2] >= 'n' && lex[3] == 'g' && lex[4] == '\0' )
    {
        s = 1;      //long
    }

    else if(lex[0] == 's' && lex[1] == 'h' && lex[2] >= 'o' && lex[3] == 'r' && lex[4] == 't' && lex[5] == '\0' )
    {
        s = 1;      //short
    }

    else if(lex[0] == 'w' && lex[1] == 'h' && lex[2] >= 'i' && lex[3] == 'l' && lex[4] == 'e' && lex[5] == '\0' )
    {
        s = 1;      //while
    }

    else if(lex[0] == 'f' && lex[1] == 'o' && lex[2] >= 'r' && lex[3] == '\0' )
    {
        s = 1;      //for
    }

    else if(lex[0] == 'd' && lex[1] == 'o' && lex[2] == '\0' )
    {
        s = 1;      //do
    }

    else if(lex[0] == 'i' && lex[1] == 'f' && lex[2] == '\0' )
    {
        s = 1;      //if
    }

    else if(lex[0] == 'e' && lex[1] == 'l' && lex[2] >= 's' && lex[3] == 'e' && lex[4] == '\0' )
    {
        s = 1;      //else
    }

    else if(lex[0] == 'v' && lex[1] == 'o' && lex[2] >= 'i' && lex[3] == 'd' && lex[4] == '\0' )
    {
        s = 1;      //void
    }

    else if(lex[0] == 's' && lex[1] == 't' && lex[2] >= 'a' && lex[3] == 't' && lex[4] == 'i' && lex[5] == 'c' && lex[6] == '\0' )
    {
        s = 1;      //static
    }

    else if(lex[0] == 'b' && lex[1] == 'r' && lex[2] >= 'e' && lex[3] == 'a' && lex[4] == 'k' && lex[5] == '\0' )
    {
        s = 1;      //break
    }

    else if(lex[0] == 'c' && lex[1] == 'o' && lex[2] >= 'n' && lex[3] == 't' && lex[4] == 'i' && lex[5] == 'n' && lex[6] == 'u' && lex[7] == 'e' && lex[8] == '\0' )
    {
        s = 1;      //continue
    }

    else if(lex[0] == 'd' && lex[1] == 'e' && lex[2] >= 'f' && lex[3] == 'a' && lex[4] == 'u' && lex[5] == 'l' && lex[6] == 't' && lex[7] == '\0' )
    {
        s = 1;      //default
    }

    else if(lex[0] == 'c' && lex[1] == 'o' && lex[2] >= 'n' && lex[3] == 's' && lex[4] == 't' && lex[5] == '\0' )
    {
        s = 1;      //const
    }

    else if(lex[0] == 's' && lex[1] == 'w' && lex[2] >= 'i' && lex[3] == 't' && lex[4] == 'c' && lex[5] == 'h' && lex[6] == '\0' )
    {
        s = 1;      //switch
    }

    else if(lex[0] == 'c' && lex[1] == 'a' && lex[2] >= 's' && lex[3] == 'e' && lex[4] == '\0' )
    {
        s = 1;      //case
    }

    else if(lex[0] == 's' && lex[1] == 'i' && lex[2] >= 'z' && lex[3] == 'e' && lex[4] == 'o' && lex[5] == 'f' && lex[6] == '\0' )
    {
        s = 1;      //sizeof
    }

    else if(lex[0] == 's' && lex[1] == 't' && lex[2] >= 'r' && lex[3] == 'u' && lex[4] == 'c' && lex[5] == 't' && lex[6] == '\0' )
    {
        s = 1;      //struct
    }

    else if(lex[0] == 's' && lex[1] == 'i' && lex[2] >= 'g' && lex[3] == 'n' && lex[4] == 'e' && lex[5] == 'd' && lex[6] == '\0' )
    {
        s = 1;      //signed
    }

    else if(lex[0] == 'u' && lex[1] == 'n' && lex[2] >= 's' && lex[3] == 'i' && lex[4] == 'g' && lex[5] == 'n' && lex[6] == 'e' && lex[7] == 'd' && lex[8] == '\0' )
    {
        s = 1;      //unsigned
    }

    else if(lex[0] == 'r' && lex[1] == 'e' && lex[2] >= 't' && lex[3] == 'u' && lex[4] == 'r' && lex[5] == 'n' && lex[6] == '\0' )
    {
        s = 1;      //return
    }

    return s ;
}

/// /////////////////////////////////////////////////////////////////////////////////////////////////
/// /////////////////////////////////////////////////////////////////////////////////////////////////
void unmatchedParentheses(FILE *source, FILE *target)       //unmatched/unbalanced parenthesis ( ) checking
{
    char c;
    char lineNoStr[20];
    _stack *parStack = (_stack *)malloc(sizeof(_stack));
    createEmptyStack(parStack);

    if(source == NULL || target == NULL)
    {
        printf("\nFile cannot be opened");
    }
    else
    {
        int i = 0, lineNoStart = 1;
        int forStat = 0;

        while( (c = fgetc(source)) != EOF )
        {
            ///   getting Line number and storing in lineNoStr String
            if(lineNoStart == 1 && c != ':')        // line number is upto : symbol
            {
                lineNoStr[i] = c;
                i++;
                continue;
            }
            else if(lineNoStart == 1 && c == ':')
            {
                lineNoStr[i] = '\0';
                i = 0;
                lineNoStart = 0;
            }
            else if(c == 10)     //line number starts after a new line
            {
                lineNoStart = 1;
                //printf("\n");
            }

            int lineNo = atoi(lineNoStr);   //converting lineNo char array(string) to integer

            ///     for checking
            if(c == 'k')        //checking 'kw for' and setting forStat = 1
            {
                c = fgetc(source);
                if(c == 'w')
                {
                    c = fgetc(source);
                    if(c == ' ')
                    {
                        c = fgetc(source);
                        if(c == 'f')
                        {
                            c = fgetc(source);
                            if(c == 'o')
                            {
                                c = fgetc(source);
                                if(c == 'r')
                                {
                                    forStat = 1;
                                }
                            }
                        }
                    }
                }
            }
            if(forStat == 1 || forStat == 2)
            {
                if(c == '(')        //opening bracket of for kw
                {
                    forStat = 2;
                }
                if(c == ')' && forStat == 2)        //closing bracket of for kw
                {
                    forStat = 0;
                }
                continue;
            }

            ///     comparing parentheses
            if (forStat == 0)
            {
                if(c == '(')
                {
                    push(parStack, lineNo);
                }
                else if(c == ')')
                {
                    if( isempty(parStack))
                    {
                        printf("Unmatched ')' at line: %d,", lineNo);
                        printf("\n");
                    }
                    else
                    {
                        pop(parStack);
                    }
                }
                else if ( c == ';' || c == '{' )        //checking parentheses upto ; or { symbol
                {
                    if( !isempty(parStack))
                    {
                        printf("Unmatched '(' at line: ");
                        printStack(parStack);
                        printf("\n");

                        while(!isempty(parStack))
                        {
                            pop(parStack);
                        }
                    }
                }
            }
        }
    }
    while(!isempty(parStack))
    {
        pop(parStack);
    }
    fclose(source);
    fclose(target);

}

/// /////////////////////////////////////////////////////////////////////////////////////////////////
/// /////////////////////////////////////////////////////////////////////////////////////////////////
void unmatchedBraces(FILE *source, FILE *target)
{
    char c;
    char lineNoStr[20];
    _stack *brcStack = (_stack *)malloc(sizeof(_stack));
    createEmptyStack(brcStack);

    if(source == NULL || target == NULL)
    {
        printf("\nFile cannot be opened");
    }
    else
    {
        int i = 0, lineNoStart = 1;
        int forStat = 0;

        while( (c = fgetc(source)) != EOF )
        {
            ///   getting Line number and storing in lineNoStr String
            if(lineNoStart == 1 && c != ':')        // line number is upto : symbol
            {
                lineNoStr[i] = c;
                i++;
                continue;
            }
            else if(lineNoStart == 1 && c == ':')
            {
                lineNoStr[i] = '\0';
                i = 0;
                lineNoStart = 0;
            }
            else if(c == 10)     //line number starts after a new line
            {
                lineNoStart = 1;
                //printf("\n");
            }

            int lineNo = atoi(lineNoStr);   //converting lineNo char array(string) to integer

            ///     comparing braces
            if(c == '{')
            {
                push(brcStack, lineNo);
            }
            else if(c == '}')
            {
                if( isempty(brcStack))
                {
                    printf("Unmatched '}' at line: %d,", lineNo);
                    printf("\n");
                }
                else
                {
                    pop(brcStack);
                }
            }

        }
        if( !isempty(brcStack))
        {
            printf("Unmatched '{' at line: ");
            printStack(brcStack);
            printf("\n");
        }
    }
    while(!isempty(brcStack))
    {
        pop(brcStack);
    }
    fclose(source);
    fclose(target);
}

/// /////////////////////////////////////////////////////////////////////////////////////////////////
/// /////////////////////////////////////////////////////////////////////////////////////////////////
void duplicateToken(FILE *source, FILE *target)
{
    char c, currentStr[50], previousStr[50];

    if(source == NULL || target == NULL)
    {
        printf("\nFile cannot be opened");
    }
    else
    {
        int i = 0, lineNo = 1;
        while( (c = fgetc(source)) != EOF )
        {
            if(c == 10)     //line no increases after getting new line
            {
                lineNo++;
            }
            if(c == ';')     //semicolon resets previousStr variable
            {
                previousStr[0] = '\0';
            }

            if(c == ' ')        //checking each lexeme separately
            {
                currentStr[i] = '\0';
                i=0;

                if(isKeyword(currentStr))   //only keywords are comparing
                {
                    if(strcmp(previousStr, currentStr) == 0)    //if previously we got keyword is same as current
                    {
                        printf("Duplicate token %s at line %d\n", currentStr, lineNo);
                    }
                    strcpy(previousStr, currentStr);    //copying current to previous
                }
                continue;
            }
            else
            {
                currentStr[i] = c;
                i++;
            }
        }
    }

    fclose(source);
    fclose(target);
}

/// /////////////////////////////////////////////////////////////////////////////////////////////////
/// /////////////////////////////////////////////////////////////////////////////////////////////////
void duplicateSemicolon(FILE *source, FILE *target)
{
    char c;

    if(source == NULL || target == NULL)
    {
        printf("\nFile cannot be opened");
    }

    else
    {
        int i = 0, lineNo = 1, semicolonCount = 0, forStat = 0;
        while( (c = fgetc(source)) != EOF )
        {
            if(c == 10)     //line no increases after getting new line
            {
                lineNo++;
                semicolonCount = 0;
            }
            ///     for kw checking
            if(c == 'k')        //checking 'kw for' and setting forStat = 1
            {
                c = fgetc(source);
                if(c == 'w')
                {
                    c = fgetc(source);
                    if(c == ' ')
                    {
                        c = fgetc(source);
                        if(c == 'f')
                        {
                            c = fgetc(source);
                            if(c == 'o')
                            {
                                c = fgetc(source);
                                if(c == 'r')
                                {
                                    forStat = 1;
                                }
                            }
                        }
                    }
                }
            }
            if(forStat == 1 || forStat == 2)
            {
                if(c == '(')        //opening bracket of for kw
                {
                    forStat = 2;
                }
                if(c == ')' && forStat == 2)        //closing bracket of for kw
                {
                    forStat = 0;
                }
                continue;
            }
            /// other semicolon
            if (forStat == 0)
            {
                if(c == ';' && semicolonCount == 0)
                {
                    semicolonCount = 1;
                }
                else if (c == ';' && semicolonCount == 1)
                {
                    printf("Duplicate 'Semicolon' at line %d\n", lineNo);
                }

            }
        }
    }
    fclose(source);
    fclose(target);
}

/// /////////////////////////////////////////////////////////////////////////////////////////////////
/// /////////////////////////////////////////////////////////////////////////////////////////////////
void unknownError(FILE *source, FILE *target)
{
    char c;

    if(source == NULL || target == NULL)
    {
        printf("\nFile cannot be opened");
    }

    else
    {
        int i = 0, lineNo = 1, unknStat = 0;
        while( (c = fgetc(source)) != EOF )
        {
            if(c == 10)     //line no increases after getting new line
            {
                lineNo++;
            }
            ///     unkn checking
            if(c == 'u')
            {
                c = fgetc(source);
                if(c == 'n')
                {
                    c = fgetc(source);
                    if(c == 'k')
                    {
                        c = fgetc(source);
                        if(c == 'n')
                        {
                            c = fgetc(source);
                            if(c == ' ')
                            {
                                printf("'Unknown' error at line %d\n", lineNo);
                            }
                        }
                    }
                }
            }
            if(unknStat == 1)
            {

            }
        }
    }
    fclose(source);
    fclose(target);
}

/// /////////////////////////////////////////////////////////////////////////////////////////////////
/// /////////////////////////////////////////////////////////////////////////////////////////////////
void unbalancedIfElse(FILE *source, FILE *target)
{
    char c, str[50], previousStr[50];
    int ifStat=0;

    if(source == NULL || target == NULL)
    {
        printf("\nFile cannot be opened");
    }
    else
    {
        int i = 0, lineNo = 1;
        while( (c = fgetc(source)) != EOF )
        {
            if(c == 10)     //line no increases after getting new line
            {
                lineNo++;
            }

            if(c == ' ')        //checking each lexeme separately
            {
                str[i] = '\0';
                i=0;

                if(str[0]=='i' && str[1]=='f')
                {
                    ifStat=1;
                }

                else if(str[0]=='e' && str[1]=='l' && str[2]=='s' && str[3]=='e')
                {
                    if(ifStat == 0)
                        printf("Unmatched 'else' at line %d ",lineNo);

                    ifStat=0;
                }
                str[0] = '\0';
                i=0;
            }

            else
            {
                str[i] = c;
                i++;
            }
        }
    }

    fclose(source);
    fclose(target);
}

/// /////////////////////////////////////////////////////////////////////////////////////////////////
/// /////////////////////////////////////////////////////////////////////////////////////////////////
void findErrors(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30])
{
    unmatchedParentheses(source,target);

    source = fopen(sourceFileName, "r");
    target = fopen(targetFileName, "w");
    unmatchedBraces(source,target);

    source = fopen(sourceFileName, "r");
    target = fopen(targetFileName, "w");
    duplicateToken(source,target);

    source = fopen(sourceFileName, "r");
    target = fopen(targetFileName, "w");
    duplicateSemicolon(source,target);

    source = fopen(sourceFileName, "r");
    target = fopen(targetFileName, "w");
    unknownError(source,target);

    source = fopen(sourceFileName, "r");
    target = fopen(targetFileName, "w");
    unbalancedIfElse(source,target);
}
void lineNumberPrint(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]);

int main()
{
    char sourceFileName_0[30] = "170204055_Asm4_Input.txt";
    char targetFileName_1[30] = "170204055_Asm4_Out1.txt";  //removed comment output
    char targetFileName_2[30] = "170204055_Asm4_Out2.txt";  //removed space output
    char targetFileName_3[30] = "170204055_Asm4_Out3.txt";  //lexeme separator output
    char targetFileName_4[30] = "170204055_Asm4_Out4.txt";  //lexeme tokenized output
    char targetFileName_5[30] = "170204055_Asm4_Out5.txt";  //line number output
    char targetFileName_6[30] = "170204055_Asm4_Out6.txt";  //Error output
    FILE *source, *target;

    ///removing comment
    source = fopen(sourceFileName_0, "r");
    target = fopen(targetFileName_1, "w");
    removeComments(source, target, sourceFileName_0, targetFileName_1);

    ///removing spaces
    source = fopen(targetFileName_1, "r");
    target = fopen(targetFileName_2, "w");
    removeSpaces(source, target, targetFileName_1, targetFileName_2);

    ///lexeme separator
    source = fopen(targetFileName_2, "r");
    target = fopen(targetFileName_3, "w");
    lexemeSeparator(source, target, targetFileName_2, targetFileName_3);

    ///lexeme tokenized
    source = fopen(targetFileName_3, "r");
    target = fopen(targetFileName_4, "w");
    lexemeTokenization(source, target, targetFileName_3, targetFileName_4);

    ///lexeme tokenized
    source = fopen(targetFileName_4, "r");
    target = fopen(targetFileName_5, "w");
    lineNumberPrint(source, target, targetFileName_4, targetFileName_5);

    ///  printing in console
    char c;
    target = fopen (targetFileName_5,"r");
    while( (c = fgetc(target)) != EOF)
    {
        printf("%c",c);
    }
    fclose(target);
    printf("\n\n");

    printf("\n============== Errors ==============\n\n");
    ///Finding Errors
    source = fopen(targetFileName_5, "r");
    target = fopen(targetFileName_6, "w");
    findErrors(source, target, targetFileName_5, targetFileName_6);

    printf("\n\n");

    ///removing the file after operation
    remove (targetFileName_1);
    remove (targetFileName_2);
    //remove (targetFileName_3);
    remove (targetFileName_4);
    //remove (targetFileName_5);
    remove (targetFileName_6);
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void lineNumberPrint(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30])
{
    char c;
    int lineNo = 1;
    char lineNoBuffer[20];
    itoa(lineNo,lineNoBuffer,10);


    if(source == NULL)
    {
        printf("\nFile cannot be opened");
    }
    else
    {
        itoa(lineNo, lineNoBuffer,10);
        fputs(lineNoBuffer,target);
        fputs(": ",target);
        while( (c = fgetc(source)) != EOF )
        {
            if( (c == 10) )
            {
                fputc(10,target);
                lineNo++;
                itoa(lineNo,lineNoBuffer,10);
                fputs(lineNoBuffer,target);
                fputs(": ",target);
                continue;
            }

            fputc(c,target);
        }
    }
    fclose(source);
    fclose(target);
}

#include <stdio.h>
#include <stdio.h>

void omitComments(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]);
void omitSpaces(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]);

int main(){
    char c;
    char sourceFileName[30] = "170204055_Asm4.txt";
    char tempFileName[30] = "temp.txt";
    char targetFileName[30] = "170204055_Asm1.txt";
    FILE *source, *target, *temp;

    /*multi line comment
    hello world
    */
    //  removing comment
    source = fopen(sourceFileName, "r");
    temp = fopen(tempFileName, "w");
    omitComments(source, temp, sourceFileName, tempFileName);
    fclose(source);
    fclose(temp);

    //  removing spaces
    /*temp = fopen(tempFileName, "r");
    target = fopen(targetFileName, "w");
    omitSpaces(temp, target, tempFileName, targetFileName);
    fclose(temp);
    fclose(target);*/

    //  printing in console
    target = fopen (targetFileName,"r");
    while( (c = fgetc(target)) != EOF){
        printf("%c",c);
    }
    fclose(target);

    printf("\n\n");

    //  removing text file after operation
    //remove(tempFileName);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void omitComments(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]){
    char c;
    int slashStart = 0;
    int checkForCommentStop = 0;
    int singleLineComment = 0;
    int multipleLineComment = 0;

    if(source == NULL || target == NULL){
        printf("\nFile cannot be opened");
    }
    else{
        while( (c = fgetc(source)) != EOF ){
            //////////////////////////////////      single line comment started       ///////////////////////////////////
            if(singleLineComment == 1){
                //  stop when new line appears
                if(c == 10){
                    fputc(10,target);
                    singleLineComment = 0;
                    continue;
                }
            }
            ///////////////////////////////////     multi line comment started        ////////////////////////////////////
            else if(multipleLineComment == 1){
                //  ending star
                if(c == '*'){
                    checkForCommentStop = 1;
                    continue;
                }

                //  after getting star in multi line comment
                if(checkForCommentStop == 1){
                    //  comment ends after getting slash
                    if(c == '/'){
                        multipleLineComment = 0;
                        continue;
                    }
                    else {
                        checkForCommentStop = 0;
                        continue;
                    }
                }
            }
            /////////////////////////////////       Checking for comment          ///////////////////////////////////////
            else if(singleLineComment == 0 && multipleLineComment == 0){
                if(c == '/' && slashStart == 0){
                    slashStart = 1;
                    continue;
                }
                //for single line
                else if(c == '/' && slashStart == 1){
                    slashStart = 0;
                    singleLineComment = 1;
                    continue;
                }
                //for multi line
                else if(c == '*' && slashStart == 1){
                    slashStart = 0;
                    multipleLineComment = 1;
                    continue;
                }
                //one slash, means there might be division sign
                else if(c != '/' && slashStart == 1){
                    slashStart = 0;
                    fputc('/',target);
                    fputc(c,target);
                    continue;
                }
                //normal character, no comment possibility
                else {
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
void omitSpaces(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]){
    char c;
    int syntaxStart = 0;
    int syntaxSpace = 0;

    if(source == NULL || target == NULL){
        printf("\nFile cannot be opened");
    }
    else{
        while( (c = fgetc(source)) != EOF ){
            //removing tab
            if(c == 9){
                continue;
            }
            //removing new line
            else if(c == 10){
                syntaxStart = 0;
                continue;
            }
            //removing extra space from the beginning of a syntax
            else if(c == 32 && syntaxStart == 0){
                continue;
            }
            else{
                syntaxStart = 1;
            }

            //syntax started in that line
            if(syntaxStart = 1){
                //allowing first space between syntaxes
                if(c == 32 && syntaxSpace == 0){
                    fputc(32,target);
                    syntaxSpace = 1;
                    continue;
                }
                //removing more than 1 space between syntaxes
                else if(c == 32 && syntaxSpace == 1){
                    continue;
                }
            }
            //normal character, no space tendency
            fputc(c,target);
            syntaxSpace = 0;
        }
    }
    fclose(source);
    fclose(target);
}

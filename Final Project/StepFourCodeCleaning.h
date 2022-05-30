////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
void removeComments(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]){
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
void removeSpaces(FILE *source, FILE *target, char sourceFileName[30], char targetFileName[30]){
    char c;
    int syntaxStart = 0;
    int syntaxSpace = 0;

    char tempFileName[30] = "temp1.txt";
    FILE *temp;
    temp = fopen(tempFileName, "w");

    if(source == NULL || temp == NULL){
        printf("\nFile cannot be opened");
    }
    else{
        while( (c = fgetc(source)) != EOF ){
            //removing tab
            if(c == 9){
                fputc(32,temp);
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
                    fputc(32,temp);
                    syntaxSpace = 1;
                    continue;
                }
                //removing more than 1 space between syntaxes
                else if(c == 32 && syntaxSpace == 1){
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

    while( (c = fgetc(source)) != EOF ){
        if(c == 10){
            fputc(c,target);
            codeStart = 0;  //setting codestart variable to zero after getting new line
            continue;
        }
        else if(c == 32 && syntaxSpace == 0 && codeStart == 1){          //one space between syntaxes
            fputc(32,target);
            syntaxSpace = 1;
            continue;
        }
        else if(c == 32 && syntaxSpace == 1 && codeStart == 1){     //more than one space between syntaxes
            continue;
        }
        else if(c != 32){                                           //any character other than space
            fputc(c,target);
            codeStart = 1;
            syntaxSpace = 0;
        }
    }

    fclose(source);
    fclose(target);
    remove(tempFileName);
}

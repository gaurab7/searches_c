#include<stdio.h>
#include<string.h>
#include<conio.h>

#define MAX 100
#define MAX_TOKENS 100

int isException(char ch)
{
    char exceptions[] = {' ', ',', '.', '!', '?','_', '"'};
    int size = sizeof(exceptions)/sizeof(exceptions[0]);
    for(int i = 0; i < size; i++) {
        if(ch == exceptions[i]) {
            return 1;
        }

    }
    return 0;
}

void tokenize(char input[]){
    int tokenNum = 0, charInd =0;
    char tokens[MAX_TOKENS][MAX];
    for(int i=0;input[i] != '\0';i++)
    {
        if(!isException(input[i])){
            tokens[tokenNum][charInd++] = input[i];
        }
        else{
            if(charInd>0){
                tokens[tokenNum][charInd++] = '\0';
                tokenNum++;
                charInd = 0;
            }       
        }
    }
    
    if(charInd>0){
        tokens[tokenNum][charInd] = '\0';
        tokenNum++;
    }

    for(int i=0;i<tokenNum;i++){
        printf("Token %d: %s\n",i+1, tokens[i]);
    }
}

int main(){
    char text[MAX];
    printf("Enter the string:\n");
    scanf(" %[^\n]",&text);
    tokenize(text);
    return 0;

}
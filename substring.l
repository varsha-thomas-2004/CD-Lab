%{
#include<stdio.h>
#include<string.h>
int i = 0;
int flag = 0;
char name[50] = "";
%}

%%
[a-zA-Z]* {
    for(i=0;i<yyleng;i++)
    {
        if(yytext[i] == 'v' && yytext[i+1]=='a' && yytext[i+2]=='r' && yytext[i+3]=='s')
        {
        	flag = 1;
        }
    }
    strcpy(name,yytext);
}
[\n] {
    if(flag==1)
    {
        printf("%s contains 4 letters of name as substring\n",name);
        flag=0;
        strcpy(name,"");
        printf("Enter the string ");
    }
    else
    {
        printf("%s does not contain 4 letters of name as substring\n",name);
        strcpy(name,"");
        printf("Enter the string ");
    }
}
%%

int main()
{
    printf("Enter the string ");
    yylex();   // start analysis
    return 0;
}


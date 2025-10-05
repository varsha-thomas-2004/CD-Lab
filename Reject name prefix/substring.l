%{
#include<stdio.h>
%}

%option caseless

%%
.*vars.* { printf("Rejected\n"); }
.*  { printf("Accepted\n"); }
\n { printf("Enter the string: "); }
%%

int yywrap() { return 1; }

int main()
{
    printf("Enter the string: ");
    yylex();   // start analysis
    return 0;
}


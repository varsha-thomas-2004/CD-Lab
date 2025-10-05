%{
#include <stdio.h>
#include <stdlib.h>
void yyerror(char *s);
int yylex(void);
%}

%token VALID_ID INVALID EXIT

%%

start:
    line_list
;

line_list: /* allows multiple lines to be parsed in a sequence */
    line_list line
  | line
;

line:
    VALID_ID '\n'   { printf("Valid variable name\n"); }
  | INVALID '\n'    { printf("Invalid variable name\n"); }
  | EXIT '\n'       { printf("Exiting...\n"); exit(0); }
  | '\n'            { /* ignore empty line */ }
;

%%

void yyerror(char *s)
{
    /* Suppress default YACC error messages */
}

int main()
{
    printf("Enter variable names (type 'exit' to quit):\n");
    yyparse();   // start parsing; it loops naturally because of grammar
    return 0;
}


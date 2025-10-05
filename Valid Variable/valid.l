%{
#include "y.tab.h"
#include <string.h>
#include <stdio.h>
%}

%%
[a-zA-Z_][a-zA-Z_0-9]*   { 
                            if (strcmp(yytext, "exit") == 0)
                                return EXIT; 
                            else
                                return VALID_ID; 
                        }
[^\n]+                       { return INVALID; } /* anything else until newline */
\n			{ return '\n'; }  /* treat newline as a token */
%%
int yywrap() { return 1; }


%{
#define YYSTYPE char*
#include "y.tab.h"
#include "main.h"
void yyerror(const char * msg);
extern char* yylval;
%}
%option noyywrap
%%
[ \t]*;
[a-zA-Z\+\-\*\(\)]+        {/*printf("this is an expr  [%s]  ",yytext);*/
                            yylval = strdup(yytext);
                            printf("L[%s]  ",yylval);
                            return TOK_EXPR;}
[\n]                       {/*printf("\n");*/return TOK_EOL;}
<<EOF>>                    {return TOK_EOF; }
.;
%%


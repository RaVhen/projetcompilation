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
[a-zA-Z_]+                {
 	                    yylval = strdup(yytext);
	                    printf("L[%s]  ",yylval);
	                    return TOK_CMD;
                           }
[a-zA-Z1-9_\(\)-]+\.[a-z1-9]+ {
	                    yylval = strdup(yytext);
	                    printf("L[%s]  ",yylval);
	                    return TOK_IMG;
                           }
[-]?[1-9]+                 {
                            yylval = strdup(yytext);
	                    printf("L[%s]  ",yylval);
	                    return TOK_NBR;
                           }
[\n]                       {return TOK_EOL;}
<<EOF>>                    {return TOK_EOF; }
.                          ;
%%


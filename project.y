
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

 int yylex(void); 
 void yyerror (char* msg);
 extern FILE * yyin; 
 #define YYSTYPE char*
 Rules rules;
 char* temp;
 int done = 0; 
%}
%token TOK_EOL "end of line"
%token TOK_EOF "end of file"
%token TOK_EXPR "expr"

%%
input:
      TOK_EOF {printf("\n\nFIN\n\n");YYABORT;}          //Abort find EOF
     |line TOK_EOF   {printf("\n\nFIN\n\n");YYABORT;}
     |line TOK_EOL input
     ;

line:
    TOK_EXPR  TOK_EXPR       {printf("Y1[%s] Y2[%s] endl\n",$1,$2);
                              rules = addRule(rules,$1,$2);
                              echoRules(rules);}
    |TOK_EXPR                {printf("Y1[%s] endl\n",$1);
                              rules = addRule(rules,$1,"#");
                              echoRules(rules);}
    ;


%%
void yyerror (char* msg){
  printf ("Error: %s\n", msg);			
  exit(-1);
}

Rules returnList(){
  return (rules);
}

int isDone(){
  return done;
}

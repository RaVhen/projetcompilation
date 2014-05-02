
%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "main.h"

 int yylex(void); 
 void yyerror (char* msg);
 extern FILE * yyin; 
 #define YYSTYPE char*
 char* command;
 char* option; 
%}
%token TOK_EOL "end of line"
%token TOK_EOF "end of file"
%token TOK_CMD "command"
%token TOK_NBR "number"

%%
input:
      TOK_EOF            {printf("\n\nFIN\n\n");YYABORT;}          //Abort find EOF
     |line TOK_EOF       {printf("\n\nFIN\n\n");YYABORT;}
     |line TOK_EOL input
     ;

line:
    TOK_CMD  TOK_NBR       {printf("Y1[%s] Y2[%s] endl\n",$1,$2);
	                    command = malloc(sizeof(strlen($1))*1);
	                    option = malloc(sizeof(strlen($2))*1);
	                    strcpy(command,$1);
	                    strcpy(option,$2);
                           }
    |TOK_CMD               {printf("Y1[%s] endl\n",$1);
	                    command = malloc(sizeof(strlen($1))*1);
	                    strcpy(command,$1);
                           }
    ;


%%
void yyerror (char* msg){
  printf ("Error: %s\n", msg);			
  exit(-1);
}

char* returnCommand(){
	return (command);
}

char* returnOption(){
	return (option);
}


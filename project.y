
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
 char* command;
 char* option; 
 char* inputPic;   //nom du fichier d entree
 char* outputPic;  //nom du fichier de sortie
%}
%token TOK_EOL "end of line"
%token TOK_EOF "end of file"
%token TOK_CMD "command"
%token TOK_NBR "number"
%token TOK_IMG "image"

%%
input:
      TOK_EOF            {printf("\n\nFIN\n\n");YYABORT;}          //Abort find EOF
     |line TOK_EOF       {printf("\n\nFIN\n\n");YYABORT;}
     |line TOK_EOL       {printf("\n\nFIN\n\n");YYABORT;}
     ;

line:
     TOK_CMD  TOK_NBR  TOK_IMG       {printf("Y1[%s] Y2[%s] Y3[%s] endl\n",$1,$2,$3);
	                              command = malloc(sizeof(strlen($1))*1);
	                              option = malloc(sizeof(strlen($2))*1);
				      inputPic = malloc(sizeof(strlen($3))*1);
	                              strcpy(command,$1);
	                              strcpy(option,$2);
				      strcpy(inputPic,$3);
				      rules = addRule(rules,"command",command);
				      rules = addRule(rules,"option",option);
				      rules = addRule(rules,"input",inputPic);
                                     }
    |TOK_CMD TOK_IMG TOK_IMG    {printf("Y1[%s] Y2[%s] Y3[%s] endl\n",$1,$2,$3);
	                         command = malloc(sizeof(strlen($1))*1);
	                         inputPic = malloc(sizeof(strlen($2))*1);
	                         outputPic = malloc(sizeof(strlen($3))*1);
	                         strcpy(command,$1);
	                         strcpy(inputPic,$2);
				 strcpy(outputPic,$3);
				 rules = addRule(rules,"command",command);
				 rules = addRule(rules,"input",inputPic);
				 rules = addRule(rules,"output",outputPic);
                                }

     |TOK_CMD TOK_IMG        {printf("Y1[%s] Y2[%s]endl\n",$1,$2);
	                         command = malloc(sizeof(strlen($1))*1);
	                         inputPic = malloc(sizeof(strlen($2))*1);
	                         strcpy(command,$1);
	                         strcpy(inputPic,$2);
				 rules = addRule(rules,"command",command);
				 rules = addRule(rules,"input",inputPic);
                                }
     |TOK_CMD               {printf("Y1[%s] endl\n",$1);
	                     command = malloc(sizeof(strlen($1))*1);
			     strcpy(command,$1);
			     rules = addRule(rules,"command",command);
                            }
    ;


%%
void yyerror (char* msg){
  printf ("Error: %s\n", msg);			
  exit(-1);
}

Rules returnList(){
  return (rules);
}

char* returnCommand(){
	return (command);
}

char* returnOption(){
	return (option);
}


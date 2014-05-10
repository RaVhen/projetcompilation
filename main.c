#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

#define DEBUG 1

extern FILE *yyin;
extern FILE *yyout;
extern int yyparse(void);


/*
int readGrammarFromFile(char* filename){

	FILE* file
	
	scanf(%s, nonTerminal);
	
}
*/


Rules addRule(Rules r, char* type, char* name)
{
	Rules new;
		
	if(r==NULL){
	
		new = malloc(sizeof(Rule));
		if (new ==NULL)
			return(NULL);
		
		new->type = malloc(strlen(type) * sizeof(char) +1);
		new->name = malloc(strlen(name) * sizeof(char) +1);
		
		
		strcpy(new->type, type);
		strcpy(new->name, name);
		
		new->nextRule = NULL;
		r = new;
		return(new);
	}
	
	
	r->nextRule = addRule(r->nextRule, type, name);
	return(r);
}

void freeRules(Rules r){
	if(r){
		freeRules(r->nextRule);
		free(r->type);
		free(r->name);
		free(r);
	}

}


void echoRule(Rule rule){
	
	printf("%s -> %s\n", rule.type, rule.name);

}

int echoRules(Rules rules){
	while(rules){
		printf("%s -> %s\n", rules->type, rules->name);
		rules = rules->nextRule;
	} 
	return 0;
}




int compteur_(Rules t, int compt)
{
	if(!t)
		return (compt);

	return(compteur_(t->nextRule, compt+1));

}

int compteur(Rules t){
	return(compteur_(t, 0));
}


Rule getRuleN(Rules r, int n){

	if(n==0)
		exit(1);
	
	if(n==1)
		return *r;

	return getRuleN(r->nextRule, n-1);
}

Rules removeRuleN_(Rules r, int curN, int finalN){


		
	if(curN==finalN){ //free here
	
		/*
			[]->[]->[]->[]->
					^you are here
			[]->--->[]->[]->
		
		
		*/
		Rules next = r->nextRule;
		
		free(r->type);
		free(r->name);
		free(r);
		
		return(next);
	}
	
	
	r->nextRule = removeRuleN_(r->nextRule, curN+1, finalN);
	return(r);
	

}

Rules removeRuleN(Rules r, int n){
	return(removeRuleN_(r, 1, n));
}

char* newNotPresentRule(char* name, Rules r){
	
	char* newName = malloc((strlen(name)+2)*sizeof(char));
	char* newnewName;
	newName = strcpy(newName, name);
	newName[strlen(name)-2] = '\'';
	newName[strlen(name)-1] = '\0';
	
	Rules cur = r;
	while(cur){ //scan the whole list
	
	
		if(strcmp(cur->type, name)!=0){ //this name allready exists
			//we add another char to the name
			newnewName = malloc((strlen(newName)+2)*sizeof(char));
			newnewName[strlen(newName)-2] = '\'';
			newnewName[strlen(newName)-1] = '\0';
			free(newName);
			newName = newnewName;
			cur = r; //lets rescan from the beginning !
		}
		
		cur = cur->nextRule;
	}
	
}
int main(int argc, char** argv){
	
	/* TODO alphabets */
	Rule* rules;
	rules = NULL;
	rules = addRule(rules, "A", "a");
	rules = addRule(rules, "B", "bb");
	rules = addRule(rules, "C", "cc");
	
	
	printf("\nRule1:");
	echoRule(getRuleN(rules, 1));
	
	printf("\nRule2:");
	echoRule(getRuleN(rules, 2));
	
	printf("\nRule3:");
	echoRule(getRuleN(rules, 3));
	
	echoRules(rules);
	printf("REmoving rule #2\n");
	removeRuleN(rules, 2);
	echoRules(rules);
	//printf("%d regles\n", compteur(rules));
	
	freeRules(rules);



	Rule* manu = NULL;
	printf("\n\n<(^_^<) <(^_^)^ ^(^_^)^ ^(^_^)> (>^_^)>\n\n");
	Rule* dalmar = NULL;
	int done;
	//echoRules(dalmar);
	yyin = stdin;
	yyparse();
	manu = NULL;
	printf("\n\n<(^_^<) <(^_^)^ ^(^_^)^ ^(^_^)> (>^_^)>\n\n");	
	//echoRules(manu);
	//fclose(yyin);

	return 0;

}

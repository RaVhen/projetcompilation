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

/*Ouverture d'un fichier*/
void ouvrir(char filename[]){
  char commande[50];
  strcat(commande, "display");
  strcat(commande, " ");
  strcat(commande, filename);
  system(commande);
}

/*Donne les informations du fichier*/
void infos(char filename[]){
  char commande[50];
  strcat(commande, "identify");
  strcat(commande, " ");
  strcat(commande, "-ping");
  strcat(commande, " ");
  strcat(commande, filename);
  system(commande);
}

/*Enregistre dans un nouveau format*/
void format(char filename[], char type[]){
  char commande[50];
  strcat(commande, "convert");
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, ".");
  strcat(commande, type);
  system(commande);
}

/*upside-down*/
void retourne_HB(char filename[]){
  char commande[50];
  strcat(commande, "convert -flip ");
  strcat(commande, filename);
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, ".upsidedown.png");
  system(commande);
}

/*effet miroir*/
void retourne_GD(char filename[]){
  char commande[50];
  strcat(commande, "convert -flop ");
  strcat(commande, filename);
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, ".mirror.png");
  system(commande);
}

/*blur it all*/
void blur(char filename[]){
  char commande[50];
  strcat(commande, "convert -blur 10x2 ");
  strcat(commande, filename);
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, ".blurry.png");
  system(commande);
}

/*dessine un contour*/
void contour(char filename[]){
  char commande[50];
  strcat(commande, "convert -bordercolor #000000 -border ");
  strcat(commande, filename);
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, ".border.png");
  system(commande);
}

/*effet dessin*/
void dessin(char filename[]){
  char commande[50];
  strcat(commande, "commande -charcoal 4 ");
  strcat(commande, filename);
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, ".dessin.png");
  system(commande);
}

/*noir et blanc*/
void n_b(char filename[]){
  char commande[50];
  strcat(commande, "convert -monochrome ");
  strcat(commande, filename);
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, ".black_&_white.png");
  system(commande);
}

/*rotate de i°*/
void rotate(char filename[], char deg[]){
  char commande[50];
  strcat(commande, "convert -rotate \"");
  strcat(commande, deg);
  strcat(commande, "\" ");
  strcat(commande, filename);
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, ".rotate_");
  strcat(commande, deg);
  strcat(commande, "_degrees.png");
  system(commande);
}


int main(int argc, char** argv){
	
	/* TODO alphabets */
	Rule* rules;
	//Rule* rule1;
	//char filename[50];
	rules = NULL;
	rules = addRule(rules, "A", "a");
	rules = addRule(rules, "B", "bb");
	rules = addRule(rules, "C", "cc");
	//rule1 = *getRulesN(rules, 1);
	//filename = rule1 -> name;

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
	manu = returnList();
	printf("\n\n<(^_^<) <(^_^)^ ^(^_^)^ ^(^_^)> (>^_^)>\n\n");	
	echoRules(manu);
	Rule* tmp = manu;
	Rule* tmp_fich = NULL;
	Rule* tmp_op = NULL;
	char commande[15];
	char test[15] = "ouvrir";
	printf("debug1\n");
	
	while(tmp != NULL){
	  strcpy(commande, tmp -> name);

	  if(strcmp(commande, "ouvrir") == 0){
	    printf("OPEN\n"); 
	    tmp_fich = tmp -> nextRule;
	    system("pwd");
	    ouvrir(tmp_fich -> name);
	  }
	  if(strcmp(commande, "infos") == 0){
	    tmp_fich = tmp -> nextRule;
	    system("pwd");
	    infos(tmp_fich -> name);
	  }
	  if(strcmp(commande, "format") == 0){
	    tmp_fich = tmp -> nextRule;
	    tmp_op = tmp_fich -> nextRule;
	    system("pwd");
	    format(tmp_fich -> name, tmp_op -> name);
	  }
	  if(strcmp(commande, "retourne_HB") == 0){
	    tmp_fich = tmp -> nextRule;
	    system("pwd");
	    retourne_HB(tmp_fich -> name);
	  }
	  if(strcmp(commande, "retourne_GD") == 0){
	    tmp_fich = tmp -> nextRule;
	    system("pwd");
	    retourne_GD(tmp_fich -> name);
	  }
	  if(strcmp(commande, "blur") == 0){
	    tmp_fich = tmp -> nextRule;
	    system("pwd");
	    blur(tmp_fich -> name);
	  }
	  if(strcmp(commande, "contour") == 0){
	    tmp_fich = tmp -> nextRule;
	    system("pwd");
	    contour(tmp_fich -> name);
	  }
	  if(strcmp(commande, "dessin") == 0){
	    tmp_fich = tmp -> nextRule;
	    system("pwd");
	    dessin(tmp_fich -> name);
	  }
	  if(strcmp(commande, "nb") == 0){
	    tmp_fich = tmp -> nextRule;
	    system("pwd");
	    n_b(tmp_fich -> name);
	  }
	  if(strcmp(commande, "rotate") == 0){
	    tmp_fich = tmp -> nextRule;
	    tmp_op = tmp_fich -> nextRule;
	    system("pwd");
	    rotate(tmp_fich -> name, tmp_op -> name);
	  }
	  tmp = tmp -> nextRule;
	}

	//fclose(yyin);

	return 0;

}

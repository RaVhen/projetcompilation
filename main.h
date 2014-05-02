#ifndef _MAIN_HEADER_
#define _MAIN_HEADER_
extern FILE* yyin;

typedef struct Rule_ {
  char* nonTerminal;
  char* replacement;
  struct Rule_ * nextRule;
} Rule;

typedef Rule* Rules;

Rules returnList();
int isDone();
Rules addRule(Rules r, char* nonTerminal, char* replacement);
#endif

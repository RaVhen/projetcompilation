#ifndef _MAIN_HEADER_
#define _MAIN_HEADER_
extern FILE* yyin;

typedef struct Rule_ {
  char* type;
  char* name;
  struct Rule_ * nextRule;
} Rule;

typedef Rule* Rules;

Rules returnList();
int isDone();
Rules addRule(Rules r, char* type, char* name);
#endif

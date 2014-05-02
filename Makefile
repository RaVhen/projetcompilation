NAME = projet
CFILE = main.c
LFILE = project.l
YFILE = project.y

.PHONY: all clean

all: y.tab.c lex.yy.c
	gcc -o $(NAME) y.tab.c lex.yy.c $(CFILE)

y.tab.c y.tab.h: $(YFILE)
	yacc -d $(YFILE)

lex.yy.c: y.tab.h
	flex $(LFILE)

clean:
	rm -f y.tab.c y.tab.h lex.yy.c $(NAME)
a.out: parse.o prabsyn.o \
	   printtree.o \
       y.tab.o lex.yy.o  \
	   errormsg.o util.o \
	   table.o absyn.o symbol.o semant.o types.o env.o \
	   translate.o frame.o temp.o tree.o \
	   canon.o
	cc -g parse.o prabsyn.o \
		  printtree.o \
		  y.tab.o lex.yy.o errormsg.o util.o \
		  table.o absyn.o symbol.o semant.o types.o env.o \
		  translate.o frame.o temp.o tree.o \
		  canon.o
canon.o: canon.c
	cc -g -c canon.c

printtree.o: printtree.c
	cc -g -c printtree.c

tree.o: tree.c tree.h
	cc -g -c tree.c

temp.o: temp.c temp.h
	cc -g -c temp.c

translate.o: translate.c translate.h
	cc -g -c translate.c

frame.o: uframe.c frame.h
	cc -g -c -o frame.o uframe.c

types.o: types.c types.h
	cc -g -c types.c
	
env.o: env.c env.h
	cc -g -c env.c

semant.o: semant.c semant.h
	cc -g -c semant.c

parse.o: parse.c errormsg.h util.h
	cc -g -c parse.c

y.tab.o: y.tab.c
	cc -g -c y.tab.c

y.tab.c: tiger.y
	yacc -dv tiger.y

y.tab.h: y.tab.c
	echo "y.tab.h was created at the same time as y.tab.c"

symbol.o: symbol.c symbol.h
	cc -g -c symbol.c

absyn.o: absyn.c absyn.h
	cc -g -c absyn.c

table.o: table.c table.h
	cc -g -c table.c

prabsyn.o: prabsyn.c prabsyn.h
	cc -g -c prabsyn.c

errormsg.o: errormsg.c errormsg.h util.h
	cc -g -c errormsg.c

lex.yy.o: lex.yy.c symbol.h absyn.h y.tab.h errormsg.h util.h
	cc -g -c lex.yy.c

lex.yy.c: tiger.lex
	lex tiger.lex

util.o: util.c util.h
	cc -g -c util.c

clean: 
	rm -f a.out util.o parsetest.o lex.yy.o errormsg.o y.tab.c y.tab.h y.tab.o

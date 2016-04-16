compiler_test : main.o lexer.o expr.o
	cc -o compiler_test main.o lexer.o expr.o

main.o : main.c expr.h lexer.h
	cc -c main.c

lexer.o : lexer.c lexer.h token.h
	cc -c lexer.c

expr.o : expr.c lexer.h token.h
	cc -c expr.c

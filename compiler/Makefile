
all:
	flex src/lexer.l
	gcc -o bolt lex.yy.c src/main.c -lfl -lcjson

clean:
	rm -f bolt $(LEX_GEN)
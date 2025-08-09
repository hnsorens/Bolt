
all:
	flex src/lexer.l
	bison --language=c -d src/parser.y
	gcc -o bolt lex.yy.c parser.tab.c src/main.c src/ASTNodes.c src/codeGenerator.c -lfl -lcjson

clean:
	rm -f bolt $(LEX_GEN)
libs = modules/c-str-functions/lib/str_functions.o
libs_h = modules/c-str-functions/src/

str_functions.o:
	cd ./modules/c-str-functions && make str_functions.o -f ./Makefile

tree.o: str_functions.o
	gcc -o ./lib/tree.o -c ./src/tree.c -I./$(libs) -I./$(libs_h)

tree_test: tree.o
	gcc -o ./bin/tree_test ./lib/tree.o -I./$(libs) -I./$(libs_h) ./src/tree_test.c




dependencies = modules/c-str-functions
dependencies_src = -I./modules/c-str-functions/src/
dependencies_lib = -I./modules/c-str-functions/lib/

all: tree.o tree_test
.PHONY: $(dependencies) all

$(dependencies): 
	$(MAKE) -C $@	

tree.o: $(dependencies)
	gcc -o ./lib/tree.o -c ./src/tree.c $(dependencies_src) $(dependencies_lib)

tree_test: tree.o
	gcc -o ./bin/tree_test ./lib/tree.o $(dependencies_src) $(dependencies_lib) ./src/tree_test.c




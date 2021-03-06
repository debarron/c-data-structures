#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_functions.h"

typedef struct node_t {
  char* path;
  void* data;
  struct node_t* children;
  struct node_t* next;
  struct node_t* parent;
  int children_n;
} tree_t;

tree_t* tree_new_node(char* path, void* data);
tree_t* tree_init();

void tree_add_children(tree_t* root, char* element, void* data);
char tree_add(tree_t* root, char* path, void* data);

void tree_print_children(tree_t* root);

void tree_print_struct(tree_t* root, char* suffix);

tree_t* tree_find_next(tree_t* root, char* element);
tree_t* tree_find_children(tree_t* root, char* element);
tree_t* tree_find_parent(tree_t* root, char* path);
tree_t* tree_find(tree_t* root, char* path);

char** tree_get_children_names(tree_t* root);

#endif

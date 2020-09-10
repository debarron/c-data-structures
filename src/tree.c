
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str_functions.h"

#include "tree.h"

tree_t* tree_new_node(char* path, void* data){
  tree_t* new_node = (tree_t*) malloc(sizeof(tree_t));
  
  if(new_node == NULL) return NULL;
  
  new_node->path = str_duplicate(path);
  new_node->data = data;
  new_node->children = NULL;
  new_node->next = NULL;
  new_node->children_n = 0;

  return new_node;
}

tree_t* tree_init(){
  return tree_new_node("/", NULL);
}

void tree_add_children(tree_t* root, char* element, void* data){
  tree_t* new_node = tree_new_node(element, data);
  tree_t* children = root->children;

  root->children_n++;
  if(root->children == NULL)
    root->children = new_node;
  else{
    while(children->next != NULL)
      children = children->next;

    children->next = new_node;
  }
}

void tree_print_children(tree_t *root){
  tree_t* child = root->children;
  while(child != NULL){
    fprintf(stdout, "%s\n", child->path);
    child = child->next;
  }
}

void tree_print_struct(tree_t* root, char* suffix){
  tree_t* children;

  if(root == NULL) return;
  else{
    fprintf(stdout, "--%s\n", str_concat(suffix, root->path));
    tree_print_struct(root->children, str_concat(suffix, " +"));
    tree_print_struct(root->next, suffix);
  }
}

tree_t* tree_find_next(tree_t* root, char* element){
  tree_t* result = NULL;
  char found = 0;

  for(tree_t* current = root; (current != NULL && !found); current = current->next)
    if(strcmp(current->path, element) == 0){
      result = current;
      found = 1;
    }

  return result;
}

tree_t* tree_find_children(tree_t* root, char* element){
  if(root->children == NULL) return NULL;
  else return tree_find_next(root->children, element);
}

tree_t* tree_find_parent(tree_t* root, char* path){
  char** arr_path;
  char* prev_path;
  int arr_path_lenght;
  tree_t* parent;

  arr_path = str_path_to_arr(path, &arr_path_lenght);
  prev_path = str_array_to_str(arr_path, arr_path_lenght-1);  
  parent = tree_find(root, prev_path);

  free(prev_path);
  for(int i = 0; i < arr_path_lenght; i++) free(arr_path[i]);
  free(arr_path);

  return parent;
}

char tree_add(tree_t* root, char* path, void* data){
  char** arr_path;
  char* new_element;
  int arr_path_lenght;
  tree_t* parent;

  arr_path = str_path_to_arr(path, &arr_path_lenght);
  new_element = arr_path[arr_path_lenght-1];
  
  parent = tree_find_parent(root, path);
  if(parent == NULL) return 0;

  tree_add_children(parent, new_element, data);
  return 1;
}

tree_t* tree_find(tree_t* root, char* path){
  char** path_arr;
  int path_arr_lenght;
  char not_exists = 0;
  tree_t* result = NULL;
  tree_t* temp = NULL;

  if(strcmp(root->path, path) == 0)
    return root;
  
  temp = root;
  path_arr = str_path_to_arr(path, &path_arr_lenght);
  for(int i = 1; i < path_arr_lenght && !not_exists; i++){
    result = tree_find_children(temp, path_arr[i]);

    if(result == NULL)
      not_exists = 1;
  
    temp = result;
  }

  return result;
}

char** tree_get_children_names(tree_t* root){
  char** children;
  int child_index;

  if(root->children_n == 0)
    return NULL;

  child_index = 0;
  children = (char**) malloc(sizeof(char*) * root->children_n);
  for(tree_t* child = root->children; child != NULL; child = child->next)
    children[child_index++] = child->path;

  return children;
}







#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

#define GO_LEFT current = current->left;
#define GO_RIGHT current = current->right;

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

    //new->lower_than = lower_than;

    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    if (new == NULL) exit(EXIT_FAILURE);

    new->current = NULL;
    new->root = NULL;
    new->lower_than = lower_than;

    return new;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {

    TreeNode * current = tree->root;

    while (current != NULL){
        if (is_equal(tree, key, current->pair->key) == 1){
            return;
        }
        if (tree->lower_than(key, current->pair->key) == 1){
            GO_LEFT;
        }
        else {
            GO_RIGHT;
        }
    }

    TreeNode * new = createTreeNode(key, value);
    if (tree->root == NULL){
        tree->root = new;
    }
    else {
        new->parent = current->parent;
    }

    tree->current = new;
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    
    TreeNode * current = tree->root;
    Pair * result = NULL;

    while (current != NULL){
        if (is_equal(tree, key, current->pair->key) == 1){
            result = current->pair;
            break;
        }
        if (tree->lower_than(key, current->pair->key)){
            GO_LEFT;
        }
        else {
            GO_RIGHT;
        }
    }
    tree->current = current;
    
    return result;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}

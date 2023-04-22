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
    TreeNode * new = createTreeNode(key, value);
    tree->current = new;

    if (tree->root == NULL){
        tree->root = new;
    }

    while (current != NULL){
        if (is_equal(tree, key, current->pair->key) == 1){
            return;
        }
        if (tree->lower_than(key, current->pair->key) == 1){
            if (current->left == NULL){
                current->left = new;
                new->parent = current;
                return;
            }
            GO_LEFT;
        }
        else {
            if (current->right == NULL){
                current->right = new;
                new->parent = current;
                return;
            }
            GO_RIGHT;
        } 
    }
}

TreeNode * minimum(TreeNode * x){
    TreeNode * current = x;
    while (current->left != NULL){
        GO_LEFT;
    }
    return current;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    if (node->left == NULL && node->right == NULL){
        if (tree->lower_than(node->pair->key, node->parent->pair->key) == 1){
            node->parent->left = NULL;
            return;
        }
        else {
            node->parent->right = NULL;
            return;
        }
    }
    else if (node->left == NULL || node->right == NULL){
        if (node->left == NULL){
            if (tree->lower_than(node->pair->key, node->parent->pair->key) == 1){
                node->parent->left = node->right;
                node->right->parent = node->parent;
                return;
            }
            else {
                node->parent->right = node->right;
                node->right->parent = node->parent;
                return;
            }
        }

        if (tree->lower_than(node->pair->key, node->parent->pair->key) == 1){
            node->parent->left = node->left;
            node->left->parent = node->parent;
            return;
        }
        else {
            node->parent->right = node->left;
            node->left->parent = node->parent;
            return;
        }
    }
    else {
        TreeNode * current = node;
        GO_RIGHT;

        current = minimum(current);
        node->pair->key = current->pair->key;
        node->pair->value = current->pair->value; 
        removeNode(tree, current);

        return;
    }
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
    TreeNode * firstNode = minimum(tree->root);
    tree->current = firstNode;
    return firstNode->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    if (tree->current->right == NULL){
        if (tree->lower_than(tree->current->pair->key, tree->current->parent->pair->key) == 1){
            tree->current = tree->current->parent;
            return tree->current->pair;
        }
        return NULL;
    }
    else {
        TreeNode * next = minimum(tree->current->right);
        tree->current = next;
        return next->pair;
    }
}



#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BST.h"


struct treeNode {
    TreeItem item;
    treelink left;
    treelink right;
};

static treelink createNode(TreeItem item){
     treelink t = (treelink) malloc (sizeof (*t));
     t->item = item;
     t->left = NULL;
     t->right = NULL;
     return t;
}

TreeItem getItem(treelink t){
     assert(t != NULL);
     return t->item;
}

void printTreeNode (treelink t) {
     if(t != NULL);
     printf("%d ",t->item);
}

void preorderTraversal (treelink tree, void (*visit) (treelink)) {
    if (tree == NULL) {
       return;
    }
    (*visit)(tree);
    preorderTraversal (tree->left,visit);
    preorderTraversal (tree->right,visit);
}

treelink insertTreeNode (treelink tree, TreeItem item) {
  if (tree == NULL) {
      tree = createNode(item);
      tree->item = item;
      tree->left = NULL;
      tree->right = NULL;
   
  } else if (tree->item < item) {
      tree->right = insertTreeNode (tree->right, item);
  } else {
      tree->left = insertTreeNode (tree->left, item);
  }
  return tree;
}

int size(treelink t){
    if(t == NULL){
        return 0;
    } else {
        return 1 + size(t->left) + size(t->right);
    }
}

//returns the node of the element with item i
treelink search(treelink t, TreeItem i){
    treelink result = NULL;
    if (t == NULL) {
        result = NULL;
    } else if( i < t->item ){
        result = search(t->left,i); 
    } else if( i > t->item ){
        result = search(t->right,i);   
    } else {
        result = t;
    }    
    return result;
}



int countLeaves(treelink tree){
    if(tree == NULL){
        return 0;
    } else if(tree->left == NULL && tree->right == NULL){
        return 1;
    } else {
        return countLeaves(tree->left) + countLeaves(tree->right);
    }
}

//Should return the root of the tree
treelink searchInsert(treelink t, TreeItem i){
     if (t == NULL) {       // Test for end-point
         t = createNode(i); 
     } else if (i < t->item){
         // Traverse left sub-tree
         t->left = searchInsert(t->left, i);
     } else if (i > t->item) {
         // Traverse right sub-tree
         t->right = searchInsert(t->right, i);
     } //else you already have it in the tree
     return t;
}

int countIf (treelink tree, int (*pred)(TreeItem)){
    if(tree == NULL){
        return 0;
    } else if((*pred)(tree->item)){
        return 1 + countIf(tree->left,pred) + countIf(tree->right,pred);
    } else {
        return countIf(tree->left,pred) + countIf(tree->right,pred);
    }
}

int isEven (TreeItem n){
    return (n % 2 == 0);
}
int isOdd (TreeItem n){
    return (n % 2 == 1);
}

int isNegative (TreeItem n){
    return (n < 0);
}

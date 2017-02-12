//
//  BST.c
//  就是test一下delete啦
//
//  Created by Flora Li on 29/12/16.
//  Copyright © 2016 Flora Li. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "BST.h"
//#include "Stack.h"
//#include "Queue.h" //so we can do a level order traversal


struct treeNode {
    TreeItem item; //int
    Treelink left; //struct treeNode *
    Treelink right;
};

//Local helper functions
static Treelink createNode(TreeItem item){
    Treelink n = malloc(sizeof(struct treeNode));
    assert(n!=NULL);
    n->item = item;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void destroyTree(Treelink tree){
    if( tree != NULL){
        destroyTree(tree->left);
        destroyTree(tree->right);
        
        free(tree);
    }
}


static int max(TreeItem i1, TreeItem i2){
    if(i1 >= i2)
        return i1;
    return i2;
}

int height(Treelink t){
    if(t == NULL){
        return -1;
    } else {
        int leftHeight = height(t->left);
        int rightHeight = height(t->right);
        int maxHeight = max(leftHeight,rightHeight);
        return maxHeight + 1;
        
    }
}

int size(Treelink t){
    
    if(t == NULL){
        return 0;
    } else {
        return  1 + size(t->left) + size(t->right);
    }
    
}

//Interface functions

TreeItem getItem(Treelink node){
    assert(node != NULL);
    return node->item;
}

Treelink createTree(void){
    return NULL;
}




//returns the node of the element with item i
Treelink search(Treelink t, TreeItem i){
    Treelink result = NULL;
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

//returns the node of the element with item i
Treelink searchIterative(Treelink t, TreeItem i){
    Treelink curr = t;
    while(curr != NULL){
        if(curr->item == i){
            return curr;
        } else if ( i < curr->item){
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return NULL;
}




void inorderTraversal (Treelink tree) {
    if(tree != NULL){
        inorderTraversal(tree->left);
        printf("%d ",tree->item);
        inorderTraversal(tree->right);
    }
}

void postorderTraversal (Treelink tree) {
    
    if(tree != NULL){
        postorderTraversal(tree->left);
        postorderTraversal(tree->right);
        printf("%d ",tree->item);
    }
}



void preorderTraversal (Treelink tree){
    
    if(tree != NULL){
        TreeItemShow(tree->item);
        //printf("%d ",tree->item);
        preorderTraversal(tree->left);
        preorderTraversal(tree->right);
        
    }
}


//Returns the root of the tree
//inserts duplicates on theleft hand side of tree
Treelink insertRec (Treelink tree, TreeItem item) {
    if(tree == NULL){
        Treelink newNode = createNode(item);
        return newNode; //now the root of the tree
    } else {
        if(item <= tree->item){
            tree->left = insertRec(tree->left, item); //
        } else {
            tree->right = insertRec(tree->right, item);
        }
    }
    return tree;
}

//Returns the root of the tree
//inserts duplicates on theleft hand side of tree
Treelink insertIterative(Treelink tree, TreeItem key) {
    Treelink curr = tree;
    Treelink prev = NULL;
    Treelink newNode = createNode(key);
    while(curr != NULL){
        prev = curr;
        if ( key <= curr->item){
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    if(prev == NULL){
        return newNode;
    } else if(key <= prev->item){
        prev->left = newNode;
    } else {
        prev->right = newNode;
    }
    return tree;
    
}



void mirror(Treelink tree){
    Treelink curr = tree;
    if(curr->left != NULL){
        mirror(curr->left);
    }
    if(curr->right != NULL){
        mirror(curr->right);
    }
    Treelink store = curr;
    curr = store->left;
    store->left = store->right;
    store->right = curr;
    
}

/*int hasPathSum(Treelink tree, int sum){
    int sumval=0;
    if(tree==NULL) return 0;
    
    if(tree->left!=NULL){
        sumval=sumval+tree->item+hasPathSum(tree->left,sum);
    }
    if(tree->right != NULL){
        sumval=sumval+tree->item+hasPathSum(tree->right, sum);
    }
    if(sumval == sum) return 0;
    else {
        return sumval;
    }
    return 1;
}
*/
int hasPathSum(Treelink tree, int sum){
    if(tree==NULL) return 0;
    if(tree->left==NULL && tree->right==NULL) return sum==tree->item;
    return hasPathSum(tree->left, sum-tree->item) || hasPathSum(tree->right,sum-tree->item);
}
/*
 public class Solution {
 public boolean hasPathSum(TreeNode root, int sum) {
 if(root == null) return false;
 
 if(root.left == null && root.right == null) return sum == root.val;
 
 return hasPathSum(root.left, sum - root.val) || hasPathSum(root.right, sum - root.val);
 }
 }
Treelink left=tree->left;
 Treelink right=tree->right;
 while(left!=NULL){
 left=left->left;
 }
 
 Treelink prev=tree;
 
 if(curr->left==NULL && curr->right==NULL) return tree;
 else{
 mirror(prev->left);
 mirror(curr->left);
 
 //mirror(curr->right);
 
 }
 }
 
 {*/

/*void levelOrderTraversal(Treelink tree){
 
    Queue q = newQueue();
    Treelink curr= NULL;
    if(tree != NULL){
        QueueJoin(q,tree);
        
        while(!QueueIsEmpty(q)){
            curr = QueueLeave(q);
            printf("%d ", curr->item);
            
            if(curr->left != NULL){
                QueueJoin(q,curr->left);
            }
            if(curr->right != NULL){
                QueueJoin(q,curr->right);
            }
        }
    }
    
    dropQueue(q);
    
}
//Same as recursive Preorder
void mysteryIterativeTraversal(Treelink tree){
    
    Stack s = newStack();
    if(tree != NULL){
        StackPush(s,tree);
        while(!StackIsEmpty(s)){
            Treelink curr = StackPop(s);
            printf("%d ", curr->item);
            if(curr->right != NULL){
                StackPush(s,curr->right);
            }
            if(curr->left != NULL){
                StackPush(s,curr->left);
            }
        }
    }
    dropStack(s);
    
}
*/
//Assume t1 is the left subtree and t2 the right subtree

static Treelink join(Treelink t1, Treelink t2){
    if(t1 == NULL && t2 == NULL){
        return NULL;
    } else if(t1 == NULL){
        return t2;
    } else if(t2 == NULL){
        return t1;
    } else {
        Treelink curr = t2;
        Treelink prev = NULL;
        while(curr->left != NULL){
            prev = curr;
            curr = curr->left;
        }
        if(prev != NULL){
            prev->left = curr->right;
            curr->right = t2;
        }
        curr->left = t1;
        
        return curr;
    }
}

Treelink delete(Treelink tree, TreeItem item){
    if(tree == NULL){
        //I did not find it so I could not delete it
        return tree;
    } else if ( item < tree->item){
        //Try the left side
        tree->left = delete(tree->left,item);
    } else if (item > tree->item){
        //Try the right side
        tree->right = delete(tree->right,item);
    } else {
        //I found it and I need to delete it
        Treelink leftsubtree = tree->left;
        Treelink rightsubtree = tree->right;
        free(tree);
        return join(leftsubtree,rightsubtree);
    }
    return tree;
}

static void doShowBSTree(Treelink t, int level)
{
    int i;
    if (t == NULL) return;
    doShowBSTree(t->right, level+1);
    for (i = 0; i < level; i++) printf("   ");
    
    printf("%d\n", t->item);
    doShowBSTree(t->left, level+1);
}

void showBSTree(Treelink t)
{
    doShowBSTree(t, 0);
}


//PRACTICE QUESTIONS
//Some of these questions would only
//be doable assuming the tree has int items.
int sumEven(Treelink tree){
    //Treelink curr=tree;
    int sum=0;
    if(tree==NULL) return 0;
    else{
        if(tree->item%2==0) return sum=tree->item+sumEven(tree->left)+sumEven(tree->right);
        else return sum=sumEven(tree->left)+sumEven(tree->right);
    }
     //sum+=tree->item;
    
    return -1;
}


TreeItem getSmallest(Treelink tree){
    if(tree==NULL) return -1;
    if(tree->left!=NULL) return getSmallest(tree->left);
    return tree->item;
    
}

//An internal node has at least one non-null child
int numInternalNodes(Treelink tree){
    if(tree==NULL) return 0;
    if(tree->left!=NULL || tree->right!=NULL) {
        return 1+numInternalNodes(tree->left)+numInternalNodes(tree->right);
    }else{
        return 0;
    }
}


//Does a path from the root to an external node(in this case an external node can be considered to have at least one null child)
//have the given sum?
//0 false
//1 true
/*
 //Double tree
 //
 //     2
 //   /   \
 //  1     3
 //
 // would become
 //        2
 //      /  \
 //     2    3
 //    /    /
 //   1    3
 //  /
 // 1
 //
 */
void doubleTree(Treelink tree){
    if(tree==NULL) return;
    Treelink new=createNode(tree->item);
    Treelink oldL=tree->left;
    tree->left=new;
    new->left=oldL;
    doubleTree(oldL);
    doubleTree(tree->right);
}
void doubleTree(Treelink tree);

//Delete nodes with items < min  or > max

/*Treelink trimTree(Treelink tree, int min, int max){
    if(tree==NULL) return NULL;
    tree->left=trimTree(tree,min,max);
    tree->right=trimTree(tree,min,max);
    if(tree->item >= min && tree->item <=max){
        return tree;
    }
    Treelink newTree;
    if(tree->item<min){
        newTree=tree->right;
    }else{
        newTree=tree->left;
    }
    free(tree);
    return newTree;
}
*/
Treelink trimTree(Treelink tree, int min, int max){
    if(tree == NULL) return NULL;
    tree->left = trimTree(tree->left,min,max);//tree left hand side
    tree->right = trimTree(tree->right,min,max);
    if(tree->item >= min && tree->item <= max){
        return tree;
    }
    Treelink newTree;
    if(tree->item < min){
        newTree = tree->right;
    } else {
        newTree = tree->left;
    }
    free(tree);
    return newTree;
}





Treelink partition(Treelink t, int i)
{
    if (t == NULL) return NULL;
    assert(0 <= i && i < size(t));
    int n = size(t->left);
    if (i < n) {
        t->left = partition(t->left, i);
        t = rotateR(t);
    }
    if (i > n) {
        t->right = partition(t->right, i-n-1);
        t = rotateL(t);
    }
    return t;
}


Treelink rotateR(Treelink n1)
{
    if (n1 == NULL) return n1;
    Treelink n2 = n1->left;
    if (n2 == NULL) return n1;
    n1->left = n2->right;
    n2->right = n1;
    return n2;
}
// rotate Tree left around node
Treelink rotateL(Treelink n2)
{
    if (n2 == NULL) return n2;
    Treelink n1 = n2->right;
    if (n1 == NULL) return n2;
    n2->right = n1->left;
    n1->left = n2;
    return n1;
}



/*Treelink insertDegenerate(Treelink tree,TreeItem item){
    Treelink curr = tree;
    Treelink newNode = createNode(item);
    Treelink oldUp=NULL;
    if(curr==NULL){
        if(oldUp==NULL) return newNode;
        else{
            oldUp->left=newNode;
            return tree;
        }
    }if(curr->item>item){
        oldUp=curr;
        return ;
    }
    if(curr->item<item){
        Treelink new=createNode(item);
        new->left=curr;
        if(oldUp!=NULL) oldUp->left=new;
        return tree;
    }
    else{
        return NULL;
    }
}
*/


//struct node {
//    Item item;
//    link next;
//};

Treelink insertDegenerate (Treelink tree, TreeItem item) {
    if(tree == NULL){
        Treelink newNode = createNode(item);
        return newNode;
    } else {
        if(item <= tree->item){
            tree->left = insertDegenerate(tree->left, item);
        }
        else{
            Treelink newNode = createNode(item);
            newNode->left=tree;
            tree=newNode;
        }
    }
    return tree;
}



void map(Treelink t,int (*f)(int)){
    if(t==NULL) return;
    else{
        t->item=(*f)(t->item);//返回类型
        map(t->left,f);
        map(t->right,f);
        return;
    }
}


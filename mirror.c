/*
The most impressive magic trick at CSE is when you take a BST and produce an exact mirrored copy of it.
Of course being a first year is hard and you would like to make more friends, thus you resort to learning the magic trick.
We all know that it is just smoke and mirrors so we will use our programming talent.

TASK 
Write a program that given a tree modifies it into a mirror of
the given tree
    4                           4
   / \                         / \
  2   5      ===Shazzam!=>    5   2
 / \                             / \
1   3                           3   1
*/
#include <stdio.h>
#include <stdlib.h>
 
/* A binary tree node has data, pointer to left child 
   and a pointer to right child */
struct node 
{
    int data;
    struct node* left;
    struct node* right;
};
 
/* Helper function that allocates a new node with the
   given data and NULL left and right pointers. */
struct node* newNode(int data)
 
{
  struct node* node = (struct node*)
                       malloc(sizeof(struct node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
   
  return(node);
}
 
 
void mirror(struct node* node){
 //WRITE THIS FUNCTION
} 
 
 
/* Helper function to test mirror(). Given a binary
   search tree, print out its data elements in 
   increasing sorted order.*/
void inOrder(struct node* node) 
{
  if (node == NULL) 
    return;
   
  inOrder(node->left);
  printf("%d ", node->data);
  inOrder(node->right);
}  
 
struct node * insertNode(struct node * root, int val){
  if(root == NULL){
    return newNode(val);
  }
  if(val < root->data){
    root->left = insertNode(root->left, val);
  }else if(val >root->data){
    root->right = insertNode(root->right, val);
  }
  return root;
}
 
/* Driver program to test mirror() */
int main(){ 
  struct node *root = NULL;
  root = insertNode(root, 10);
  insertNode(root, 12);
  insertNode(root, 13);
  insertNode(root, 41);
  insertNode(root, 115);
   
  /* Print inorder traversal of the input tree */
  printf("\nInorder tree: ");
  inOrder(root);
  /* Convert tree to its mirror */
  mirror(root);
  printf("\nShazzam!"); 
  /* Print inorder traversal of the mirror tree */
  printf("\nYour output: ");  
  inOrder(root);
  printf("\nShould be : 115 41 13 12 10\n");
  
  struct node *root1 = NULL;
  root1 = insertNode(root1, 4);
  insertNode(root1, 2);
  insertNode(root1, 5);
  insertNode(root1, 1);
  insertNode(root1, 3);
   
  printf("\nInorder tree: ");
  inOrder(root1);
  mirror(root1); 
  printf("\nShazzam!"); 
  printf("\nYour output: ");   
  inOrder(root1);
  printf("\nShould be : 5 4 3 2 1\n");

  struct node *root2 = NULL;
  printf("\nInorder tree: ");
  inOrder(root2);
  mirror(root2); 
  printf("\nShazzam!"); 
  printf("\nYour output: "); 
  inOrder(root2);
  printf("\nShould be : \n");
  return 0;  
}
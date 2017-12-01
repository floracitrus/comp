/*
Hello agent1927, we are so glad to see you. The time couldn't been better as we have been infiltrated by russian spies.
This is already an embarrassment but moreover they have swapped all the room numbers in the building. This is so confusing 
and very frustraing. But our scientists have discovered a pattern. If we make a list of all the rooms we can see that the numbers are swapped pairwise.
We would like to restore order and you must help us! 
TASK:
Given a singly linked list, write a function to swap elements pairwise. 
For example, if the linked list is 1->2->3->4->5 then the function should change it to 2->1->4->3->5,
 and if the linked list is 1->2->3->4->5->6 then the function should change it to 2->1->4->3->6->5. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
/* A linked list node */
struct node{
    int data;
    struct node *next;
};
 
 
/* Function to pairwise swap elements of a linked list */
void pairWiseSwap(struct node *head){
    //IMPLEMENT THIS FUNCTION
}
 
 
/* Function to add a node at the begining of Linked List */
void push(struct node** head_ref, int new_data){
    /* allocate node */
    struct node* new_node =
              (struct node*) malloc(sizeof(struct node));
  
    /* put in the data  */
    new_node->data  = new_data;
 
    /* link the old list off the new node */
    new_node->next = (*head_ref);
 
    /* move the head to point to the new node */
    (*head_ref)    = new_node;
}
 
/* Function to print nodes in a given linked list */
void printList(struct node *node){
    while (node != NULL)
    {
        printf("%d ", node->data);
       node = node->next;
    }
}

void check(struct node *head, int *output, int size);

/* Driver program to test above function */
int main(){

    struct node *l0 = NULL;
    push(&l0, 0);
    pairWiseSwap(l0);
    assert(l0->data == 0);
    printf("Test 1 passed\n");
    struct node *l1 = NULL;
    /* The constructed linked list is:
     1->2->3->4->5 */
    push(&l1, 5);
    push(&l1, 4);
    push(&l1, 3);
    push(&l1, 2);
    push(&l1, 1);
    pairWiseSwap(l1);
    /*List after swap be 2->1->4->3->5*/ 
    int out[5] = {2,1,4,3,5};
    check(l1, out, 5);
    printf("Test 2 passed\n");
     /* The constructed linked list is:
     1->2->3->4->5->6 */
    struct node *l2 = NULL;
    push(&l2, 6);
    push(&l2, 5);
    push(&l2, 4);
    push(&l2, 3);
    push(&l2, 2);
    push(&l2, 1);
    pairWiseSwap(l2);
    /*List after swap 2->1->4->3->6->5*/
    int output[6] = {2,1,4,3,6,5};
    check(l2, output, 6);
    printf("Test 3 passed\n");
    struct node *l3 = NULL;
    pairWiseSwap(l3);
    assert(l3 == NULL);
    printf("Test 4 passed\n");
    printf("All tests passed. Congrats!\n");

    return 0;
}
void check(struct node *head, int *output, int size){
    
    for(int i = 0; i < size; i++){
        if(head == NULL){
            printf("List is broken. I am sorry, comrade, but you are going to Siberia\n");
            exit(1);
        }
        assert(head->data == output[i]);
        head = head->next;
    }
}
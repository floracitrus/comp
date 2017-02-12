//
//  main.c
//  就是test一下delete啦
//
//  Created by Flora Li on 29/12/16.
//  Copyright © 2016 Flora Li. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include "BST.h"
#include <assert.h>

//To compile please type
//gcc -Wall -Werror -O -o testBST2 BST.c testBST2.c Stack.c
//To run please type
//./testBST2

void printStuff(Treelink tree);


//Need to change type of TreeItem to char
int main(int argc, char * argv[]){
    Treelink t1 = createTree();
    //assert(size(t1) == 0);
    t1 = insertIterative(t1,5);
    t1 = insertIterative(t1,3);
    t1 = insertIterative(t1,4);
    t1 = insertIterative(t1,8);
    //t1 = insertIterative(t1,7);
    //t1 = insertIterative(t1,10);
    //t1 = insertIterative(t1,9);
    //t1 = insertIterative(t1,11);
    //t1 = insertIterative(t1,12);
    //t1 =insertIterative(t1, 1);
    mirror(t1);
    //               5
    //            3      8
    //            \
    //             4   7   10
    //                    9  11
    
    int num=hasPathSum(t1, 13);
    printf("true or false? %d\n",num);
    t1=trimTree(t1, 3, 10);

    
    
    
    Treelink t2=createTree();
    t2=insertIterative(t2, 10);
    //t2=insertDegenerate(t2,10);
    t2=insertDegenerate(t2,5);
    t2=insertDegenerate(t2,15);
    t2=insertDegenerate(t2,3);
    t2=insertDegenerate(t2,16);
    t2=insertDegenerate(t2,13);
    t2=insertDegenerate(t2,6);
    t2=insertDegenerate(t2, 17);
    
    
    
        printStuff(t2);
    int a=getSmallest(t1);
    printf("the smallest is %d",a);
    t1 = delete(t1,8);
    printf("size of that is %d \n",size(t1));
    //t1 = delete(t1,7);
    //t1 = delete(t1,3);
    
    //printStuff(t1);
    
    destroyTree(t1);
    
    return 0;
}


void printStuff(Treelink tree){
    
    
    printf("Pre order traversal: ");
    preorderTraversal(tree);
    
    printf("\n");
    
}

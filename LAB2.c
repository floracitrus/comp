/*Task 1: Stack ADT Array Implementation with Bounds Checking - 1 mark

The array based stack ADT implementation we developed in lectures, Had some serious shortcomings.

Pushing an item onto the stack when the maximum number of items has been reached, or popping from the stack when the stack is empty, leads to out of bounds array access. This can cause other program variables to be unintentionally overwritten and/or may result in apparently random crashes. It is good programming practice to make ADT implementations robust against out-of-bounds errors and similar problems.
The file stackArray.c, provided for this week's lab, implements the first class Stack ADT defined in stack.h. This overcomes the first limitation of the stack we implemented in lectures and allows a client program to create as many stacks as they would like. However the stackArray.c still has some problems when pushing or popping a full or empty stack. You need to modify the implementation in stackArray.c to provide the following behaviour:

When an attempt is made to push an item onto a stack that is already full, the array is resized to accomodate the extra element. Make sure the stack is only resized when it is full and make the resized array be 2 times bigger.
It prints the message "stack underflow" when an attempt is made to pop from an empty stack and calls the function abort to terminate the program. Also when the size of the stack drops below 1/4 of the size of the array, the array size should be resized to half of its size. However the array size should never dop below its original starting size.
Hint: Look at the C function realloc. (Note: this should ONLY be used to resize memory that has been malloced. Thus if you had declared you array like: int array[100]; You could NOT use realloc to resize it).

While you are developing you implementation, add some tests to the whiteBoxTests function in arrayStack.c. This should contain unit tests that have access to the internal structure of the ADT. These tests should be able to make sure the array is resized appropriately, as well as testing the rest of the stack functionality.

Add test cases to the testStack.c program, that would have triggered the out of bounds conditions to test that your code works properly. Be brutal with your tests! Also check that popping an empty stack generates the appropriate error messages. Note that the tests you create in testStack.c should be black box tests and can only only use the typedefs and functions that are declared in the .h interface.
*/
//answer
void push (Stack stack, Item item){
    assert(stack != NULL);
    if(stack->top == stack->maxSize){         
        stack->items = realloc(stack->items,stack->maxSize*2*sizeof(Item));
        assert(stack->items != NULL);
        stack->maxSize = stack->maxSize*2;
    }
    stack->items[stack->top++] = item;
}

Item pop (Stack stack){   
    assert(stack != NULL);
    if(stack->top == 0){
        fprintf(stderr,"stack underflow");
        abort();
    }
    stack->top--;
    Item item = stack->items[stack->top];
    if(stack->top <= stack->maxSize/4.0  && stack->maxSize/2.0 >= DEFAULT_SIZE){
        stack->items = realloc(stack->items,(stack->maxSize/2.0)*sizeof(Item));
        assert(stack->items != NULL);   
        stack->maxSize = stack->maxSize/2.0;
    }
    return item;
}

//Ex2
void putQueue (Queue q, Item item){
    assert(q != NULL);
    link n = createNode(item);
    if(q->tail != NULL){
       q->tail->next = n; 
    } else {
       q->head = n; 
    }
    q->tail = n;
    q->size++;
}
    
Item getQueue (Queue q){
    assert(q != NULL);
    if(q->head == NULL){
        fprintf(stderr,"queue underflow\n");
        abort();
    }
    Item item = q->head->item;
    link delNode = q->head; 
    q->head = q->head->next;
    if(delNode == q->tail){
        q->tail = NULL;
    }
    free(delNode);
    q->size--;  
    return item;
}


void queueWhiteBoxTests(void){
    printf("White box tests: \n");
    int i;
    Queue q = createQueue();
    printf("White Box Tests - linked list implementation\n");
    printf("Test 1: Create a new Queue\n");
    assert(q != NULL);
    assert(q->head == NULL);
    assert(q->size == 0);  
    printf("Passed\n");   
        
    printf("Test 2: putQueue\n");  
    for(i=0;i<100000;i++){
        putQueue(q,i);
        assert(q->size = i+1);
        assert(q->head->item == 0);
        assert(q->tail->item == i);
    }
    printf("Passed\n");
    printf("Test 3: getQueue\n");
    for(i=0;i<100000;i++){
        Item item = getQueue(q);
        assert(i == item);
        assert(q->size == 99999 - i);
    }
    assert(q->head == NULL);
    assert(q->tail == NULL);
    printf("Passed\n");

    printf("Test 4: Destroy queue\n");
    destroyQueue(q);
    printf("Passed\n");    
}




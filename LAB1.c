// Create a circular list with the number of nodes specified
link create_circular_list(int num_nodes) {
    
    link start, current,new;
    int pos;
    current = malloc(sizeof(link));
    
    if (current!=NULL) {
        current->data = 1;
        current->next = current;
        start=current;
        new=current;
    }
    for (pos=2; pos<=num_nodes; pos++){
        new = malloc(sizeof(link));
        new->data=pos;
        new->next=start;
        current->next=new;
        current=new;
    }
    return start;
    
}

void print_nodes(link t){
    int i=1;
    link start=t; 
    printf("Nodes are: [ %d ",t->data);
    t=t->next;
    while (t!=start){
      printf("%d ",t->data);
      i++;
      t=t->next;
    }
    printf("]\n");
}

//Write a function

//dlink doublify (link ls)
//which, given a linked list, creates a new doubly linked list with the same items as elements. You might want to write a printDList function to test it.



dlink doublify (link list) {
    dlink head = NULL;
    dlink tail = NULL;
    link tmp;

    for(tmp = list; tmp != NULL; tmp = tmp->next){
        dlink newNode = malloc(sizeof(dnode));
        newNode->item = tmp->item;
        newNode->next = NULL;
        newNode->prev = tail;
        if(head == NULL){
           head = newNode;
        } else {
           tail->next = newNode;
        }
        tail = newNode;
     }
     return head;
}
/*another method
 dlink doublify (link l) {
  dlink t,
  new = NULL,
  nextPrev = NULL;
  dlink *dlinkPtr = &new;

  while (l != NULL) {
    t = (dlink) malloc (sizeof *t);
    t->item = l->item;
    t->prev = nextPrev;
    t->next = NULL;
    nextPrev = t;
    *dlinkPtr = t;
    dlinkPtr = &(t->next);
    l = l->next;
  }
  return new;
 }
 
 */

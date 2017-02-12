link selectionSort(link list){
  link sorted = NULL;
  link curr = NULL;
  link prev = NULL;
  link max = NULL;
  link maxPrev = NULL;
  
  while(list!=NULL){
    prev = NULL;
    maxPrev = NULL;
    max = list;
    for(Curr = list; curr!=NULL;curr=curr->next){
      if(curr->item > max->item){
        max=curr;
        maxPrev = prev;
      }
      prev = curr;
    }
    if(maxPrev!=NULL){
      maxPrev->next = max->next;//eliminate the max and append afterwards
    }else{
      list = max->next;
    }
    max->next = sorted;
    sorted = max;
  }
  return sorted;
}

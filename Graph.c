Graph GRAPHcopy(Graph g){
  assert(g!= NULL);
  int i;
  Graph newGraph = malloc(sizeof(*newGraph));
  newGraph->V = g->V;
  newGraph->E = g->E;
  newGraph->adj = malloc(newGraph->V * sizeof(vlink));
  for(i = 0; i < g->V; i++){
      vlink newListStart = NULL;
      vlink newListEnd = NULL;
      vlink curr = g->adj[i];
      while(curr != NULL){
          vlink newNode = malloc(sizeof(*newNode));
          newNode->v = curr->v;
          newNode->next = NULL;
          if(newListStart == NULL){
               newListStart = newNode;
          } else {
               newListEnd->next = newNode;
          }
          newListEnd = newNode;
          curr = curr->next;
      }
      newGraph->adj[i] = newListStart;
  }
  return newGraph;
}
void GRAPHdestroy (Graph g) {
    assert(g != NULL);
    int i;
    //First free all linked lists
    for(i = 0; i < g->V; i++){
        vlink curr = g->adj[i];
        vlink prev = NULL;
        while(curr != NULL){
            prev = curr;
            curr = curr->next;
            free(prev);
        }
    }
    //Free array
    free(g->adj);
    //Free the graph struct
    free(g);
}
 int GRAPHdegree(Graph g, Vertex v){
    assert(g != NULL);
    assert(v >= 0  &&v < g->V);
    int degree = 0;
    vlink curr = g->adj[v];
    while(curr != NULL){
        degree++;
        curr = curr->next;
    }
    return degree;
}

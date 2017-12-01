/*
Mrs Barnabie likes to collect maps, she has hundreds of those and her obsession is borderline disturbing.
The only thing Mrs Barnabie is obsessed even more is russian cars. (We all know that they are the best.)
Russian cars are really expensive, and Mrs Barnabie is an old lady and has no money.
But to her joy she finds out that the museum of cartography is willing to buy old maps for a lot pf money(just enough for a LADA!).
However, the museum only wants special maps, those that contains treephs.
Treephs are graphs that are actually trees. Note that the rules of trees apply(think edge cases).
Can you help Mrs Barnabie find out all the treeph maps??

TASK: 
Basic: Given undirected graph find out if it is actually a tree. 

Challenge: A forest also counts.

*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

typedef struct GraphRep *Graph;
// graph representation (adjacency matrix)
typedef struct GraphRep {
	int    nV;    // #vertices
	int    nE;    // #edges
	int  **edges; // matrix of weights (0 == no edge)
} GraphRep;

// check validity of int
int validV(Graph g, int v)
{
	return (g != NULL && v >= 0 && v < g->nV);
}

// - sets (v,w) and (w,v)
void insertEdge(Graph g, int v, int w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] == 0) {
		g->edges[v][w] = 1;
		g->edges[w][v] = 1;
		g->nE++;
	}
}

// remove an Edge
// - unsets (v,w) and (w,v)
void removeEdge(Graph g, int v, int w)
{
	assert(g != NULL && validV(g,v) && validV(g,w));
	if (g->edges[v][w] != 0) {
		g->edges[v][w] = 0;
		g->edges[w][v] = 0;
		g->nE--;
	}
}

// create an empty graph
Graph newGraph(int nV)
{
	assert(nV > 0);
	Graph g = malloc(sizeof(GraphRep));
	g->nV = nV;
	g->edges = malloc(sizeof(int *) * nV);
	for(int i = 0; i < nV; i++){
		g->edges[i] = malloc(sizeof(int) * nV);
	}
	for(int i = 0; i < nV; i++){
		for(int j = 0; j < nV; j++){
			g->edges[i][j] = 0;
		}
	}
	return g; 
}
void dropGraph(Graph g){
	if(g == NULL) return;
	for(int i = 0; i < g->nV; i++){
		free(g->edges[i]);
	}
	free(g->edges);
	free(g);
}

// display graph, using names for vertices
void showGraph(Graph g)
{
	assert(g != NULL);
	int v, w;
	for (v = 0; v < g->nV; v++) {
		for (w = 0; w < g->nV; w++) {
			printf("%d ",g->edges[v][w]);
		}
		printf("\n");
	}
}


int isTreeph(Graph g){
	//Complete this function
}

int main(){
	// okay lets start easy
	Graph one = newGraph(3);
	insertEdge(one,0,1);
	insertEdge(one,0,2);
	int result = isTreeph(one);
	assert(result == 1);
	dropGraph(one);

	Graph two = newGraph(3);
	insertEdge(two,0,1);
	insertEdge(two,0,2);
	insertEdge(two,1,2);
	result = isTreeph(two);
	assert(result == 0);
	dropGraph(two);

	Graph three = newGraph(5);
	insertEdge(three,0,1);
	insertEdge(three,0,2);
	insertEdge(three,2,3);
	insertEdge(three,3,4);
	result = isTreeph(three);
	assert(result == 1);
	dropGraph(three);
	
	Graph four = newGraph(5);
	insertEdge(four,0,1);
	insertEdge(four,0,2);
	insertEdge(four,2,3);
	insertEdge(four,3,4);
	insertEdge(four,4,0);
	result = isTreeph(four);
	assert(result == 0);
	dropGraph(four);

	Graph five = NULL;
	result = isTreeph(five);
	assert(result == 1);
	dropGraph(five);
	printf("Congrats, you've passed all tests\n");

/*=================Challenge===================*/
	// What about a forest?
	Graph six = newGraph(8);
	insertEdge(six,0,1);
	insertEdge(six,0,2);
	insertEdge(six,0,3);
	insertEdge(six,6,5);
	insertEdge(six,6,4);
	insertEdge(six,6,7);
	result = isTreeph(six);
	assert(result == 1);
	dropGraph(six);

	six = newGraph(11); // got lazy changing all the names :/
	insertEdge(six,0,1);
	insertEdge(six,0,2);
	insertEdge(six,0,3);
	insertEdge(six,6,5);
	insertEdge(six,6,4);
	insertEdge(six,6,7);
	insertEdge(six,9,10);
	insertEdge(six,9,8);
	result = isTreeph(six);
	assert(result == 1);
	dropGraph(six);
	printf("Congrats, you passed the challenge challenge\n");
	
	return 0;
}




//
//  agent.c
//  Jan18
//
//  Created by Flora Li on 18/1/17.
//  Copyright © 2017 Flora Li. All rights reserved.
//
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include "Agent.h"

//#include <limit.h>

#define NONETARGET -1
#define TRUE 1
#define FALSE 0
#define INFINITY 9999
#define HASINFO 5 
#define NOINFO 6
//This struct stores information about an individual agent(detective or thief)
//You might want to add to this struct to store more information
struct agentRep{
    Vertex startLocation;
    Vertex currentLocation;
    int currentCycle;
    int maxCycles;
    int initialStamina; //max stamina
    int stamina;  //current stamina
    int strategy;
    Graph map;
    char *name;
    int target;//if it is detective then the target should be unavailable
    int *visit;
    Vertex *plan;
    int flag;//indicate take the rest times;
    int *dist;
    int firstEnterShortest;
    int * restStamina;
    int history;
    
};
int checkStamina(Agent agent);
//static int flag;//to indicate how many time it go to rest,reset that flag each agent;

//This creates one individual thief or detective
//You may need to add more to this
Agent initAgent(Vertex start, int maxCycles,int stamina,
            int strategy, Graph g, char * name,int target){
    if(start >= numV(g)){
        printf("Error starting vertex %d not valid\n",start);
        abort();
    }
    Agent agent = malloc(sizeof(struct agentRep));

    agent->startLocation = start;
    agent->currentLocation = start;
    agent->currentCycle = 0;
    agent->maxCycles = maxCycles;
    agent->initialStamina = stamina;
    agent->stamina = stamina;
    agent->strategy = strategy;
    agent->map = g;
    agent->name = strdup(name);
    agent->target = target;
    agent->visit = malloc(sizeof(int)*numV(g));
    agent->plan = malloc(sizeof(Vertex)*50);
    agent->flag =0;
    agent->dist = malloc(sizeof(int)*numV(g));
    agent->restStamina = malloc(sizeof(int)*numV(g));
    agent->history = NONETARGET; 
    int i;
    for(i=0; i< numV(g); i++){
        agent->visit[i] = 0;
    }
    for(i=0; i<50; i++){
        agent->plan[i] = -1;
    }
    for(i=0; i< numV(g); i++){
        agent->dist[i] = INFINITY;
    }
    for(i=0; i< numV(g); i++){
        agent->restStamina[i] = INFINITY;
    }

    return agent;
}


// Takes an array with all the possible edges and puts the ones the agent
// has enough stamina for into the filteredMoves array
// returns the number of filteredMoves
int filterEdges(Agent a,int numEdges,Edge *possibleMoves,Edge * filteredMoves){

    int numFiltered = 0;
    int i;
    for(i=0;i<numEdges;i++){
        if(possibleMoves[i].weight <= a->stamina){
            filteredMoves[numFiltered++] = possibleMoves[i];
        }
    }
    return numFiltered;
}

// Get a legal move. This should be a move that the agent has enough
// stamina to make and is a valid edge from the graph.
// You need to implement all other strategies.
Edge getNextMove(Agent agent,Graph g,int thiefLoc){
    //printf("check info is %d \n",checkInfo(g,getCurrentLocation(agent)));
    if(checkInfo(g,getCurrentLocation(agent))==HASINFO){
        //printf("I m changing strategy to shortest hh\n");
        agent->strategy=SHORTEST;
        agent->target=thiefLoc;
    }

    Edge nextMove;
    //Stationary strategy useful for debugging
    if(agent->strategy == STATIONARY){
        nextMove = mkEdge(agent->currentLocation,agent->currentLocation,0);
    
    }else if(agent->strategy == RANDOM){
        Edge * possibleMoves = malloc(numV(g) * sizeof(Edge));
        Edge * filteredMoves = malloc(numV(g) * sizeof(Edge));

        //Get all edges to adjacent vertices
        int numEdges = incidentEdges(g,agent->currentLocation,possibleMoves);

        //Filter out edges that the agent does not have enough stamina for
        int numFilteredEdges = filterEdges(agent,numEdges,possibleMoves,filteredMoves);
        if(numFilteredEdges!= 0){
            //nextMove is randomly chosen from the filteredEdges
            nextMove = filteredMoves[rand()%numFilteredEdges];
     }else{
            //the agent must stay in the same location
            nextMove = mkEdge(agent->currentLocation,agent->currentLocation,0);
            agent->stamina=agent->initialStamina;
        }
        free(filteredMoves);
        free(possibleMoves);

    }else if(agent->strategy == C_L_VISITED){
        Edge *possibleMoves = malloc(numV(g) * sizeof(Edge));
        Edge *filteredMoves = malloc(numV(g) * sizeof(Edge));
        
        int numEdges = incidentEdges(g,agent->currentLocation,possibleMoves);
        int numFilteredEdges = filterEdges(agent,numEdges,possibleMoves,filteredMoves);
        
        if(numFilteredEdges != 0){
        //int i;
            nextMove = cheapLeast(filteredMoves,numFilteredEdges,agent->visit);
        }else{
            //stay in a same spot for one round
            nextMove = mkEdge(agent->currentLocation,agent->currentLocation,0);
            agent->stamina = agent->initialStamina;
            //agent->visit[agent->currentLocation]++;
            //change that in to make NEXT move
        }
        free(filteredMoves);
        free(possibleMoves);

    }else if(agent->strategy == DFS){
        Edge *possibleMoves = malloc(numV(g) * sizeof(Edge));
        Edge *filteredMoves = malloc(numV(g) * sizeof(Edge));
        
        int numEdges = incidentEdges(g,agent->currentLocation,possibleMoves);
        int numFilteredEdges = filterEdges(agent,numEdges,possibleMoves,filteredMoves);
        
        if(numFilteredEdges!= 0){
            //first loop
            if(agent->currentCycle==0||checkFullVisit(agent)==1||agent->history == DFS){
                if(agent->history == DFS) agent->history = NONETARGET;
                agent->plan = dfSearch(agent->map,agent->currentLocation,agent->visit,agent->plan);//agent->initialStamina);
                nextMove=mkEdge(agent->plan[1],agent->plan[2],getWeight(agent->map,agent->plan[1],agent->plan[2]));
            //second and others
            }else{
               int i;
               for(i=0;agent->plan[i]==-2;i++){
               }
                if(agent->stamina < getWeight(agent->map,agent->plan[i],agent->plan[i+1])){
//                    printf("I am in here stamina not enough\n");
                    nextMove=mkEdge(agent->currentLocation,agent->currentLocation,0);
                    agent->stamina = agent->initialStamina;
                }
                else{
                    nextMove = mkEdge(agent->plan[i],agent->plan[i+1],getWeight(agent->map,agent->plan[i],agent->plan[i+1]));
                }
            }
        }
        else{
            //agent->flag++; should comeent above off
            nextMove = mkEdge(agent->currentLocation,agent->currentLocation,0);
            agent->stamina = agent->initialStamina;
        }
    }
    else if(agent->strategy == SHORTEST){
        
        Edge * possibleMoves = malloc(numV(g) * sizeof(Edge));
        Edge * filteredMoves = malloc(numV(g) * sizeof(Edge));

        int numEdges = incidentEdges(g,agent->currentLocation,possibleMoves);
        int numFilteredEdges = filterEdges(agent,numEdges,possibleMoves,filteredMoves);

        if(numFilteredEdges!= 0){
           // printf("thief location is %d \n",thiefLoc);
            //ffirst round
            if(checkInfo(agent->map,agent->currentLocation)==HASINFO){
                agent->plan = dijkstra(agent->map,agent->currentLocation,thiefLoc,agent->plan,agent->initialStamina);
                nextMove = mkEdge(agent->plan[0],agent->plan[1],getWeight(agent->map,agent->plan[0],agent->plan[1]));//debug
            }
            //following
            else{
                int i;
                for(i=0;agent->plan[i]==-2;i++){
                }
                if(agent->stamina < getWeight(agent->map,agent->plan[i],agent->plan[i+1])){
//                    printf("I am in here stamina not enough\n");
                    agent->flag++;
                    agent->dist[agent->currentLocation]++;
                    nextMove=mkEdge(agent->currentLocation,agent->currentLocation,0);
                    agent->stamina = agent->initialStamina;
                }
                else{
                    nextMove = mkEdge(agent->plan[i],agent->plan[i+1],getWeight(agent->map,agent->plan[i],agent->plan[i+1]));
                }
            }
        }else{
            agent->flag++;
            nextMove = mkEdge(agent->currentLocation,agent->currentLocation,0);
            agent->stamina = agent->initialStamina;
        }
    }
    else if(agent->strategy == THEIF){
        Edge * possibleMoves = malloc(numV(g) * sizeof(Edge));
        Edge * filteredMoves = malloc(numV(g) * sizeof(Edge));

        int numEdges = incidentEdges(g,agent->currentLocation,possibleMoves);
        int numFilteredEdges = filterEdges(agent,numEdges,possibleMoves,filteredMoves);

        if(numFilteredEdges!= 0){

                agent->plan = dijkstra(agent->map,agent->currentLocation,thiefLoc,agent->plan,agent->initialStamina);
                int i;
                for(i=0;agent->plan[i]==-2;i++){
                }
                if(agent->stamina < getWeight(agent->map,agent->plan[i],agent->plan[i+1])){
//                    printf("I am in here stamina not enough\n");
                    agent->flag++;
                    agent->dist[agent->currentLocation]++;
                    nextMove=mkEdge(agent->currentLocation,agent->currentLocation,0);
                    agent->stamina = agent->initialStamina;
                }
                else{
                   if(isadjacent(agent->d1loc,agent->plan[i])){
                        nextMove = highest()
                   nextMove = mkEdge(agent->plan[i],agent->plan[i+1],getWeight(agent->map,agent->plan[i],agent->plan[i+1]));
                }
                
        }else{
            agent->flag++;
            nextMove = mkEdge(agent->currentLocation,agent->currentLocation,0);
            agent->stamina = agent->initialStamina;
        }


    }
    else {
        printf("no such strategy in agent\n");
        abort();
    }
    return nextMove;
}

int checkStamina(Agent agent){
    if(agent->currentCycle!=0 && agent->stamina==agent->initialStamina){
       // printf("he just finish the rest; return 1 \n");
        return 1;
    }
    else{
        return 0;
    }
}



//Actually perform the move, by changing the agent's state
//This function needs to be updated to adjust the agent's stamina
void makeNextMove(Agent agent,Edge move){
    agent->currentCycle++;
    if(agent->stamina<move.weight){
        agent->stamina = agent->initialStamina;
        move.w=move.v;
    }else{
        agent->currentLocation = move.w;
        agent->stamina -= move.weight;
    }//consider here the dfs to change back
    agent->visit[move.v]++;
    //make visit is 1 or 0
    //mark the visited plan to be -2
    if(agent->currentCycle == 1 && agent->strategy == DFS){
        agent->plan[0]=-2;
        agent->plan[1]=-2;
    }
  
    else{
        //only mark to -2 when it not selfloop
        if(move.v!=move.w){
            int i;
            for(i=0;agent->plan[i]==-2;i++);
            agent->plan[i]=-2;
        }
    }
    if(strcmp(agent->name,"T")==0){
        agent->map = setThief(agent->map,getCurrentLocation(agent));
    }
    if(checkInfo(agent->map,move.w) == HASINFO){
        agent->target = getThief(agent->map);
        agent->history = agent->strategy;
    }
    //when it reach the target it change strategy back to cheapleast
    if(agent->currentLocation == agent->target){
        agent->strategy = agent->history;
    }
  
}


Vertex getCurrentLocation(Agent agent){
    return agent->currentLocation;
}


char * getName(Agent agent){
    return agent->name;
}


//Needs to be updated to print out vertex name information
//and * for cities with informants

void printAgent(Agent agent){
    if(strcmp(agent->name,"T")==0){
        if(getInfo(agent->map,agent->currentLocation)=='n'){
           printf("%s %d %s (%d)",agent->name,agent->stamina,getCityName(agent->map,agent->currentLocation),agent->currentLocation);
            if(getInfo(agent->map,agent->target)!='i'){
                printf(" %s (%d)\n",getCityName(agent->map,agent->target),agent->target);
            }
            else{
                printf(" %s (%d*)\n",getCityName(agent->map,agent->target),agent->target);
            }
        }
        else{
             printf("%s %d %s (%d*)",agent->name,agent->stamina,getCityName(agent->map,agent->currentLocation),agent->currentLocation);
             printf(" %s (%d)\n",getCityName(agent->map,agent->target),agent->target);
        }
    }
    else{
        if(getInfo(agent->map,agent->currentLocation)=='i'){
           // printf("infomant\n");//getCityName(agent->map,agent->currentLocation),
            printf("%s %d (%d*)",agent->name,agent->stamina, agent->currentLocation);
            printf(" %s (%d)\n",getCityName(agent->map,agent->target),agent->target);
        }
        else{
            printf("%s %d %s (%d)\n",agent->name,agent->stamina,getCityName(agent->map,agent->currentLocation),agent->currentLocation);
           // printf(" %s (%d)\n",getCityName(agent->map,agent->target),agent->target);
        }

    }
}

//You may need to update this to free any extra memory you use
void destroyAgent(Agent agent){
    //YOU MAY NEED TO MODIFY THIS
    free(agent->plan);
    free(agent->visit);
    free(agent->name);
    free(agent->dist);
    //free(agent->map);
    free(agent);
}

int getTarget(Agent agent){
    return agent->target;
}
int checkFullVisit(Agent agent){
    int i=0;
    for(i=0;i < numV(agent->map);i++){
        if(agent->visit[i]==0){
             return 0;
        }
    }
    return 1;
}
void changeStrategy(int *now,int* tar,int newTarget){
    *now=SHORTEST;
    *tar=newTarget;
}



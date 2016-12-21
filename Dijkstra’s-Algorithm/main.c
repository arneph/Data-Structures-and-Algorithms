//
//  main.c
//  Dijkstra’s Algorithm
//
//  Created by Arne Philipeit on 12/12/2016.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <math.h>
#include <time.h>


typedef struct{
    int n_nodes;
    char * nodeData;
    int * weights;
}Graph;


//Graph management:
Graph * graph_create(int n_nodes);
void graph_delete(Graph * g);

char graph_get_node_data(Graph * g, int node_index);
int graph_get_node_index_for_data(Graph * g, char data);
void graph_set_node_data(Graph * g, int node_index, char data);

int graph_get_weight(Graph * g, int node_index_a, int node_index_b);
void graph_set_weight(Graph * g, int node_index_a, int node_index_b, int weight);


//Depth first search:
bool graph_dfs(Graph * g, int start_index, char find_value);


//Dijkstra's algorithm:
bool graph_dijkstra(Graph * g, int startIndex, char find_value);


int main(int argc, const char * argv[]) {
    //Graph setup:
    Graph *graph = graph_create(12);
    
    for (int i = 0; i < 12; i++) {
        graph_set_node_data(graph, i, (char)(65 + i));
    }
    
    graph_set_weight(graph, 0,  1,  1); //A- 1-B
    
    graph_set_weight(graph, 1,  2,  2); //B- 2-C
    graph_set_weight(graph, 1,  3,  2); //B- 2-D
    
    graph_set_weight(graph, 2,  4,  3); //C- 3-E
    graph_set_weight(graph, 2,  5,  2); //C- 2-F
    
    graph_set_weight(graph, 3,  6,  2); //D- 2-G
    
    graph_set_weight(graph, 5,  7,  1); //F- 1-H
    graph_set_weight(graph, 5,  8,  2); //F- 2-I
    graph_set_weight(graph, 5,  9,  4); //F- 4-J
    
    graph_set_weight(graph, 6,  9,  1); //G- 1-J
    graph_set_weight(graph, 6, 10,  2); //G- 2-K
    graph_set_weight(graph, 6, 11,  3); //G- 3-L
    
    graph_set_weight(graph, 8, 10, 11); //I-11-K
    
    graph_set_weight(graph, 9, 11,  5); //J- 5-L
    
    
    //Depth first search:
    graph_dfs(graph, graph_get_node_index_for_data(graph, 'A'), 'X');
    graph_dfs(graph, graph_get_node_index_for_data(graph, 'K'), 'B');
    
    printf("\n");
    
    
    //Dijkstra's algorithm:
    graph_dijkstra(graph, graph_get_node_index_for_data(graph, 'A'), 'X');
    graph_dijkstra(graph, graph_get_node_index_for_data(graph, 'A'), 'J');
    
    
    //Clean up:
    graph_delete(graph);
    
    return 0;
}

Graph * graph_create(int n) {
    assert(n >= 1);
    
    Graph * g = (Graph *) malloc(sizeof(Graph));
    
    g->n_nodes = n;
    g->nodeData = (char *) malloc(n * sizeof(char));
    g->weights = (int *) malloc(n * n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        g->nodeData[i] = '\0';
    }
    
    for (int i = 0; i < n * n; i++) {
        g->weights[i] = -1;
    }
    
    return g;
}

void graph_delete(Graph * g) {
    assert(g != NULL);
    
    free(g->nodeData);
    free(g->weights);
    
    free(g);
}

char graph_get_node_data(Graph * g, int node_index) {
    assert(g != NULL);
    
    if (node_index < 0 || node_index >= g->n_nodes) {
        return '\0';
    }else{
        return g->nodeData[node_index];
    }
}

int graph_get_node_index_for_data(Graph * g, char data) {
    assert(g != NULL);
    
    for (int i = 0; i < g->n_nodes; i++) {
        if (g->nodeData[i] == data) {
            return i;
        }
    }
    
    return -1;
}

void graph_set_node_data(Graph * g, int node_index, char data) {
    assert(g != NULL);
    
    if (node_index >= 0 && node_index < g->n_nodes) {
        g->nodeData[node_index] = data;
    }
}

int graph_get_weight(Graph * g, int node_index_a, int node_index_b) {
    assert(g != NULL);
    
    if (node_index_a < 0 || node_index_a >= g->n_nodes ||
        node_index_b < 0 || node_index_b >= g->n_nodes) {
        return -1;
    }else if (node_index_a == node_index_b) {
        return 0;
    }else if (node_index_a < node_index_b) {
        return g->weights[node_index_a * g->n_nodes + node_index_b];
    }else{
        return g->weights[node_index_b * g->n_nodes + node_index_a];
    }
}

void graph_set_weight(Graph * g, int node_index_a, int node_index_b, int weight) {
    assert(g != NULL);
    
    if (weight < 0) {
        weight = -1;
    }
    
    if (node_index_a >= 0 && node_index_a < g->n_nodes &&
        node_index_b >= 0 && node_index_b < g->n_nodes &&
        node_index_a != node_index_b) {
        
        if (node_index_a < node_index_b) {
            g->weights[node_index_a * g->n_nodes + node_index_b] = weight;
        }else{
            g->weights[node_index_b * g->n_nodes + node_index_a] = weight;
        }
    }
}

//DFS is split into two functions:
//graph_dfs manages the common visited array
//graph_dfs_internal does the recursion
bool graph_dfs_internal(Graph * g, int start_index, char find_value, bool * visited);

bool graph_dfs(Graph * g, int start_index, char find_value) {
    assert(g != NULL);
    assert(start_index >= 0);
    assert(start_index < g->n_nodes);
    
    printf("DFS from '%c': ", g->nodeData[start_index]);
    
    bool * visited = (bool *) calloc(g->n_nodes, sizeof(bool));
    
    bool result = graph_dfs_internal(g, start_index, find_value, visited);
    
    free(visited);
    
    printf("\n");
    
    return result;
}

//If find_value is at start_index return
//Otherwise investigate neighbors that have not been visited yet
bool graph_dfs_internal(Graph * g, int start_index, char find_value, bool * visited) {
    visited[start_index] = true;
    
    printf("%c ", g->nodeData[start_index]);
    
    if (find_value == g->nodeData[start_index]) {
        printf("target found - HALT");
        
        return true;
        
    }else{
        for (int i = 0; i < g->n_nodes; i++) {
            if (visited[i]) continue;
            if (graph_get_weight(g, start_index, i) == -1) continue;
            
            bool result = graph_dfs_internal(g, i, find_value, visited);
            
            if (result) {
                return result;
            }
        }
        
        return false;
    }
}

//Dijkstra is split into two functions:
//graph_dijkstra manages the common arrays for permanent nodes, etc.
//graph_dijkstra_internal does the recursion
bool graph_dijkstra_internal(Graph * g, int start_index, char find_value, bool * permanent, int * parents, int * minDistances);

bool graph_dijkstra(Graph * g, int start_index, char find_value) {
    assert(g != NULL);
    assert(start_index >= 0);
    assert(start_index < g->n_nodes);
    
    printf("Dijkstra's path from '%c' length 0\n", g->nodeData[start_index]);
    
    bool * permanent = (bool *) calloc(sizeof(bool), g->n_nodes);
    int * parents = (int *) malloc(g->n_nodes * sizeof(int));
    int * minDistances = (int *) malloc(g->n_nodes * sizeof(int));
    
    for (int i = 0; i < g->n_nodes; i++) {
        parents[i] = -1;
        minDistances[i] = -1;
    }
    
    minDistances[start_index] = 0;
    
    bool result = graph_dijkstra_internal(g, start_index, find_value, permanent, parents, minDistances);
    
    free(permanent);
    free(parents);
    free(minDistances);
    
    printf("\n");
    
    return result;
}

//If find_value is at start_index return
//Otherwise update minimum distances to all not yet permanent neighbours:
//    If distance from start_index to neighbor is smaller than current minDistance to neighbour, change it
//Find node with smallest minDistance of not yet permanent nodes
//If found
//    Continue search at said node
//If not found
//    Return
bool graph_dijkstra_internal(Graph * g, int start_index, char find_value, bool * permanent, int * parents, int * minDistances) {
    permanent[start_index] = true;
    
    if (minDistances[start_index] > 0) {
        printf("%c length %i, parent %c\n", g->nodeData[start_index], minDistances[start_index], g->nodeData[parents[start_index]]);
    }
    
    //Check start_index:
    if (g->nodeData[start_index] == find_value) {
        printf("target found - HALT\n");
        
        return true;
    }
    
    //Update not yet permanent neighbours:
    for (int i = 0; i < g->n_nodes; i++) {
        if (permanent[i]) continue;
        if (graph_get_weight(g, start_index, i) == -1) continue;
        
        int distance = minDistances[start_index] + graph_get_weight(g, start_index, i);
        
        if (minDistances[i] == -1 ||
            minDistances[i] > distance) {
            minDistances[i] = distance;
            parents[i] = start_index;
        }
    }
    
    //Find node with smallest minDistance of not yet permanent nodes:
    int min = -1;
    int min_dist = -1;
    
    for (int i = 0; i < g->n_nodes; i++) {
        if (permanent[i]) continue;
        if (minDistances[i] == -1) continue;
        
        if (min_dist == -1 ||
            min_dist > minDistances[i]) {
            min_dist = minDistances[i];
            min = i;
        }
    }
    
    if (min == -1) {
        return false;
    }else{
        return graph_dijkstra_internal(g, min, find_value, permanent, parents, minDistances);
    }
}

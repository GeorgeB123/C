#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"
#include "graph.h"
#include "queue.h"

/*struct for the graph compnents*/
struct graphrec{
    int capacity;
    int **edges;
    struct vertexrec *vertices;
};

/*struct for each vertex*/
struct vertexrec{
    int finish;
    int predecessor;
    int distance;
    state_t state;
};

/*creates a new graph 
-capacity is the size of the graph
*/
graph graph_new(int capacity){
    int i = 0, j;
    graph g = emalloc(sizeof *g);
    g->capacity = capacity;
    g->edges = emalloc(g->capacity * sizeof g->edges[0]);
    for(i = 0; i < g->capacity; i++){
        g->edges[i] = emalloc(g->capacity * sizeof g->edges[0][0]);
        for(j=0; j<g->capacity;j++){
            g->edges[i][j]= 0;
        }
    }
    g->vertices = emalloc(g->capacity * sizeof (struct vertexrec));
    return g;
}

/*de-allocates the graph to free memory
-g is the graph
*/
graph graph_free(graph g){
    int i = 0;
    for(i = 0; i < g->capacity; i++){
        free(g->edges[i]);
        }
    free(g->edges);
    free(g->vertices);
    free(g);
    return g;
}



/*adds edges for a directed graph
u and v are the vertices the edge is between.
*/
void graph_add_directed(graph g,int u,int v){
    g->edges[u][v] = 1;
}
/*adds edges for a un-directed graph
u and v are the vertices the edge is between.
*/
void graph_add_undirected(graph g,int u,int v){
    g->edges[u][v] = 1;
    g->edges[v][u] = 1;
}

/*searches the graph using a breadth-first
search method.
*/
void graph_bfs(graph g, int source){
    int i, j, u;
    queue q = queue_new(g->capacity);
    for(i = 0; i < g->capacity; i++){
        g->vertices[i].state = UNVISITED;
        g->vertices[i].distance = -1;
        g->vertices[i].predecessor = -1;
    }
    g->vertices[source].state = VISITED_SELF;
    g->vertices[source].distance = 0;
    enqueue(q, source);
    while(!(queue_size(q) == 0)){
        u = dequeue(q);
        for(j = 0; j < g->capacity; j++){
            if(g->edges[u][j] == 1 && g->vertices[j].state == UNVISITED){
                g->vertices[j].state = VISITED_SELF;
                g->vertices[j].distance = 1 + g->vertices[u].distance;
                g->vertices[j].predecessor = u;
                enqueue(q, j);
            }
            g->vertices[u].state = VISITED_DESCENDANTS;
        }
    }
    queue_free(q);
}

/*prints out the graph g and its vertices
and edges.
*/
void graph_print(graph g){
    int i,j;
    printf("adjacency list:\n");
    for(i = 0; i < g->capacity;i++){
        printf("%d | ",i);
        for(j = 0;j < g->capacity; j++){
            if(g->edges[i][j] == 1){
                printf("%d, ", j);
            }
        }
        printf("\n");
    }
    printf("\nvertex distance pred\n");
    for(i=0;i<g->capacity;i++){
        printf("%d\t%d\t%d\n",i,g->vertices[i].distance,
        g->vertices[i].predecessor);
    }
}

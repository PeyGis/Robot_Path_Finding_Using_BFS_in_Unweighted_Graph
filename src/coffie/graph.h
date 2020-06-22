/* 
  Interface file

  Graph - adjacency list implementation based on code by Steven Skiena:

  Steven S. Skiena, "The Algorithm Design Manual", 2nd Edition, Springer, 2008.

  David Vernon
  19 March 2017

*/
 
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <ctype.h>

#define TRUE 1
#define FALSE 0

#define QUEUESIZE       10000

typedef int item_type;

typedef struct {
        item_type q[QUEUESIZE+1];       /* body of queue */
        int first;                      /* position of first element */
        int last;                       /* position of last element */
        int count;                      /* number of queue elements */
} queue;


/* Adjacency list representation of a graph of degree MAXV          */
/*                                                                  */
/* Directed edge (x, y) is represented by edgenode y in x’s         */
/* adjacency list. Vertices are numbered 1 .. MAXV                  */

#define MAXV 10000  /* maximum number of vertices */
#define MAX_N 100
#define MAX_M 100

//Original code
//typedef struct {
//   int y;                        /* adjacent vertex number          */
//   int weight;                   /* edge weight, if any             */
//   struct edgenode *next;        /* next edge in list               */
//} edgenode;

typedef struct edgenode *EDGENODE_PTR;

typedef struct edgenode {
   int y;                        /* adjacent vertex number          */
   int weight;                   /* edge weight, if any             */
   EDGENODE_PTR next;            /* next edge in list               */
} edgenode;

typedef struct {
        edgenode *edges[MAXV+1]; /* adjacency info: list of edges   */
        int degree[MAXV+1];      /* number of edges for each vertex */
        int nvertices;           /* number of vertices in graph     */
        int nedges;              /* number of edges in graph        */
        bool directed;           /* is the graph directed?          */
} graph;


void initialize_graph(graph *g, bool directed);

bool read_graph(graph *g, bool directed);
 
void insert_edge(graph *g, int x, int y, bool directed, int w);

void read_map(FILE *fp_in,   int map[][MAX_M], int map_dimension_x, int map_dimension_y);

void convert_map_values_to_characters(FILE *fp_out,   int map[][MAX_M], int map_dimension_x, int map_dimension_y);

int get_graph_vertex_number(int map_column_size, int cell_index_x, int cell_index_y);

void map_to_graph(graph *g, bool directed, int map[][MAX_M], int map_dimension_x, int map_dimension_y);

bool get_start_and_destination_coordinates(int map[][MAX_M], int map_dimension_x, int map_dimension_y, int *robot_x, int *robot_y, int *goal_x, int *goal_y); 

void reset_start_and_destination_coordinates(int *robot_x, int *robot_y, int *goal_x, int *goal_y); 

void mark_map(int map[][MAX_M], int map_dimension_x, int map_dimension_y, int v);

int convert_vertex_to_map_x_cordinates(int map_dimension_y, int vertex_number);

int convert_vertex_to_map_y_cordinates(int map_dimension_y, int vertex_number);

void print_graph(graph *g);

void initialize_search(graph *g);

void bfs(graph *g, int start);

void process_vertex_late(int v);

void process_vertex_early(int v);

void process_edge(int x, int y);

bool find_path(int start, int end, int parents[]);

bool find_path_modified(int start, int end, int parents[], int map[][MAX_M], int map_dimension_y);

void print_map(FILE *fp_out, int map[][MAX_M], int map_dimension_x, int map_dimension_y);

bool find_path(graph *g, int start, int end);

bool find_path_on_map(graph *g, int start, int end, int map[][MAX_M], int map_dimension_y);

void init_queue(queue *q);

void enqueue(queue *q, item_type x);

item_type dequeue(queue *q);

item_type headq(queue *q);

int empty_queue(queue *q);

void print_queue(queue *q);

void prompt_and_exit(int status);

void read_map_v2(FILE *fp_in,  int map_dimension_x, int map_dimension_y);
 
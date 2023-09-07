/*This file contains all the objects needed for the 
  string graph datastructure. This includes edges, 
   vertices, adjacency list, and the actual string graph*/

/*creates a graph structure */

/*creates an edge structure with weight for vertex*/
struct edge{
  int weight;

};

/*creates a vertex structure with a name, a linked list 
  of all vertices that are connected to the head vertex 
  by an edge, and the edge incoming*/
struct vertex{
  char *name;
  struct vertex *next;
  struct edge *incoming;

} ;

/*creates an adjacency list for each vertex with a vertex head
  and another vertex adjacency list*/
struct adjacency_list{
  struct vertex *head;
  struct adjacency_list *next;

};


/*creates graph structure with number of edges, vertices 
  and the first vertex of the graph */
typedef struct { 

  int edges;
  int vertices;
  struct adjacency_list* first_vertex;

} String_graph;


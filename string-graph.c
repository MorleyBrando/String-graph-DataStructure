/*This file uses the graph structure in string-graph-structure.h and creates 
  functions needed to use the graph. These functions allows the user to 
  initiliaze the graph, add vertices and edges, and get information on these 
  edges and vertices. The new functions added for project 8 allow us to remove
  certain vertices and edges as well delete the whole graph as a whole. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string-graph.h"

/* this function initializes the graph, given an empty graph */

void graph_init(String_graph *const graph) { 
  
  /* if statement makes sure the given graph is not NULL. 
     Inside the if statement the number of edges and vertices 
     are set to 0. The first vertex is set to NULL*/
  if(graph != NULL) {
    graph->edges = 0;
    graph->vertices = 0;
    graph->first_vertex = NULL;
  }
}

/*This function adds a vertex to the graph unless the graph given is NULL or 
  there is already a vertex with that name.*/

short add_vertex_to_graph(String_graph *const graph, const char new_vertex[]) { 
  
  /*the variables curr and prev are used to iterate through the graph while 
    the variable new_addition is the new vertex being added*/
  struct adjacency_list* prev = NULL, *curr = NULL;
  struct adjacency_list* new_addition = NULL;
  
  /*checks if graph given is NULL */
  if(graph == NULL || new_vertex == NULL) {
    return 0;
  }

  /*curr is set to first vertex*/
  curr = graph->first_vertex;
  
  /*this if statement checks if there is already a vertex in the graph. 
    If there is no vertices yet the first vertex will be the vertex 
    being added. */
  if(graph->first_vertex == NULL) {
    graph->first_vertex = malloc(sizeof(struct adjacency_list));
    graph->first_vertex->head = malloc(sizeof(struct vertex));
    graph->first_vertex->head->name  = malloc(strlen(new_vertex) + 1);
    strcpy(graph->first_vertex->head->name, new_vertex);
    graph->first_vertex->next = NULL;
    graph->first_vertex->head->next = NULL;
    graph->vertices++;
    return 1;
  } 

  /*this vertex checks if the vertex being added is the same as the first 
    one in the graph */
  if(strcmp(curr->head->name, new_vertex) == 0) {
    return 0;
  } 

  /* this while loop checks all the vertices in the graph. If there is a 
     vertex with the same name, nothing is done and 0 is returned. 
     Otherwise the while loop will just end */
  while(curr != NULL) {
    if(strcmp(curr->head->name, new_vertex) == 0) {
      return 0;
    }else { 
      prev = curr;
      curr = curr->next;
    }
  }
  
  /*the new vertex is added to the end of the linked list of vertices. */
  new_addition = malloc(sizeof(struct adjacency_list));
  new_addition->head = malloc(sizeof(struct vertex));
  new_addition->head->name  = malloc(strlen(new_vertex) + 1);
  strcpy(new_addition->head->name, new_vertex);
  prev->next = new_addition;
  new_addition->next = NULL;
  new_addition->head->next = NULL;
  graph->vertices++;

  return 1;

}

/*this function returns the number of vertices unless the graph given is NULL */
short vertex_count(const String_graph *const graph) {
  if(graph == NULL) {
    return 0;
  }
  return graph->vertices;
}

/*this function checks if there is a vertex with the name given in the graph */
short isa_vertex(const String_graph *const graph, const char name[]) {
  struct adjacency_list* curr;
  
  /*checks if graph given is NULL */
  if(graph == NULL || name == NULL) {
    return 0;
  }
  /*makes the variable curr equal to the first vertex */
  curr = graph->first_vertex;

  if(curr == NULL) {
    return 0;
  }

  /*checks if the first vertex has the same name */ 
  if(strcmp(curr->head->name, name) == 0) {
    return 1;
  }
  
  /*checks all vertices in the graph to check if there is a vertex with
    the same name*/
  while(curr != NULL) {
    if(strcmp(curr->head->name, name) == 0) {
      return 1;
    } else {
      curr = curr->next;
    }
  }

  return 0;
}

/*This function returns the list of vertices names in alphabetical order */
char **get_vertex_list(const String_graph *const graph) {
  char** vertex_list = malloc((graph->vertices + 1) * sizeof(char *));
  struct adjacency_list* curr;
  struct adjacency_list* compared;
  int count = 0, i;

  /*checks if graph given is NULL */
  if(graph == NULL) {
    return NULL;
  }
  
  compared = graph->first_vertex;
  
  /*takes a vertex and compares it with all the other vertices. If the vertex
    is less than another vertex, 1 is added to count, until it is done going 
    through the vertices. The original vertex will then be put into the spot 
    equal to the count integer */ 
  for(i = 1; i <= graph->vertices; i++) {
    count = 0;
    curr = graph->first_vertex;
    while(curr != NULL) {
      if(strcmp(compared->head->name, curr->head->name) > 0) {
	count++;
      }  
      curr = curr->next;
    }
    vertex_list[count] = malloc(strlen(compared->head->name) + 1);
    strcpy(vertex_list[count], compared->head->name);
    compared = compared->next;
  }

  /*adds a NULL to the end of the list */
  vertex_list[graph->vertices] = NULL;
  

  return vertex_list;
}

/*this function creates an edge with a weight from a vertex with the source 
  name to the dest vertex, unless weight is less than 0 or the graph given is 
  NULL. If the source and dest vertices haven't been created then they are 
  created. If the there is already an edge between the 2 vertices only the 
  weight is changed. */
short create_graph_edge(String_graph *const graph, const char source[],
                        const char dest[], int weight) { 
  struct adjacency_list* source_compared = NULL;
  struct vertex* dest_compared = NULL;
  struct vertex* prev = NULL;
  
  /*checks if weigh is less than 0 or graph is NULL */
  if(weight < 0 || graph == NULL || source == NULL || dest == NULL) {
    return 0;
  }
  
  /*checks if graph has source vertex, and adds one if it doesn't*/
  if(isa_vertex(graph, source) == 0) {
    add_vertex_to_graph(graph, source);
  }

  /*finds the source vertex and sets the variable source_compared to it*/
  source_compared = graph->first_vertex;
  while(strcmp(source_compared->head->name, source) != 0) {
    source_compared = source_compared->next; 
  }

  /*checks if graph has dest vertex, and adds one if it doesn't*/
  if(isa_vertex(graph, dest) == 0) {
    add_vertex_to_graph(graph, dest);
  }

  /*checks if source vertex has at least on edge, and if it doesnt it
    adds one */
  if(source_compared->head->next == NULL) {
    dest_compared = malloc(sizeof(struct vertex));
    source_compared->head->next = dest_compared;
    dest_compared->name = malloc(strlen(dest) + 1);
    strcpy(dest_compared->name, dest);
    dest_compared->incoming = malloc(sizeof(struct edge));
    dest_compared->incoming->weight = weight;
    dest_compared->next = NULL;
    graph->edges++;
    return 1;
  }

  /*goes through all edges the source vertex has and checks if there
    is one to dest. If there is the weight is change to the weight
    given. */
  dest_compared = source_compared->head->next;
  while(dest_compared != NULL) {
    if(strcmp(dest_compared->name, dest) == 0) {
      dest_compared->incoming->weight = weight;
      return 1;
    }
    prev = dest_compared;
    dest_compared = dest_compared->next;
  }

  /*creates an edge from source to dest*/
  dest_compared = malloc(sizeof(struct vertex));
  prev->next = dest_compared;
  dest_compared->name = malloc(strlen(dest) + 1);
  strcpy(dest_compared->name, dest);
  dest_compared->incoming = malloc(sizeof(struct edge));
  dest_compared->incoming->weight = weight;
  dest_compared->next = NULL;
  graph->edges++;
  return 1;

}


/*this function returns the weight of an edge from source to dest */
short get_graph_edge_weight(const String_graph *const graph,
                            const char source[], const char dest[]) { 

  struct adjacency_list* source_compared;
  struct vertex* dest_compared;

  /*returns -1 if parameters are NULL or if the dest and source vertices
    aren't in the graph*/
  if(isa_vertex(graph, source) == 0 || isa_vertex(graph, source) == 0 || 
     graph == NULL || source == NULL || dest == NULL) {
    return -1;
  }

  /*finds source vertex and sets source_compared variable to it*/
  source_compared = graph->first_vertex;
  while(strcmp(source_compared->head->name, source) != 0) {
    source_compared = source_compared->next;
  }

  /*goes through each of the source vertex's edges and finds dest. 
    if there is an edge then the weight is return, otherwise -1 is returned*/
  dest_compared = source_compared->head->next;
  while(dest_compared != NULL) {
    if(strcmp(dest_compared->name, dest) == 0) {
      return dest_compared->incoming->weight;
    }
    dest_compared = dest_compared->next;
  }

  return -1;
}

/*this function returns the number of edges a vertex has, unless the parameters
 given are NULL or the vertex is not in the graph*/  
short neighbor_count(const String_graph *const graph, const char vertex[]) {
  int count = 0;
  struct adjacency_list* curr;
  struct vertex* neighbors;

  /*checks if paramaters are NULL or vertex is in the graph*/
  if(isa_vertex(graph, vertex) == 0 || graph == NULL || vertex == NULL) {
    return -1;
  }
 

  /*goes through each vertex and finds original vertex */
  curr = graph->first_vertex;
  while(strcmp(curr->head->name, vertex) != 0) {
    curr = curr->next;
  }
  
  /*goes through all edges of vertex, and adds one to count everytime*/
  neighbors = curr->head->next;
  while(neighbors != NULL) {
    count++;
    neighbors = neighbors->next;
  }

  /*returns amount of neighbors*/
  return count;
}

/*this function frees all the dynamically allocated names in the list 
 given*/
void free_vertex_name_list(char **const names) {
  
  if(names != NULL) {
    int i = 0;

    /*this while loop goes through the list and frees the names */
    while(names[i] != NULL) {
      free(names[i]);
      i++;
    }
    free(names);
  }
}

/*this function returns a list of names that a vertex has an edge to */
char **get_neighbor_names(const String_graph *const graph, 
			  const char vertex[]) {
  char **neighbors;
  short num_neighbors;
  struct adjacency_list* temp;
  struct vertex* curr, *prev; 
  int i, count = 0;

  if(graph == NULL || vertex == NULL) {
    return NULL;
  }

  /*This if statement uses the function num_neighbors from above to see 
   how many edges this vertex has. If it doesn't have any num_neighbors 
  is -1 and therefore NULL is returned.*/
  num_neighbors = neighbor_count(graph, vertex);
  if(num_neighbors == -1) {
    return NULL;
  } 

  /*dynamically allocates list that is going to be returned.*/
  neighbors = malloc((num_neighbors + 1) * sizeof(char *));

  /*This while loop finds the original vertex we are looking for*/
  temp = graph->first_vertex;
  while(strcmp(temp->head->name , vertex) != 0) {
    temp = temp->next;
  }

  /*this for loop uses the number of neighbors that we got before to
   go through all the neighbors. The while loop takes one name and 
   compares it to each other name. The count checks how many names
   the first name is greater than according to the strcmp function. 
   Eventually the name gets put into the correct spot on the list.*/
  curr = temp->head->next;
  for(i = 0; i < num_neighbors; i++) {
    prev = temp->head->next;
    count = 0;
    while(prev != NULL) {
      if(strcmp(curr->name, prev->name) > 0){
	count++;
      } 
      prev = prev->next;
    }
    /*the name gets dynamically created and copied into the 
      spot. NULL is added at the end.*/
    neighbors[count] = malloc(strlen(curr->name) + 1);
    strcpy(neighbors[count], curr->name);
    curr = curr->next;
  }
  neighbors[num_neighbors] = NULL;

  return neighbors;
}

/*This function checks if there is an edge between two given vertices and removes it 
 if there is an the edge, it is removed. */
int remove_graph_edge(String_graph *const graph, const char source[], const char dest[]) {
  struct adjacency_list *find_source;
  struct vertex *curr, *prev;

  if(graph == NULL || source == NULL || dest == NULL) {
    return 0;
  }

  /*Checks to see if the vertices given are in the graph. Returns 0 if not*/
  if(isa_vertex(graph, source) == 0 || isa_vertex(graph, dest) == 0) {
    return 0;
  }

  /*checks to see if there is an edge between the 2 vertices, if not 0 is returned.*/
  if(get_graph_edge_weight(graph, source, dest) == -1) {
    return 0;
  }
    
  /*this while loop find the source vertex*/
  find_source = graph->first_vertex;
  while(strcmp(find_source->head->name, source) != 0) {
    find_source = find_source->next;
  }

  /*this if statement checks if to see if the first vertex in the linked list 
   is the destination vertex. If it is prev is set to the original source 
   vertex,which allows the linked list to stay completed when the first neighbor
   is freed. */
  curr = find_source->head->next;
  if(strcmp(curr->name, dest) == 0) {
    prev = find_source->head;
  }

  /*while loop goes through neighbors to find dest vertex. */
  while(strcmp(curr->name, dest) != 0) {
    prev = curr;
    curr = curr->next;
  }

  /*the linked list is restored and the vertex and all its variables are freed*/
  prev->next = curr->next;
  free(curr->incoming);
  free(curr->name);
  free(curr);

  graph->edges--;

  return 1;
}

/*This function removes a vertex from the graph along with all the edges that 
  are incoming and outgoing. */
int remove_vertex_from_graph(String_graph *const graph, const char vertex[]) {
  char **neighbors;
  int i = 0;
  struct adjacency_list *curr, *prev;

  if(graph == NULL || vertex == NULL) {
    return 0;
  }

  /*checks to see if the graph has the given vertex*/
  if(isa_vertex(graph, vertex) == 0) {
    return 0;
  }

  /*gets the names of the neighbors and removes the edge between them*/
  neighbors = get_neighbor_names(graph, vertex);
  while(neighbors[i] != NULL) {
    remove_graph_edge(graph, vertex, neighbors[i]);
    i++;
  }

  /*uses previous function to check all vertices and checks if there is a vertex
    between them and the vertex given. If there is, then it is removed. */
  curr = graph->first_vertex;
  while(curr != NULL) {
    remove_graph_edge(graph, curr->head->name, vertex);
    curr = curr->next;
  }

  /*checks to see if first vertex is the vertex we are looking for. If it is 
    then the graph first_vertex is changed to the next vertex. The while loop
    after finds the vertex*/
  curr = graph->first_vertex;
  if(strcmp(curr->head->name, vertex) == 0) {
    graph->first_vertex = curr->next;
  } else {
    while(strcmp(curr->head->name, vertex) != 0) {
      prev = curr;
      curr = curr->next;
    }
  
    prev->next = curr->next;
  }

  /*frees the neighbors list we used before, and the vertex we wanted.*/
  free_vertex_name_list(neighbors);
  free(curr->head->name);
  free(curr->head);
  free(curr);
  graph->vertices--;

  return 1;
}

/*This function removes the whole graph including all vertices and edges*/
void graph_delete(String_graph *const graph) {
  /*This while loop removes the first vertex until there is no more vertices*/
  while(graph->first_vertex != NULL) {
    remove_vertex_from_graph(graph, graph->first_vertex->head->name);
  }
}

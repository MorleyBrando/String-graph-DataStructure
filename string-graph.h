/*This file contains all the functions of the string-graph datastructure. */


#include "string-graph-datastructure.h"

void graph_init(String_graph *const graph);
short add_vertex_to_graph(String_graph *const graph, const char new_vertex[]);
short vertex_count(const String_graph *const graph);
short isa_vertex(const String_graph *const graph, const char name[]);
char **get_vertex_list(const String_graph *const graph);
short create_graph_edge(String_graph *const graph, const char source[],
                        const char dest[], int weight);
short get_graph_edge_weight(const String_graph *const graph,
                            const char source[], const char dest[]);
short neighbor_count(const String_graph *const graph, const char vertex[]);

void free_vertex_name_list(char **const names);
char **get_neighbor_names(const String_graph *const graph, const char vertex[]);
int remove_graph_edge(String_graph *const graph, const char source[],
                      const char dest[]);
int remove_vertex_from_graph(String_graph *const graph, const char vertex[]);
void graph_delete(String_graph *const graph);

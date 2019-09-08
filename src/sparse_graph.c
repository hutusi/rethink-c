/**
 * @file sparse_graph.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to sparse_graph.h
 * @date 2019-09-05
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "sparse_graph.h"
#include "def.h"
#include "dup.h"
#include "queue.h"

#include <stdlib.h>
#include <string.h>

struct _AdjacencyArc {
    int vertex;
    int weight;
    struct _AdjacencyArc *next;
};

struct _AdjacencyList {
    unsigned int out_degree;
    struct _AdjacencyArc *first_arc;
};

AdjacencyList *adjacency_list_new()
{
    AdjacencyList *list = (AdjacencyList *)malloc(sizeof(AdjacencyList));
    list->out_degree = 0;
    list->first_arc = NULL;
    return list;
}

void adjacency_list_free(AdjacencyList *list)
{
    AdjacencyArc *arc = list->first_arc;
    AdjacencyArc *pre_arc = NULL;
    while (arc != NULL) {
        pre_arc = arc;
        arc = arc->next;
        free(pre_arc);
    }

    free(list);
}

SparseGraph *sparse_graph_new(unsigned int num_vertex)
{
    SparseGraph *graph = arraylist_new(adjacency_list_free, num_vertex);
    for (int i = 0; i < num_vertex; ++i) {
        arraylist_append(graph, adjacency_list_new());
    }
    return graph;
}

void sparse_graph_free(SparseGraph *graph)
{
    arraylist_free(graph);
}

int sparse_graph_is_linked(SparseGraph *graph, int vertex1, int vertex2)
{
    AdjacencyList *list = (AdjacencyList *)graph->data[vertex1];
    if (list == NULL) {
        return 0;
    }

    AdjacencyArc *arc = list->first_arc;

    while (arc != NULL) {
        if (arc->vertex == vertex2) 
            return 1;
        arc = arc->next;
    }

    return 0;
}

AdjacencyArc *sparse_graph_new_arc(int vertex, int weight)
{
    AdjacencyArc *arc = (AdjacencyArc *)malloc(sizeof(AdjacencyArc));
    arc->vertex = vertex;
    arc->weight = weight;
    arc->next = NULL;
    return arc;
}

int sparse_graph_link(SparseGraph *graph, int vertex1, int vertex2)
{
    AdjacencyList *list = (AdjacencyList *)graph->data[vertex1];
    if (list == NULL) {
        return -1;
    }

    AdjacencyArc *arc = list->first_arc;
    AdjacencyArc *pre_arc = NULL;
    while (arc != NULL) {
        if (arc->vertex == vertex2) 
            return 1;
        pre_arc = arc;
        arc = arc->next;
    }

    AdjacencyArc *new_arc = sparse_graph_new_arc(vertex2, 1);
    if (pre_arc = NULL) {
        list->first_arc = new_arc;
    } else {
        pre_arc->next = new_arc;
    }
    ++(list->out_degree);

    return 0;
}

int *sparse_graph_topo_sort(SparseGraph *graph)
{
    int *sorted_vertexes = (int *)malloc(graph->length * sizeof(int));
    int *in_degrees = (int *)malloc(graph->length * sizeof(int));
    memset(in_degrees, 0, graph->length * sizeof(int));

    for (int i = 0; i < graph->length; ++i) {
        AdjacencyList *alist = (AdjacencyList *)graph->data[i];
        AdjacencyArc *arc = alist->first_arc;
        while (arc != NULL) {
            ++(in_degrees[arc->vertex]);
            arc = arc->next;
        }
    }

    Queue *queue = queue_new();
    for (int i = 0; i < graph->length; ++i) {
        if (in_degrees[i] == 0) {
            queue_push_tail(queue, intdup(i));
        }
    }

    int num = 0;
    while (!queue_is_empty(queue)) {
        int *v = (int *)queue_pop_head(queue);
        sorted_vertexes[num++] = *v;
        
        AdjacencyList *alist = (AdjacencyList *)graph->data[*v];
        AdjacencyArc *arc = alist->first_arc;
        while (arc != NULL) {
            --(in_degrees[arc->vertex]);
            arc = arc->next;
        }
        --(in_degrees[*v]);
        free(v);

        for (int i = 0; i < graph->length; ++i) {
            if (in_degrees[i] == 0) {
                queue_push_tail(queue, intdup(i));
            }
        }
    }

    queue_free(queue);
    free(in_degrees);
    return sorted_vertexes;
}

/**
 * @file graph.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to graph.h
 * @date 2019-07-21
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "graph.h"
#include "def.h"
#include "dup.h"
#include "queue.h"

#include <stdlib.h>
#include <string.h>

AdjacencyMatrix *adjacency_matrix_new(GraphType type, int num_vertexes)
{
    AdjacencyMatrix *graph = (AdjacencyMatrix *)malloc(sizeof(AdjacencyMatrix));
    graph->type = type;
    graph->num_vertexes = num_vertexes;
    graph->edges = (int **)malloc(sizeof(int *) * num_vertexes);
    for (int i = 0; i < num_vertexes; ++i) {
        graph->edges[i] = (int *)malloc(sizeof(int) * num_vertexes);
    }

    adjacency_matrix_reset(graph, -1);
    return graph;
}

void adjacency_matrix_free(AdjacencyMatrix *graph)
{
    for (int i = 0; i < graph->num_vertexes; ++i) {
        free(graph->edges[i]);
    }
    free(graph->edges);
    free(graph);
}

void adjacency_matrix_reset(AdjacencyMatrix *graph, int weight)
{
    for (int i = 0; i < graph->num_vertexes; ++i) {
        for (int j = 0; j < graph->num_vertexes; ++j) {
            graph->edges[i][j] = weight;
        }
    }
}

void adjacency_matrix_set(AdjacencyMatrix *graph,
                          int vertex1,
                          int vertex2,
                          int edge)
{
    graph->edges[vertex1][vertex2] = edge;
}

int adjacency_matrix_get(const AdjacencyMatrix *graph, int vertex1, int vertex2)
{
    return graph->edges[vertex1][vertex2];
}

static inline void adjacency_matrix_link_internal(AdjacencyMatrix *graph, int vertex1, int vertex2)
{
    graph->edges[vertex1][vertex2] = 1;
}

int adjacency_matrix_link(AdjacencyMatrix *graph, int vertex1, int vertex2)
{
    adjacency_matrix_link_internal(graph, vertex1, vertex2);
    if (graph->type == UndirectedUnweighted || graph->type == UndirectedWeighted) {
        adjacency_matrix_link_internal(graph, vertex2, vertex1);
    }
    return 0;
}

static inline int
adjacency_matrix_connected(const AdjacencyMatrix *graph, int from, int to)
{
    return graph->edges[from][to] >= 0;
}

int adjacency_matrix_bfs(const AdjacencyMatrix *graph, int start, int end)
{
    int found = -1;
    int *visited = (int *)malloc(sizeof(int) * graph->num_vertexes);
    memset(visited, 0, sizeof(int) * graph->num_vertexes);

    Queue *candidates = queue_new();
    queue_push_tail(candidates, intdup(start));

    while (queue_is_empty(candidates)) {
        int *current = (int *)queue_pop_head(candidates);
        visited[*current] = 1;

        if (*current == end) {
            free(current);
            found = 0;
            break;
        }

        for (int i = 0; i < graph->num_vertexes; ++i) {
            if (adjacency_matrix_connected(graph, *current, i) && !visited[i]) {
                queue_push_tail(candidates, intdup(i));
            }
        }
        free(current);
    }

    queue_free(candidates);
    free(visited);
    return found;
}

static int adjacency_matrix_dfs_internal(const AdjacencyMatrix *graph,
                                         int start,
                                         int end,
                                         int *visited)
{
    if (start == end) {
        return 0;
    }

    for (int i = 0; i < graph->num_vertexes; ++i) {
        if (adjacency_matrix_connected(graph, start, i) && !visited[i]) {
            adjacency_matrix_dfs_internal(graph, i, end, visited);
        }
    }

    return -1;
}

int adjacency_matrix_dfs(const AdjacencyMatrix *graph, int start, int end)
{
    int *visited = (int *)malloc(sizeof(int) * graph->num_vertexes);
    memset(visited, 0, sizeof(int) * graph->num_vertexes);
    int found = adjacency_matrix_dfs_internal(graph, start, end, visited);
    free(visited);
    return found;
}

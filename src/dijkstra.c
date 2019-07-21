/**
 * @file dijkstra.c
 * @author hutusi (hutusi@outlook.com)
 * @brief Refer to dijkstra.h
 * @date 2019-07-21
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#include "dijkstra.h"
#include <stdlib.h>

static void dijkstra_init_distances(int *distances, int num_vertexes)
{
    for (int i = 0; i < num_vertexes; ++i) {
        distances[i] = -1;
    }
}

static void dijkstra_refresh_candidates(const AdjacencyMatrix *graph,
                                        int vertex,
                                        int *distances,
                                        int *candidates)
{
    for (int i = 0; i < graph->num_vertexes; ++i) {
        int edge = adjacency_matrix_get(graph, vertex, i);
        /** if distances[i] > 0, the vertex has been selected */
        if (edge >= 0 && distances[i] < 0) {
            int new_weight = distances[vertex] + edge;
            if (candidates[i] < 0 || candidates[i] > new_weight) {
                candidates[i] = new_weight;
            }
        }
    }
    candidates[vertex] = -1;
}

int dijkstra_select_vertex(int *candidates, int num_vertexes)
{
    int weight = -1;
    int vertex = -1;
    for (int i = 0; i < num_vertexes; ++i) {
        if (candidates[i] >= 0 && (weight == -1 || weight > candidates[i])) {
            weight = candidates[i];
            vertex = i;
        }
    }
    return vertex;
}

void dijkstra(const AdjacencyMatrix *graph, int vertex, int *distances)
{
    dijkstra_init_distances(distances, graph->num_vertexes);
    int *candidates = (int *)malloc(sizeof(int *) * graph->num_vertexes);
    dijkstra_init_distances(candidates, graph->num_vertexes);

    int select = vertex;
    candidates[vertex] = 0;
    while (select >= 0) {
        distances[select] = candidates[select];
        dijkstra_refresh_candidates(graph, select, distances, candidates);
        select = dijkstra_select_vertex(candidates, graph->num_vertexes);
    }

    free(candidates);
}

/**
 * @file dijkstra.h
 *
 * @author hutusi (hutusi@outlook.com)
 *
 * @brief Dijkstra algorithm.
 *
 * @date 2019-07-21
 *
 * @copyright Copyright (c) 2019, hutusi.com
 *
 */

#ifndef RETHINK_C_DIJKSTRA_H
#define RETHINK_C_DIJKSTRA_H

#include "graph.h"

/**
 * @brief Dijkstra algorithm.
 *
 * @param graph         AdjacencyMatrix graph.
 * @param vertex        The start vertex.
 * @param distances     The distances array. (output)
 */
void dijkstra(const AdjacencyMatrix *graph, int vertex, int *distances);

#endif /* #ifndef RETHINK_C_DIJKSTRA_H */

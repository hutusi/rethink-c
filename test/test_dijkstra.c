#include "dijkstra.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc-testing.h"
#include "test_helper.h"

static int max_in_array(int *distances, int num)
{
    int max = -1;
    for (int i = 0; i < num; ++i) {
        if (distances[i] < 0) {
            max = -1;
            break;
        } else if (distances[i] > max) {
            max = distances[i];
        } else {
        }
    }
    return max;
}

static void test_dijkstra_1()
{
    AdjacencyMatrix *graph = adjacency_matrix_new(DirectedWeighted, 4);
    adjacency_matrix_reset(graph, -1);
    adjacency_matrix_set(graph, 1, 0, 1);
    adjacency_matrix_set(graph, 1, 2, 1);
    adjacency_matrix_set(graph, 2, 3, 1);
    int *distances = (int *)malloc(sizeof(int) * 4);

    dijkstra(graph, 1, distances);
    assert(max_in_array(distances, 4) == 2);

    free(distances);
    adjacency_matrix_free(graph);
}

static void test_dijkstra_2()
{
    AdjacencyMatrix *graph = adjacency_matrix_new(DirectedWeighted, 2);
    adjacency_matrix_reset(graph, -1);
    adjacency_matrix_set(graph, 0, 1, 1);
    int *distances = (int *)malloc(sizeof(int) * 4);

    dijkstra(graph, 1, distances);
    assert(max_in_array(distances, 2) == -1);

    free(distances);
    adjacency_matrix_free(graph);
}

static void test_dijkstra_3()
{
    AdjacencyMatrix *graph = adjacency_matrix_new(DirectedWeighted, 4);
    adjacency_matrix_reset(graph, -1);
    adjacency_matrix_set(graph, 0, 1, 1);
    adjacency_matrix_set(graph, 1, 2, 1);
    adjacency_matrix_set(graph, 2, 3, 1);
    adjacency_matrix_set(graph, 3, 0, 1);
    int *distances = (int *)malloc(sizeof(int) * 4);

    dijkstra(graph, 1, distances);
    assert(max_in_array(distances, 4) == 3);

    free(distances);
    adjacency_matrix_free(graph);
}

static void test_dijkstra_4()
{
    AdjacencyMatrix *graph = adjacency_matrix_new(DirectedWeighted, 4);
    adjacency_matrix_reset(graph, -1);
    adjacency_matrix_set(graph, 0, 1, 1);
    adjacency_matrix_set(graph, 1, 2, 1);
    adjacency_matrix_set(graph, 2, 3, 1);
    adjacency_matrix_set(graph, 0, 3, 1);
    int *distances = (int *)malloc(sizeof(int) * 4);

    dijkstra(graph, 0, distances);
    assert(max_in_array(distances, 4) == 2);

    free(distances);
    adjacency_matrix_free(graph);
}

static void test_dijkstra_5()
{
    AdjacencyMatrix *graph = adjacency_matrix_new(DirectedWeighted, 3);
    adjacency_matrix_reset(graph, -1);
    adjacency_matrix_set(graph, 0, 1, 1);
    adjacency_matrix_set(graph, 1, 2, 2);
    adjacency_matrix_set(graph, 0, 2, 2);
    int *distances = (int *)malloc(sizeof(int) * 3);

    dijkstra(graph, 0, distances);
    assert(max_in_array(distances, 3) == 2);

    free(distances);
    adjacency_matrix_free(graph);
}

void test_dijkstra()
{
    test_dijkstra_1();
    test_dijkstra_2();
    test_dijkstra_3();
    test_dijkstra_4();
    test_dijkstra_5();
}

// https://leetcode.com/problems/network-delay-time/
int networkDelayTime(
    int **times, int timesSize, int *timesColSize, int N, int K)
{
    AdjacencyMatrix *graph = adjacency_matrix_new(DirectedWeighted, N + 1);
    int *distances = (int *)malloc(sizeof(int) * (N + 1));
    adjacency_matrix_reset(graph, -1);

    for (int i = 0; i < timesSize; ++i) {
        adjacency_matrix_set(graph, times[i][0], times[i][1], times[i][2]);
    }

    dijkstra(graph, K, distances);
    int time = max_in_array(distances, N + 1);

    free(distances);
    adjacency_matrix_free(graph);
    return time;
}

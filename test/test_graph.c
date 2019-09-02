#include "graph.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "alloc-testing.h"
#include "test_helper.h"

static AdjacencyMatrix *init_ud_uw_graph()
{
    AdjacencyMatrix *graph = adjacency_matrix_new(UndirectedUnweighted, 10);
    adjacency_matrix_link(graph, 0, 1);
    adjacency_matrix_link(graph, 0, 2);
    adjacency_matrix_link(graph, 0, 3);
    adjacency_matrix_link(graph, 0, 4);
    adjacency_matrix_link(graph, 0, 5);

    adjacency_matrix_link(graph, 1, 2);
    adjacency_matrix_link(graph, 1, 3);
    adjacency_matrix_link(graph, 1, 4);
    adjacency_matrix_link(graph, 1, 5);
    adjacency_matrix_link(graph, 1, 6);

    adjacency_matrix_link(graph, 2, 3);
    adjacency_matrix_link(graph, 2, 4);
    adjacency_matrix_link(graph, 2, 5);
    adjacency_matrix_link(graph, 2, 6);
    adjacency_matrix_link(graph, 2, 7);

    adjacency_matrix_link(graph, 3, 4);
    adjacency_matrix_link(graph, 3, 5);
    adjacency_matrix_link(graph, 3, 6);
    adjacency_matrix_link(graph, 3, 7);

    adjacency_matrix_link(graph, 4, 5);
    adjacency_matrix_link(graph, 4, 6);
    adjacency_matrix_link(graph, 4, 7);

    adjacency_matrix_link(graph, 5, 6);
    adjacency_matrix_link(graph, 5, 7);

    adjacency_matrix_link(graph, 6, 7);

    adjacency_matrix_link(graph, 7, 8);

    return graph;
}

void test_graph_bfs()
{
    AdjacencyMatrix *graph = init_ud_uw_graph();
    ASSERT_INT_EQ(adjacency_matrix_bfs(graph, 0, 9), -1);
    ASSERT_INT_EQ(adjacency_matrix_bfs(graph, 0, 8), 0);
    adjacency_matrix_free(graph);
}

void test_graph_dfs()
{
    AdjacencyMatrix *graph = init_ud_uw_graph();
    ASSERT_INT_EQ(adjacency_matrix_dfs(graph, 0, 9), -1);
    ASSERT_INT_EQ(adjacency_matrix_dfs(graph, 0, 8), 0);
    adjacency_matrix_free(graph);
}

void test_graph()
{
    test_graph_bfs();
    test_graph_dfs();
}

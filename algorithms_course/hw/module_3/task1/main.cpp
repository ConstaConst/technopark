#include <iostream>
#include "CListGraph.h"
#include "CMatrixGraph.h"
#include "CSetGraph.h"
#include "CArcGraph.h"

int main() {
    CArcGraph graph(7);
    graph.AddEdge(0, 1);
    graph.AddEdge(0, 5);
    graph.AddEdge(1, 2);
    graph.AddEdge(1, 3);
    graph.AddEdge(1, 5);
    graph.AddEdge(1, 6);
    graph.AddEdge(3, 2);
    graph.AddEdge(3, 6);
    graph.AddEdge(4, 3);
    graph.AddEdge(5, 4);
    graph.AddEdge(5, 6);
    graph.AddEdge(6, 4);

    CMatrixGraph graph2(graph);

    for (int i = 0; i < graph2.VerticesCount(); ++i) {
        std::vector<int> vertices;
        graph2.GetNextVertices(i, vertices);
        std::cout << "next: ";
        for(auto v: vertices) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
        graph2.GetPrevVertices(i, vertices);
        std::cout << "prev: ";
        for(auto v: vertices) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
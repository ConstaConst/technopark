#include <cassert>
#include "CArcGraph.h"

CArcGraph::CArcGraph(int count) : verticesCounter(count) {}

CArcGraph::CArcGraph(const IGraph& graph) : verticesCounter(graph.VerticesCount()) {
    std::vector<int> nextV;
    for (int i = 0; i < verticesCounter; i++) {
        graph.GetNextVertices(i, nextV);
        for (int next: nextV) {
            adjacencyLists.emplace_back(i, next);
        }
    }
}

void CArcGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < verticesCounter);
    assert(to >= 0 && to < verticesCounter);

    adjacencyLists.emplace_back(from, to);
}

int CArcGraph::VerticesCount() const {
    return verticesCounter;
}

void CArcGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const {
    assert(vertex >= 0 && vertex < verticesCounter);

    vertices.clear();
    for (auto link: adjacencyLists) {
        if (link.first == vertex) {
            vertices.push_back(link.second);
        }
    }
}

void CArcGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
    assert(vertex >= 0 && vertex < verticesCounter);

    vertices.clear();
    for (auto link: adjacencyLists) {
        if (link.second == vertex) {
            vertices.push_back(link.first);
        }
    }
}

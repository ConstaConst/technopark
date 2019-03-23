#include <cassert>
#include "CMatrixGraph.h"

CMatrixGraph::CMatrixGraph(int count) : adjacencyLists(count, std::vector<bool >(count, false)) {}

CMatrixGraph::CMatrixGraph(const IGraph& graph)
        : adjacencyLists(graph.VerticesCount(), std::vector<bool>(graph.VerticesCount(), false)) {
    std::vector<int> nextV;
    for (int i = 0; i < adjacencyLists.size(); ++i) {
        graph.GetNextVertices(i, nextV);
        for (int next: nextV) {
            adjacencyLists[i][next] = true;
        }
    }
}

void CMatrixGraph::AddEdge(int from, int to) {
    assert(0 <= from && from < adjacencyLists.size());
    assert(0 <= to && to < adjacencyLists.size());

    adjacencyLists[from][to] = true;
}

int CMatrixGraph::VerticesCount() const {
    return adjacencyLists.size();
}

void CMatrixGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const {
    assert(0 <= vertex && vertex < adjacencyLists.size());

    vertices.clear();
    for (int to = 0; to < adjacencyLists.size(); ++to) {
        if (adjacencyLists[vertex][to]) {
            vertices.push_back(to);
        }
    }
}

void CMatrixGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
    assert(0 <= vertex && vertex < adjacencyLists.size());

    vertices.clear();
    for (int from = 0; from < adjacencyLists.size(); ++from) {
        if (adjacencyLists[from][vertex]) {
            vertices.push_back(from);
        }
    }
}

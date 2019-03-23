#include <cassert>
#include "CSetGraph.h"

CSetGraph::CSetGraph(int count) : adjacencyLists(count) {}

CSetGraph::CSetGraph(const IGraph& graph) : adjacencyLists(graph.VerticesCount()) {
    std::vector<int> nextV;
    for (int from = 0; from < adjacencyLists.size(); from++) {
        graph.GetNextVertices(from, nextV);
        adjacencyLists[from].insert(nextV.begin(), nextV.end());
    }
}

void CSetGraph::AddEdge(int from, int to) {
    assert(from >= 0 && from < adjacencyLists.size());
    assert(to >= 0 && to < adjacencyLists.size());

    adjacencyLists[from].insert({to});
}

int CSetGraph::VerticesCount() const {
    return adjacencyLists.size();
}

void CSetGraph::GetNextVertices(int vertex, std::vector<int>& vertices) const {
    assert(0 <= vertex && vertex < adjacencyLists.size());

    vertices.clear();
    for (const int& next: adjacencyLists[vertex]) {
        vertices.push_back(next);
    }
}

void CSetGraph::GetPrevVertices(int vertex, std::vector<int>& vertices) const {
    assert(0 <= vertex && vertex < adjacencyLists.size());

    vertices.clear();
    for(int i = 0; i < adjacencyLists.size(); i++) {
        if (adjacencyLists[i].count(vertex) > 0) {
            vertices.push_back(i);
        }
    }
}


#include <algorithm>
#include "Graph.h"

Graph::Graph(int n) : adjacencyLists(n) {}

void Graph::addEdge(int first, int second, int cost) {
    assert(first >= 0 && first < adjacencyLists.size() && second >= 0 && second < adjacencyLists.size());

    adjacencyLists[first].insert({second, cost});
    adjacencyLists[second].insert({first, cost});
}

const std::set<std::pair<int, int>> &Graph::getAdjacencyVertices(int vertex) const {
    assert(vertex >= 0 && vertex < adjacencyLists.size());

    return adjacencyLists[vertex];
}

int Graph::verticesCount() const {
    return adjacencyLists.size();
}

std::set<std::pair<int, std::pair<int, int>>> Graph::getEdges() const {
    std::set<std::pair<int, std::pair<int, int>>> edges;

    for (int i = 0; i < adjacencyLists.size(); ++i) {
        for (auto link: adjacencyLists[i]) {
            edges.insert({link.second, {i, link.first}});
        }
    }

    return edges;
}

int Graph::getEdgeCost(int v, int u) const {
    assert(v >= 0 && v < adjacencyLists.size());
    assert(u >= 0 && u < adjacencyLists.size());

    auto listIt = adjacencyLists[v].begin();
    for (; listIt != adjacencyLists[v].end(); ++listIt) {
        if (listIt->first == u) {
            return listIt->second;
        }
    }
}



#include "DSU.h"
#include "Graph.h"

int makeMSTbyKruskal(const Graph& graph, Graph& mst) {
    int cost = 0;

    mst = Graph(graph.verticesCount());

    auto edges = graph.getEdges();

    DSU dsu(graph.verticesCount());

    int u = 0;
    int v = 0;
    int weight = 0;
    for (auto &edge : edges) {
        u = edge.second.first;
        v = edge.second.second;
        weight = edge.first;
        if (dsu.find(u) != dsu.find(v)) {
            cost += weight;
            mst.addEdge(u, v, weight);
            dsu.merge(u, v);
        }
    }

    return cost;
}

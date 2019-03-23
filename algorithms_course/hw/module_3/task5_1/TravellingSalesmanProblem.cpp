#include "TravellingSalesmanProblem.h"
#include "KruskalsAlgorithm.h"

int recursionSearch(const Graph& graph, int vertex, std::vector<int> way, std::vector<bool> used, int cost) {
    assert(vertex >= 0 && vertex < graph.verticesCount());

    used[vertex] = true;
    way.push_back(vertex);
    if (way.size() == graph.verticesCount()) {
        return cost + graph.getEdgeCost(vertex, 0);
    }
    int minCost = -1;
    for (const auto& next: graph.getAdjacencyVertices(vertex)) {
        if (used[next.first] != true) {
            int nextCost = recursionSearch(graph, next.first, way, used, cost + graph.getEdgeCost(vertex, next.first));
            if (nextCost < minCost || minCost == -1) {
                minCost = nextCost;
            }
        }
    }
    return minCost;
}

int searchCostMinSalesmanWay(const Graph& graph) {
    if (graph.verticesCount() == 0) {
        return 0;
    }

    std::vector<int> way;
    std::vector<bool> used(graph.verticesCount(), false);

    return recursionSearch(graph, 0, way, used, 0);
}

void dfs(const Graph& graph, int start, std::vector<int>& way, std::vector<bool>& used) {
    assert(start >= 0 && start < graph.verticesCount());

    used[start] = true;
    way.push_back(start);
    for (const auto& next: graph.getAdjacencyVertices(start)) {
        if (used[next.first] != true) {
            dfs(graph, next.first, way, used);
        }
    }
}


std::vector<int> searchSalesmanWay(const Graph& graph) {
    if (graph.verticesCount() == 0) {
        return std::vector<int>();
    }

    Graph mst(0);
    makeMSTbyKruskal(graph, mst);

    std::vector<int> way;
    std::vector<bool> used(mst.verticesCount(), false);
    dfs(mst, 0, way, used);

    return way;
}

int countWayCost(const Graph& graph, const std::vector<int>& way) {
    int result = 0;

    for (int i = 0; i < way.size() - 1; ++i) {
        result += graph.getEdgeCost(way[i], way[i + 1]);
    }
    result += graph.getEdgeCost(way[way.size() - 1], way[0]);

    return result;
}
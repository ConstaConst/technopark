#ifndef TASK5_1_GRAPH_H
#define TASK5_1_GRAPH_H


#include <cassert>
#include <vector>
#include <set>
#include <list>

class Graph {
public:
    explicit Graph(int n);

    Graph(const Graph& graph) = default;

    void addEdge(int first, int second, int cost);
    const std::set<std::pair<int, int>>& getAdjacencyVertices(int vertex) const;
    int getEdgeCost(int v, int u) const;
    int verticesCount() const;
    //<вес ребра <v, u>>
    std::set<std::pair<int, std::pair<int, int>>> getEdges() const;;

private:
    //to - стоимость
    std::vector<std::set<std::pair<int, int>>> adjacencyLists;
};

#endif //TASK5_1_GRAPH_H

#ifndef TASK1_CSETGRAPH_H
#define TASK1_CSETGRAPH_H


#include <unordered_set>
#include "IGraph.h"

class CSetGraph : public IGraph {
public:
    explicit CSetGraph(int count);
    explicit CSetGraph(const IGraph& graph);
    ~CSetGraph() override = default;

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    void GetNextVertices(int vertex, std::vector<int>& vertices) const override;

    void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;

private:
    std::vector<std::unordered_set<int>> adjacencyLists;
};

#endif //TASK1_CSETGRAPH_H


#ifndef TASK1_CLISTGRAPH_H
#define TASK1_CLISTGRAPH_H

#include <vector>
#include "IGraph.h"

class CListGraph : public IGraph {
public:
    explicit CListGraph(int count);
    explicit CListGraph(const IGraph& graph);

    ~CListGraph() override = default;

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    void GetNextVertices(int vertex, std::vector<int>& vertices) const override;

    void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;

private:
    std::vector<std::vector<int>> adjacencyLists;
};
#endif //TASK1_CLISTGRAPH_H

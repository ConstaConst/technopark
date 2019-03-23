#ifndef TASK1_CARCGRAPH_H
#define TASK1_CARCGRAPH_H


#include "IGraph.h"

class CArcGraph : public IGraph {
public:
    explicit CArcGraph(int count);
    explicit CArcGraph(const IGraph& graph);
    ~CArcGraph() override = default;

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    void GetNextVertices(int vertex, std::vector<int>& vertices) const override;

    void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;

private:
    //from, to
    std::vector<std::pair<int, int>> adjacencyLists;
    int verticesCounter;
};


#endif //TASK1_CARCGRAPH_H

#ifndef TASK1_CMATRIXGRAPH_H
#define TASK1_CMATRIXGRAPH_H


#include "IGraph.h"

class CMatrixGraph: public IGraph {
public:
    explicit CMatrixGraph(int count);
    explicit CMatrixGraph(const IGraph& graph);

    ~CMatrixGraph() override = default;

    // Добавление ребра от from к to.
    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    void GetNextVertices(int vertex, std::vector<int>& vertices) const override;

    void GetPrevVertices(int vertex, std::vector<int>& vertices) const override;

private:
    std::vector<std::vector<bool>> adjacencyLists;
};


#endif //TASK1_CMATRIXGRAPH_H

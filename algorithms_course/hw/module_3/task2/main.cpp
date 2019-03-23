/* Задача 2. Количество различных путей
    Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).
Формат ввода.
v: кол-во вершин (макс. 50000),
n: кол-во ребер (макс. 200000),
n пар реберных вершин,
пара вершин u, w для запроса.
Формат вывода.
Количество кратчайших путей от u к w.
in: 4           out: 2
    5
    0 1
    0 2
    1 2
    1 3
    2 3

    0 3
*/

#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <queue>


class Graph {
public:
    explicit Graph(size_t n) : adjacencyList_(n) {}

    void addEdge(size_t first, size_t second) {
        assert(first < adjacencyList_.size() && second < adjacencyList_.size());

        adjacencyList_[first].push_back(second);
        adjacencyList_[second].push_back(first);
    }

    const std::list<size_t>& getAdjacencyVertices(size_t vertex) const {
        assert(vertex < adjacencyList_.size());

        return adjacencyList_[vertex];
    }

    size_t verticesCount() const {
        return adjacencyList_.size();
    }

private:
    std::vector<std::list<size_t>> adjacencyList_;
};

size_t countMinWays(const Graph& graph, size_t start, size_t finish) {
    assert(start < graph.verticesCount() && finish < graph.verticesCount() && start != finish);

    //first - количество мин путей, second - длина мин пути
    std::vector<std::pair<size_t, size_t>> searchInfo(graph.verticesCount(), {0, UINT64_MAX});

    std::queue<size_t> q;
    q.push(start);
    searchInfo[start] = {1, 0};

    while (!q.empty() && q.front() != finish) {
        size_t currentV = q.front();
        q.pop();

        for(size_t nextV: graph.getAdjacencyVertices(currentV)) {
            if (searchInfo[nextV].second < searchInfo[currentV].second + 1) {
                continue;
            }
            if (searchInfo[nextV].second == UINT64_MAX || searchInfo[nextV].second > searchInfo[currentV].second + 1) {
                searchInfo[nextV].second = searchInfo[currentV].second + 1;
                searchInfo[nextV].first = searchInfo[currentV].first;
                q.push(nextV);
            } else {
                searchInfo[nextV].first += searchInfo[currentV].first;
            }
        }
    }

    return searchInfo[finish].first;
}


int main() {
    size_t numV = 0;
    std::cin >> numV;

    Graph graph(numV);

    size_t numE = 0;
    std::cin >> numE;
    size_t v = 0;
    size_t u = 0;
    for(size_t i = 0; i < numE; ++i) {
        std::cin >> v >> u;
        graph.addEdge(v, u);
    }
    std::cin >> v >> u;

    std::cout << countMinWays(graph, v, u);

    return 0;
}
/* Задача 3. «Города»
Требуется отыскать самый выгодный маршрут между городами. Требуемое время работы O((N+M)logN),
 где N-количество городов, M-известных дорог между ними.
Оптимизируйте ввод
Формат входных данных.
Первая строка содержит число N – количество городов.
Вторая строка содержит число M - количество дорог.
Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
Последняя строка содержит маршрут (откуда и куда нужно доехать).
Формат выходных данных.
Вывести длину самого выгодного маршрута.

    in: 6       out: 9
        9
        0 3 1
        0 4 2
        1 2 7
        1 3 2
        1 4 3
        1 5 3
        2 5 3
        3 4 4
        3 5 6
        0 2
*/

#include <iostream>
#include <vector>
#include <list>
#include <cassert>
#include <set>

#define INF 10000000

class Graph {
public:
    explicit Graph(int n) : adjacencyList_(static_cast<unsigned long>(n)) {}

    void addEdge(int first, int second, int cost) {
        assert(first < adjacencyList_.size() && second < adjacencyList_.size());

        adjacencyList_[first].emplace_back(second, cost);
        adjacencyList_[second].emplace_back(first, cost);
    }

    const std::list<std::pair<int, int >>& getAdjacencyVertices(int vertex) const {
        assert(vertex < adjacencyList_.size());

        return adjacencyList_[vertex];
    }

    int verticesCount() const {
        return static_cast<int>(adjacencyList_.size());
    }

private:
    //first - вершина, second - стоимость
    std::vector<std::list<std::pair<int, int>>> adjacencyList_;
};

int searchMinWay(const Graph& graph, int start, int finish) {
    assert(start < graph.verticesCount() && finish < graph.verticesCount());

    //first - distance, second - is visited
    std::vector<std::pair<int, bool>> distances(static_cast<unsigned long>(graph.verticesCount()), {INF, false});

    //first - мин расстояние до вершины second
    std::set<std::pair<int, int>> priorityVertices;
    priorityVertices.emplace(0, start);
    distances[start] = {0, false};

    while (!priorityVertices.empty()) {
        int currentV = priorityVertices.begin()->second;
        if (currentV == finish) {
            break;
        }
        priorityVertices.erase(priorityVertices.begin());
        distances[currentV].second = true;

        for (std::pair<int, int> nextV: graph.getAdjacencyVertices(currentV)) {
            int distTo = distances[nextV.first].first;
            if (!distances[nextV.first].second && distTo > distances[currentV].first + nextV.second) {

                int newDistance = distances[currentV].first + nextV.second;
                priorityVertices.erase({distTo, nextV.first});
                distances[nextV.first].first = newDistance;
                priorityVertices.emplace(newDistance, nextV.first);
            }
        }
    }

    return distances[finish].first;
}

int main() {
    int N = 0;
    std::cin >> N;
    Graph graph(N);

    int M = 0;
    std::cin >> M;
    int v = 0;
    int u = 0;
    int dist = 0;
    for (int i = 0; i < M; ++i) {
        std::cin >> v >> u >> dist;
        graph.addEdge(v, u, dist);
    }

    std::cin >> v >> u;

    std::cout << searchMinWay(graph, v, u);
}
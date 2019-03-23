/* Задача 5. Приближенное решение метрической неориентированной задачи коммивояжера.
Найдите приближенное решение метрической неориентированной задачи коммивояжера в полном графе (на плоскости)
с помощью минимального остовного дерева.
Оцените качество приближения на случайном наборе точек, нормально распределенном на плоскости с дисперсией 1.
Нормально распределенный набор точек получайте с помощью преобразования Бокса-Мюллера.
При фиксированном N, количестве вершин графа, несколько раз запустите оценку качества приближения.
Вычислите среднее значение и среднеквадратичное отклонение качества приближения для данного N.
Запустите данный эксперимент для всех N в некотором диапазоне, например, [2, 10].
Автоматизируйте запуск экспериментов.
В решении требуется разумно разделить код на файлы. Каждому классу - свой заголовочный файл и файл с реализацией.

Для построения минимального остовного дерева используйте алгоритм Крускала.

В контесте протестируйте работу алгоритма построения минимального остовного дерева.
(Варианты в контесте - не те, который описаны здесь. Правильные варианты - здесь.)

Для контеста.
Дан неориентированный связный граф. Требуется найти вес минимального остовного дерева в этом графе.
Формат ввода
Первая строка содержит два натуральных числа n и m — количество вершин и ребер графа соответственно
(1 ≤ n ≤ 20000, 0 ≤ m ≤ 100000).
Следующие m строк содержат описание ребер по одному на строке.
Ребро номер i описывается тремя натуральными числами bi, ei и wi — номера концов ребра и его вес соответственно
(1 ≤ bi, ei ≤ n, 0 ≤ wi ≤ 100000).
Формат вывода
Выведите единственное целое число - вес минимального остовного дерева.
    in: 4 4             out: 7
        1 2 1
        2 3 2
        3 4 5
        4 1 4

    in: 5 10            out: 107923
        4 3 3046
        4 5 90110
        5 1 57786
        3 2 28280
        4 3 18010
        4 5 61367
        4 1 18811
        4 2 69898
        3 5 72518
        3 1 85838
 */
#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <list>
#include <set>

class Graph {
public:
    explicit Graph(int n) : verticesCounter(n), edges() {}

    void addEdge(int first, int second, int cost) {
        assert(first >= 0 && first < verticesCounter && second >= 0 && verticesCounter);

        edges.push_back({cost, {first, second}});
    }

    int verticesCount() const {
        return verticesCounter;
    }
    //<вес ребра <v, u>>
    std::set<std::pair<int, std::pair<int, int>>> getEdges() const {
        return std::set<std::pair<int, std::pair<int, int>>>(edges.begin(), edges.end());
    };

private:
    //стоимость, (v, u)
    std::vector<std::pair<int, std::pair<int, int>>> edges;
    int verticesCounter;
};



class DSU {
public:
    explicit DSU (int n) : parent(n), rank(n) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] == u) {
            return u;
        }
        // Сжатие пути.
        return parent[u] = find(parent[u]);
    }
    void merge(int u, int v) {
        const int rootU = find(u);
        const int rootV = find(v);
        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else {
            if (rank[rootU] == rank[rootV]) {
                ++rank[rootU];
            }
            parent[rootV] = rootU;
        }
    }

private:
    std::vector<int> parent;
    std::vector<int> rank; // Ранги узлов. Глубина дереве не больше ранга.
};

int makeMSTbyKruskal(const Graph& graph, Graph& mst) {
    int cost = 0;

    std::set<std::pair<int, std::pair<int, int>>> edges = graph.getEdges();
    mst = Graph(graph.verticesCount());
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



int main() {
    int V = 0;
    std::cin >> V;
    Graph graph(V);

    int E = 0;
    std::cin >> E;
    int u = 0;
    int v = 0;
    int weight = 0;
    for (int i = 0; i < E; ++i) {
        std::cin >> u >> v >> weight;
        graph.addEdge(u - 1, v - 1, weight);
    }

    Graph mst(0);

    std::cout << makeMSTbyKruskal(graph, mst) << std::endl;

    return 0;
}

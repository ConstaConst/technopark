#ifndef TASK5_1_DSU_H
#define TASK5_1_DSU_H


#include <vector>


class DSU {
public:
    explicit DSU(int n);

    int find(int u);
    void merge(int u, int v);

private:
    std::vector<int> parent;
    std::vector<int> rank; // Ранги узлов. Глубина дереве не больше ранга.
};


#endif //TASK5_1_DSU_H

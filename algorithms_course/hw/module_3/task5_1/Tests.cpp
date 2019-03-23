#include <cassert>
#include <iostream>
#include <numeric>
#include <cmath>
#include "Tests.h"
#include "Graph.h"
#include "RandomPointsGenerator.h"
#include "TravellingSalesmanProblem.h"


float testNGraph (int n) {
    assert(n > 0);

    std::vector<std::pair<int, int>> points = generateNormalRandomPoints(n);

    std::cout << n << " points: ";
    for (const auto& point: points) {
        std::cout << "(" << point.first << ", " << point.second << ") ";
    }
    std::cout << std::endl;

    Graph graph(makeFullGraphOfPoints(points));
    int costMST = countWayCost(graph, searchSalesmanWay(graph));
    int minCost = searchCostMinSalesmanWay(graph);
    std::cout << "MST solution: " << costMST << "\t";
    std::cout << "Ideal solution: " << minCost << "\t";
    std::cout << "Difference: " << costMST - minCost << std::endl;

    float error = static_cast<float>(costMST) / minCost - 1;
    std::cout << "Error value = " << error * 100 << "%" << std::endl;

    return error;
}
//<среднее значение, среднеквадратичное значение>
std::pair<float, float> calculateErrors(const std::vector<float>& errors) {
    float sum = static_cast<float>(std::accumulate(errors.begin(), errors.end(), 0.));
    float midDev = sum/ errors.size();
    float standardDev = 0;
    for (float error : errors) {
        standardDev += (error - midDev) * (error - midDev);
    }
    standardDev = std::sqrt(standardDev / errors.size());

    return {midDev, standardDev};
};
//Тесты в диапазоне [from, to] times раз каждое значение
void test(int from, int to, int times) {
    assert(from >= 0 && to >= 0 && from < to);
    std::vector<float> errors;
    for (int i = from; i <= to; ++i) {
        std::cout << "Vertices: " << i << std::endl;
        for (int j = 0; j < times; ++j) {
            std::cout << "(N " << j + 1 << ") " << "{" << std::endl;
            errors.push_back(testNGraph(i));
            std::cout << "}" << std::endl;
        }
        auto divs = calculateErrors(errors);
        std::cout << "Middle deviation = " << divs.first * 100 << "%" << "\t\t"
                 << "Standard deviation = " << divs.second * 100 << "%" << std::endl;
        std::cout << "=========================================================================================" << std::endl;
        errors.clear();
    }
}
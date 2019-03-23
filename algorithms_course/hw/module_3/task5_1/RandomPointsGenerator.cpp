#include <cmath>
#include <cassert>
#include <random>
#include <iostream>
#include "RandomPointsGenerator.h"
#include "Graph.h"


bool transformBoxMuller(std::pair<float, float>& point) {
    if (-1 <=  point.first && point.first >= 1 && -1 <= point.second && point.second >= 1) {
        return false;
    }
    float s = point.first * point.first + point.second * point.second;
    if (s > 1 || s == 0) {
        return false;
    }

    float forTransform = std::sqrt(-2 *std::log(s) / s);
    point.first = point.first * forTransform;
    point.second = point.second * forTransform;

    return true;
}

std::vector<std::pair<int, int>> generateNormalRandomPoints(int count) {
    assert(count >= 0);

    std::random_device rd1;
    std::random_device rd2;
    std::uniform_real_distribution<float> distribution(-1,1);

    std::vector<std::pair<int, int>> points;

    std::pair<float, float> point;
    while (count > 0) {
        do {
            point = {distribution(rd1), distribution(rd2)};
        } while(!transformBoxMuller(point));

        points.emplace_back(static_cast<int>(100 * point.first), static_cast<int>(100 * point.second));
        --count;
    }

    return points;
};

int distance(const std::pair<int, int>& firstPoint, const std::pair<int, int>& secondPoint) {
    return static_cast<int>(std::sqrt((firstPoint.first - secondPoint.first) * (firstPoint.first - secondPoint.first)
                                      + (firstPoint.second - secondPoint.second) * (firstPoint.second - secondPoint.second)));
}

Graph makeFullGraphOfPoints(const std::vector<std::pair<int, int>>& points) {
    Graph graph(points.size());

    for (int i = 0; i < points.size(); ++i) {
        for (int j = 0; j < points.size(); ++j) {
            if (i != j) {
                //std::cout << "dist: " << i << "|" << j << " " << distance(points[i], points[j]) << std::endl;
                graph.addEdge(i, j, distance(points[i], points[j]));
            }
        }
    }
    return graph;
}
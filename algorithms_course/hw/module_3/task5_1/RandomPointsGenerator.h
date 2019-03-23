#ifndef TASK5_1_RANDOMPOINTSGENERATOR_H
#define TASK5_1_RANDOMPOINTSGENERATOR_H

#include <vector>
#include "Graph.h"

std::vector<std::pair<int, int>> generateNormalRandomPoints(int count);

Graph makeFullGraphOfPoints(const std::vector<std::pair<int, int>>& points);

#endif //TASK5_1_RANDOMPOINTSGENERATOR_H

#ifndef TASK5_1_TRAVELLINGSALESMANPROBLEM_H
#define TASK5_1_TRAVELLINGSALESMANPROBLEM_H


#include "Graph.h"

std::vector<int> searchSalesmanWay(const Graph& graph);
int countWayCost(const Graph& graph, const std::vector<int>& way);

int searchCostMinSalesmanWay(const Graph& graph);


#endif //TASK5_1_TRAVELLINGSALESMANPROBLEM_H

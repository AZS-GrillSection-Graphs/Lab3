#ifndef GRAPHS1_RANDOMSIMPLEGRAPH_H
#define GRAPHS1_RANDOMSIMPLEGRAPH_H

#include "AdjacencyList.h"
#include "SimpleGraph.h"


class RandomSimpleConsistentGraph : public SimpleGraph {
public:
    RandomSimpleConsistentGraph();
    std::string GenerateNumberSeries();

private:
    std::vector<int> verticlesValues;

    void FillWithRandomWages();
};

#endif //GRAPHS1_RANDOMSIMPLEGRAPH_H

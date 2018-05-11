//
// Created by os8 on 10.05.18.
//

#ifndef GRAPHS3_NEWSTRUCTURE_SIMPLEGRAPH_H
#define GRAPHS3_NEWSTRUCTURE_SIMPLEGRAPH_H


#include "Graph.h"

class RandomSimpleConsistentGraph : public Graph {
public:
    RandomSimpleConsistentGraph();

private:
    std::vector<int> Components();
    void Components_R(const int componentNumber, const int index, std::vector<int> &componentsOfVerticles);
    int NumberOfComponents();

};


#endif //GRAPHS3_NEWSTRUCTURE_SIMPLEGRAPH_H

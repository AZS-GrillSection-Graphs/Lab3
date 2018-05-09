#include "RandomSimpleConsistentGraph.h"

#include <iostream>


RandomSimpleConsistentGraph::RandomSimpleConsistentGraph() : SimpleGraph(GenerateNumberSeries()) {
    while(NumberOfComponents() > 1) {
        RandomizeGraph();
    }

    m_graphRepr = reinterpret_cast<AdjacencyList *>(m_graphRepr)->CovertToAdjacencyMatrix();
    FillWithRandomWages();

}

std::string RandomSimpleConsistentGraph::GenerateNumberSeries() {
    std::string numberSeries;

    do {
        if(!numberSeries.empty())
            numberSeries.clear();

        int numberOfVerticles = rand() % 20 + 5;        //limit for tests

        for (int i = 0; i < numberOfVerticles; i++) {
            int verticleDegree = rand() % numberOfVerticles + 1;

            numberSeries += std::to_string(verticleDegree);
            numberSeries += " ";
        }
    }
    while(!IsGraphicSeries(numberSeries));

    return numberSeries;
}

void RandomSimpleConsistentGraph::FillWithRandomWages() {
    for(int i = 0; i < m_graphRepr->GetData().size(); i++)
        verticlesValues.push_back(rand() % 10 + 1);
}





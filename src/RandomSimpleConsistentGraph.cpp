//
// Created by os8 on 10.05.18.
//

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "RandomSimpleConsistentGraph.h"

RandomSimpleConsistentGraph::RandomSimpleConsistentGraph() {
    srand(time(0));

    int numberOfVertices = rand() % 10 + 3;                                                                  //restrictions for tests
    int numberOfEdges = rand() % (numberOfVertices - 1) * (numberOfVertices - 2) / 2 + (numberOfVertices - 1);

    m_adjacencyMatrix = new AdjacencyMatrix(numberOfVertices, numberOfEdges);

    int firstVerticle;
    int secondVerticle;

    for(int i = 0; i < numberOfEdges; i++) {
        do{
            firstVerticle = rand() % numberOfVertices;
            secondVerticle = rand() % numberOfVertices;
        }
        while(firstVerticle == secondVerticle || m_adjacencyMatrix->DoesEdgeExist(firstVerticle, secondVerticle));

        m_adjacencyMatrix->MakeEdge(firstVerticle, secondVerticle);
    }

    m_edgeWeights = new std::vector<int>;

    for(int i = 0; i < numberOfEdges; i++) {
        int weight = rand() % 10 + 1;
        m_edgeWeights->push_back(weight);
    }
}

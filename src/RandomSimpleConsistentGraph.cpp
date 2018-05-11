//
// Created by os8 on 10.05.18.
//

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>
#include "RandomSimpleConsistentGraph.h"

RandomSimpleConsistentGraph::RandomSimpleConsistentGraph() {
    srand(time(0));

    int numberOfVertices = /*rand() % 10 + 3;*/ 6;                                                                  //restrictions for tests
    int numberOfEdges = /*rand() % (numberOfVertices - 1) * (numberOfVertices - 2) / 2 + (numberOfVertices - 1);*/ 8;

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


std::vector <int> RandomSimpleConsistentGraph::Components() {
    int componentNumber = -1;
    std::vector <int> componentsOfVerticles(m_adjacencyMatrix->GetNumberOfVertices(), -1);

    for(int i = 0; i < componentsOfVerticles.size(); i++) {
        if(componentsOfVerticles[i] == -1) {
            componentNumber++;
            componentsOfVerticles[i] = componentNumber;
            Components_R(componentNumber, i, componentsOfVerticles);
        }
    }

    return componentsOfVerticles;
}

void RandomSimpleConsistentGraph::Components_R(const int componentNumber, const int index, std::vector<int> &componentsOfVerticles) {
    std::vector<int> neighbours;
    FindNeighbors(index, neighbours);
    for(int i = 0; i < neighbours.size(); i++) {
        if(componentsOfVerticles[neighbours[i]] == -1) {
            componentsOfVerticles[neighbours[i]] = componentNumber;
            Components_R(componentNumber, neighbours[i], componentsOfVerticles);
        }
    }
}

int RandomSimpleConsistentGraph::NumberOfComponents() {
    std::vector <int> ComponentsOfVerticles = Components();
    int numberOfComponents = 1;
    int acctualComponent = ComponentsOfVerticles[0];

    for(int i = 1; i < ComponentsOfVerticles.size(); i++)
    {
        if(ComponentsOfVerticles[i] != acctualComponent) {
            acctualComponent = ComponentsOfVerticles[i];
            numberOfComponents++;
        }
    }

    return numberOfComponents;
}

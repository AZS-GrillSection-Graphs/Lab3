#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <iostream>
#include <algorithm>
#include "RandomSimpleConsistentGraph.h"

RandomSimpleConsistentGraph::RandomSimpleConsistentGraph() {
    srand(time(0));

    int numberOfVertices = rand() % 10 + 3;                                     //restrictions for tests
    int numberOfEdges = rand() % (numberOfVertices - 1) * (numberOfVertices - 2) / 2 + (numberOfVertices - 1);

    m_incidenceMatrix = new IncidenceMatrix(numberOfVertices, numberOfEdges);
    RandomlyFillAdjacencyMatrix(numberOfVertices, numberOfEdges);

    m_edgeWeights = new std::vector<int>;
    GenerateRandomWeights(numberOfEdges);
}

void RandomSimpleConsistentGraph::GenerateRandomWeights(int numberOfEdges) const {
    for(int i = 0; i < numberOfEdges; i++) {
        int weight = rand() % 10 + 1;
        m_edgeWeights->push_back(weight);
    }
}

void RandomSimpleConsistentGraph::RandomlyFillAdjacencyMatrix(int numberOfVertices, int numberOfEdges) {
    do {
        m_incidenceMatrix->ResetMatrix();

        int firstVerticle;
        int secondVerticle;

        for(int i = 0; i < numberOfEdges; i++) {
            do{
                firstVerticle = rand() % numberOfVertices;
                secondVerticle = rand() % numberOfVertices;
            }
            while(firstVerticle == secondVerticle || m_incidenceMatrix->DoesEdgeExist(firstVerticle, secondVerticle));

            m_incidenceMatrix->MakeEdge(firstVerticle, secondVerticle);
        }
    } while(NumberOfComponents() != 1);
}

std::vector <int> RandomSimpleConsistentGraph::Components() {
    int componentNumber = -1;
    std::vector <int> componentsOfVerticles(m_incidenceMatrix->GetNumberOfVertices(), -1);

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
    std::vector <int> componentsOfVerticles = Components();
    std::sort(componentsOfVerticles.begin(), componentsOfVerticles.end());
    int numberOfComponents = 1;
    int acctualComponent = componentsOfVerticles[0];

    for(int i = 1; i < componentsOfVerticles.size(); i++)
    {
        if(componentsOfVerticles[i] != acctualComponent) {
            acctualComponent = componentsOfVerticles[i];
            numberOfComponents++;
        }
    }

    return numberOfComponents;
}

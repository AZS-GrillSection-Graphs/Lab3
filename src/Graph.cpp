//
// Created by os8 on 10.05.18.
//

#include <iostream>
#include <stdio.h>
#include "Graph.h"


void Graph::Print() const {
    m_adjacencyMatrix->Print();

    std::cout << "\nWeights:\n";
    for(int i = 0; i < m_edgeWeights->size(); i++)
        std::cout << i << ":" << (*m_edgeWeights)[i] << "  ";
    std::cout << std::endl;
}

Graph::~Graph() {
    delete m_adjacencyMatrix;
    delete m_edgeWeights;
}

void Graph::DijkstraWithPrint(const int chosenVertex) {
    std::vector<int> Q;
    std::vector<int> S;
    std::vector<bool> QS;                   //if vetrex belongs to S - true
    std::vector<int> costArray;
    std::vector<int> predecessorsArray;

    DijkstraInitialization(Q, costArray, predecessorsArray, QS, chosenVertex);

    while(S.size() != m_adjacencyMatrix->GetNumberOfVertices()) {
        int nearestVertex = NearestVertex(QS, costArray);
        S.push_back(nearestVertex);
        QS[nearestVertex] = true;

        std::vector<int> neighbors;
        FindNeighbors(nearestVertex, neighbors);

        for(int i = 0; i < neighbors.size(); i++)
            Relax(costArray, predecessorsArray, nearestVertex, neighbors[i]);
    }

    PrintPaths(chosenVertex, costArray, predecessorsArray);
}

void Graph::FindNeighbors(int nearestVertex, std::vector<int> &neighbors) const {
    for(int i = 0; i < m_adjacencyMatrix->GetNumberOfVertices(); i++)
            if(m_adjacencyMatrix->DoesEdgeExist(nearestVertex, i))
                neighbors.push_back(i);
}

int Graph::NearestVertex(const std::vector<bool> &QS, const std::vector<int> &costArray) const {
    int nearestVertex = -1;
    for(int i = 0; i < costArray.size(); i++)
            if(!QS[i]) {
                nearestVertex = i;
                break;
            }

    for(int i = 0; i < costArray.size(); i++)
            if(!QS[i] && costArray[nearestVertex] > costArray[i])
                nearestVertex = i;

    return nearestVertex;
}

void Graph::DijkstraInitialization(std::vector<int> &Q, std::vector<int> &costArray, std::vector<int> &predecessorsArray, std::vector<bool> &QS, const int chosenVertex) {
    for(int i = 0; i < m_adjacencyMatrix->GetNumberOfVertices(); i++) {
        Q.push_back(i);
        QS.push_back(false);
        costArray.push_back(9999);
        predecessorsArray.push_back(-1);
    }

    costArray[chosenVertex] = 0;

}

void Graph::Relax(std::vector<int> &costArray, std::vector<int> &predecessorsArray, const int firstVertex, const int secondVertex) {
    int indexOfEdge = m_adjacencyMatrix->GetIndexOfEdge(firstVertex, secondVertex);

    if(costArray[secondVertex] > costArray[firstVertex] + (*m_edgeWeights)[indexOfEdge]) {
        costArray[secondVertex] = costArray[firstVertex] + (*m_edgeWeights)[indexOfEdge];
        predecessorsArray[secondVertex] = firstVertex;
    }
}

void Graph::PrintPaths(const int chosenVertex, std::vector<int> &costArray, std::vector<int> &predecessorsArray) const {
    std::cout << std::endl;
    for(int i = 0; i < m_adjacencyMatrix->GetNumberOfVertices(); i++) {
        printf("Path to vertex %2d (cost:%2d): ", i, costArray[i]);

        int currentVertex = i;

        if(costArray[i] == 0) {
            std::cout << "empty path";
            currentVertex = -1;
        }

        while(currentVertex > -1) {
                if(predecessorsArray[currentVertex] != chosenVertex)
                    std::cout << predecessorsArray[currentVertex] << "-";
                else {
                    std::cout << predecessorsArray[currentVertex];
                    break;
                }

            currentVertex = predecessorsArray[currentVertex];
        }

        std::cout << std::endl;
    }

}

void Graph::PrintCostMatrix(){
    std::vector<std::vector<int>> costMatrix = SetCostMatrix();

    std::cout << "\nDistance Matrix:\n";

    for(int i = 0; i < costMatrix.size(); i++) {
        for(int j = 0; j < costMatrix[i].size(); j++)
            printf("%-2d  ", costMatrix[i][j]);

        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> Graph::SetCostMatrix() {
    std::vector<std::vector<int>> costMatrix;

    for(int i = 0; i < m_adjacencyMatrix->GetNumberOfVertices(); i++)
        costMatrix.push_back(Dijkstra(i));

    return costMatrix;
}

std::vector<int> Graph::Dijkstra(const int chosenVertex) {
    std::vector<int> Q;
    std::vector<int> S;
    std::vector<bool> QS;                   //if vetrex belongs to S - true
    std::vector<int> costArray;
    std::vector<int> predecessorsArray;

    DijkstraInitialization(Q, costArray, predecessorsArray, QS, chosenVertex);

    while(S.size() != m_adjacencyMatrix->GetNumberOfVertices()) {
        int nearestVertex = NearestVertex(QS, costArray);
        S.push_back(nearestVertex);
        QS[nearestVertex] = true;

        std::vector<int> neighbors;
        FindNeighbors(nearestVertex, neighbors);

        for(int i = 0; i < neighbors.size(); i++)
            Relax(costArray, predecessorsArray, nearestVertex, neighbors[i]);
    }

    return costArray;
}




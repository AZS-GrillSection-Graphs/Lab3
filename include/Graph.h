//
// Created by os8 on 10.05.18.
//

#ifndef GRAPHS3_GRAPH_H
#define GRAPHS3_GRAPH_H


#include "AdjacencyMatrix.h"

class Graph {
public:
    explicit Graph(AdjacencyMatrix * adjacencyMatrix, std::vector<int> * edgeWeights) : m_adjacencyMatrix(adjacencyMatrix), m_edgeWeights(edgeWeights) {}
    Graph() = default;
    ~Graph();

    void Print() const;
    void DijkstraWithPrint(const int chosenVertex);
    void PrintCostMatrix();

protected:
    AdjacencyMatrix * m_adjacencyMatrix;
    std::vector<int> * m_edgeWeights;

    void DijkstraInitialization(std::vector<int> &Q, std::vector<int> &costArray, std::vector<int> &predecessorsArray, std::vector<bool> &QS, const int chosenVertex);

    int NearestVertex(const std::vector<bool> &QS, const std::vector<int> &costArray) const;

    void FindNeighbors(int nearestVertex, std::vector<int> &neighbors) const;

    void Relax(std::vector<int> &costArray, std::vector<int> &predecessorsArray, const int firstVertex, const int secondVertex);

    void PrintPaths(const int chosenVertex, std::vector<int> &costArray, std::vector<int> &predecessorsArray) const;

    std::vector<std::vector<int>> SetCostMatrix();

    std::vector<int> Dijkstra(const int chosenVertex);
};


#endif //GRAPHS3_GRAPH_H

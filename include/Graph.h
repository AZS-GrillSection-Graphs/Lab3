//
// Created by os8 on 10.05.18.
//

#ifndef GRAPHS3_GRAPH_H
#define GRAPHS3_GRAPH_H


#include <vector>
#include "IncidenceMatrix.h"

class Graph {
public:
    explicit Graph(IncidenceMatrix * adjacencyMatrix, std::vector<int> * edgeWeights) : m_incidenceMatrix(adjacencyMatrix), m_edgeWeights(edgeWeights) {}
    Graph() = default;
    ~Graph();

    void Print() const;
    void DrawOnScreen() const;
    void DijkstraWithPrint(const int chosenVertex);
    void PrintCostMatrix();
    int FindGraphCenter();
    int FindMinimaxGraphCenter();
    void PrimWithPrint(const int choosenVertex);

protected:
    IncidenceMatrix * m_incidenceMatrix;
    std::vector<int> * m_edgeWeights;

    void FindNeighbors(int nearestVertex, std::vector<int> &neighbors) const;
    int NearestVertex(const std::vector<bool> &QS, const std::vector<int> &costArray) const;
    void PrintPaths(const int chosenVertex, std::vector<int> &costArray, std::vector<int> &predecessorsArray) const;
    void DijkstraInitialization(std::vector<int> &Q, std::vector<int> &costArray, std::vector<int> &predecessorsArray, std::vector<bool> &QS, const int chosenVertex);
    void Relax(std::vector<int> &costArray, std::vector<int> &predecessorsArray, const int firstVertex, const int secondVertex);
    std::vector<std::vector<int>> SetCostMatrix();
    std::vector<int> Dijkstra(const int chosenVertex);

    int GetLightestEdge(std::vector<int> &visited, std::vector<std::vector<int>> &adjacencyMatrix);
    void UpdateMST(std::vector<std::vector<int>> &minimalSpanningTree, const int *connectedVertices);
    bool isVisited(std::vector<int> &visited, const int vertex) const;
    void printMST(const std::vector<std::vector<int>> &minimalSpanningTree) const;
    void SaveMSTToFile(const char string[22], std::vector<std::vector<int>> vector1);
    void DrawMSTOnScreen();
};


#endif //GRAPHS3_GRAPH_H

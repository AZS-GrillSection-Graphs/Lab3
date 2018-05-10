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

protected:
    AdjacencyMatrix * m_adjacencyMatrix{};
    std::vector<int> * m_edgeWeights;

};


#endif //GRAPHS3_GRAPH_H

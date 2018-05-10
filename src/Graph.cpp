//
// Created by os8 on 10.05.18.
//

#include <iostream>
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

//
// Created by os8 on 10.05.18.
//

#include "AdjacencyMatrix.h"

#include <iostream>

AdjacencyMatrix::AdjacencyMatrix(const int numberOfVerices, const int numberOfEdges) {
    for(int i = 0; i < numberOfVerices; i++) {
        std::vector<int> column;
        for(int j = 0; j < numberOfEdges; j++)
            column.push_back(0);

        m_matrix.push_back(column);
    }
}

void AdjacencyMatrix::Print() const {
    for(int i = 0; i < m_matrix.size(); i++) {
        for(int j = 0; j < m_matrix[i].size(); j++)
            std::cout << m_matrix[i][j] << " ";

        std::cout << std::endl;
    }
}

bool AdjacencyMatrix::DoesEdgeExist(const int firstVerticle, const int secondVerticle) const {
    for(int i = 0; i < m_matrix[firstVerticle].size(); i++)
        if(m_matrix[firstVerticle][i])
            if(m_matrix[secondVerticle][i])
                return true;

    return false;
}

void AdjacencyMatrix::MakeEdge(const int firstVerticle, const int secondVerticle) {
    int notConnectedEdge = FindNotConnectedEdge();

    if(notConnectedEdge >= 0) {
        m_matrix[firstVerticle][notConnectedEdge] = 1;
        m_matrix[secondVerticle][notConnectedEdge] = 1;
    }
}

int AdjacencyMatrix::FindNotConnectedEdge() const {
    bool isClear = true;
    int notConnectedEdge = -1;

    int numberOfVertices = static_cast<int>(m_matrix.size());
    int numberOfEdges = static_cast<int>(m_matrix[0].size());

    for(int i = 0; i < numberOfEdges; i++) {
        for(int j = 0; j < numberOfVertices; j++)
            if(m_matrix[j][i])
                isClear = false;

        if(isClear) {
            notConnectedEdge = i;
            break;
        }
        else
            isClear = true;
    }

    return notConnectedEdge;
}

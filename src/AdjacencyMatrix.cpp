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
    std::cout << "V\\E\t";
    for(int j = 0; j < m_matrix[0].size(); j++)
        std::cout << j << " \t";
    std::cout << std::endl;
    std::cout << std::endl;

    for(int i = 0; i < m_matrix.size(); i++) {
        std::cout << i << ":\t";

        for(int j = 0; j < m_matrix[i].size(); j++)
            std::cout << m_matrix[i][j] << "\t";

        std::cout << std::endl;
    }
}

bool AdjacencyMatrix::DoesEdgeExist(const int firstVertex, const int secondVertex) const {
    if(firstVertex == secondVertex)
        return false;

    for(int i = 0; i < m_matrix[firstVertex].size(); i++)
        if(m_matrix[firstVertex][i])
            if(m_matrix[secondVertex][i])
                return true;

    return false;
}

void AdjacencyMatrix::MakeEdge(const int firstVertex, const int secondVertex) {
    int notConnectedEdge = FindNotConnectedEdge();

    if(notConnectedEdge >= 0) {
        m_matrix[firstVertex][notConnectedEdge] = 1;
        m_matrix[secondVertex][notConnectedEdge] = 1;
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

int AdjacencyMatrix::GetIndexOfEdge(const int firstVertex, const int secondVertex) const {
    if(!DoesEdgeExist(firstVertex, secondVertex))
        return -1;

    for(int i = 0; i < m_matrix[firstVertex].size(); i++)
        if(m_matrix[firstVertex][i])
            if(m_matrix[secondVertex][i])
                return i;
}

void AdjacencyMatrix::RandomizeEdges() {
    int firstEdge = rand() % m_matrix[0].size();
    int secondEdge = rand() % m_matrix[0].size();

    if(firstEdge == secondEdge)
        return;

    //first
    int startOfFirstEdge = GetStartOfEdge(firstEdge);
    int endOfFirstEdge = GetEndOfEdge(firstEdge, startOfFirstEdge);

    //second
    int startOfSecondEdge = GetStartOfEdge(secondEdge);
    int endOfSecondEdge = GetEndOfEdge(secondEdge, startOfSecondEdge);

    if(DoesEdgeExist(startOfFirstEdge, endOfSecondEdge) || startOfFirstEdge == endOfSecondEdge)
        return;

    if(DoesEdgeExist(startOfFirstEdge, endOfSecondEdge) || startOfSecondEdge == endOfFirstEdge)
        return;

    m_matrix[endOfFirstEdge][firstEdge] = 0;
    m_matrix[endOfSecondEdge][firstEdge] = 1;

    m_matrix[endOfSecondEdge][secondEdge] = 0;
    m_matrix[endOfFirstEdge][secondEdge] = 1;
}

int AdjacencyMatrix::GetEndOfEdge(int firstEdge, int startOfFirstEdge) const {
    int endOfFirstEdge;
    for(int i = startOfFirstEdge + 1; i < m_matrix.size(); i++) {
        if(m_matrix[i][firstEdge]) {
            endOfFirstEdge = i;
            break;
        }
    }
    return endOfFirstEdge;
}

int AdjacencyMatrix::GetStartOfEdge(int firstEdge) const {
    int startOfFirstEdge;
    for(int i = 0; i < m_matrix.size(); i++) {
        if(m_matrix[i][firstEdge]) {
            startOfFirstEdge = i;
            break;
        }
    }
    return startOfFirstEdge;
}

void AdjacencyMatrix::ResetMatrix() {
    for(int i = 0; i < m_matrix.size(); i++) {
        for(int j = 0; j < m_matrix[i].size(); j++)
            m_matrix[i][j] = 0;
    }
}

int *AdjacencyMatrix::GetConnectedVerticesBy(const int edgeNumber) const {
    auto * vertices = new int[2];

    for(int i = 0; i < m_matrix.size(); ++i) {
        if ( m_matrix[i][edgeNumber] ) {
            *vertices = i;
            vertices++;
        }
    }
    vertices -= 2;
    return vertices;
}

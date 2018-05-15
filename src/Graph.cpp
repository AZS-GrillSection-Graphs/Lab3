//
// Created by os8 on 10.05.18.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include "Graph.h"

void Graph::Print() const {
    m_incidenceMatrix->Print();

    std::cout << "\nWeights:\n";
    for (int i = 0; i < m_edgeWeights->size(); i++)
        std::cout << i << ":" << ( *m_edgeWeights )[i] << "  ";
    std::cout << std::endl;
}

Graph::~Graph() {
    delete m_incidenceMatrix;
    delete m_edgeWeights;
}

void Graph::DijkstraWithPrint(const int chosenVertex) {
    std::vector<int> Q;
    std::vector<int> S;
    std::vector<bool> QS;                   //if vetrex belongs to S - true
    std::vector<int> costArray;
    std::vector<int> predecessorsArray;

    DijkstraInitialization(Q, costArray, predecessorsArray, QS, chosenVertex);

    while (S.size() != m_incidenceMatrix->GetNumberOfVertices()) {
        int nearestVertex = NearestVertex(QS, costArray);
        S.push_back(nearestVertex);
        QS[nearestVertex] = true;

        std::vector<int> neighbors;
        FindNeighbors(nearestVertex, neighbors);

        for (int i = 0; i < neighbors.size(); i++)
            Relax(costArray, predecessorsArray, nearestVertex, neighbors[i]);
    }

    PrintPaths(chosenVertex, costArray, predecessorsArray);
}

void Graph::FindNeighbors(int nearestVertex, std::vector<int> &neighbors) const {
    for (int i = 0; i < m_incidenceMatrix->GetNumberOfVertices(); i++)
        if ( m_incidenceMatrix->DoesEdgeExist(nearestVertex, i))
            neighbors.push_back(i);
}

int Graph::NearestVertex(const std::vector<bool> &QS, const std::vector<int> &costArray) const {
    int nearestVertex = -1;
    for (int i = 0; i < costArray.size(); i++)
        if ( !QS[i] ) {
            nearestVertex = i;
            break;
        }

    for (int i = 0; i < costArray.size(); i++)
        if ( !QS[i] && costArray[nearestVertex] > costArray[i] )
            nearestVertex = i;

    return nearestVertex;
}

void
Graph::DijkstraInitialization(std::vector<int> &Q, std::vector<int> &costArray, std::vector<int> &predecessorsArray,
                              std::vector<bool> &QS, const int chosenVertex) {
    for (int i = 0; i < m_incidenceMatrix->GetNumberOfVertices(); i++) {
        Q.push_back(i);
        QS.push_back(false);
        costArray.push_back(9999);
        predecessorsArray.push_back(-1);
    }

    costArray[chosenVertex] = 0;
}

void Graph::Relax(std::vector<int> &costArray, std::vector<int> &predecessorsArray, const int firstVertex,
                  const int secondVertex) {
    int indexOfEdge = m_incidenceMatrix->GetIndexOfEdge(firstVertex, secondVertex);

    if ( costArray[secondVertex] > costArray[firstVertex] + ( *m_edgeWeights )[indexOfEdge] ) {
        costArray[secondVertex] = costArray[firstVertex] + ( *m_edgeWeights )[indexOfEdge];
        predecessorsArray[secondVertex] = firstVertex;
    }
}

void Graph::PrintPaths(const int chosenVertex, std::vector<int> &costArray, std::vector<int> &predecessorsArray) const {
    std::cout << std::endl;
    for (int i = 0; i < m_incidenceMatrix->GetNumberOfVertices(); i++) {
        printf("Path to vertex %2d (cost:%2d): ", i, costArray[i]);

        int currentVertex = i;

        if ( costArray[i] == 0 ) {
            std::cout << "empty path";
            currentVertex = -1;
        }

        while (currentVertex > -1) {
            if ( predecessorsArray[currentVertex] != chosenVertex )
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

void Graph::PrintCostMatrix() {
    std::vector<std::vector<int>> costMatrix = SetCostMatrix();

    std::cout << "\nDistance Matrix:\n";

    for (int i = 0; i < costMatrix.size(); i++) {
        for (int j = 0; j < costMatrix[i].size(); j++)
            printf("%-2d  ", costMatrix[i][j]);

        std::cout << std::endl;
    }
}

std::vector<std::vector<int>> Graph::SetCostMatrix() {
    std::vector<std::vector<int>> costMatrix;

    for (int i = 0; i < m_incidenceMatrix->GetNumberOfVertices(); i++)
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

    while (S.size() != m_incidenceMatrix->GetNumberOfVertices()) {
        int nearestVertex = NearestVertex(QS, costArray);
        S.push_back(nearestVertex);
        QS[nearestVertex] = true;

        std::vector<int> neighbors;
        FindNeighbors(nearestVertex, neighbors);

        for (int i = 0; i < neighbors.size(); i++)
            Relax(costArray, predecessorsArray, nearestVertex, neighbors[i]);
    }

    return costArray;
}

int Graph::FindGraphCenter() {
    std::vector<std::vector<int>> costMatrix = SetCostMatrix();
    std::vector<int> verticesCostSums(costMatrix.size(), 0);

    for (int i = 0; i < costMatrix.size(); ++i) {
        std::vector<int> row = costMatrix[i];
        for (int costToVertex : row) {
            verticesCostSums[i] += costToVertex;
        }
    }
    auto centerOfGraph = std::min_element(verticesCostSums.begin(), verticesCostSums.end());
    return static_cast<int>(std::distance(verticesCostSums.begin(), centerOfGraph));
}

int Graph::FindMinimaxGraphCenter() {
    std::vector<std::vector<int>> costMatrix = SetCostMatrix();
    std::vector<int> maxLengths;

    for (std::vector<int> row : costMatrix) {
        int maxLength = 0;
        for (int costToVertex : row) {
            if ( maxLength < costToVertex )
                maxLength = costToVertex;
        }
        maxLengths.emplace_back(maxLength);
    }
    auto minimaxCenter = std::min_element(maxLengths.begin(), maxLengths.end());
    return static_cast<int>(std::distance(maxLengths.begin(), minimaxCenter));
}

void Graph::PrimWithPrint(const int choosenVertex) {
    std::vector<int> visitedVertices;
    std::vector<std::vector<int>> copyOfIncidenceMatrix = m_incidenceMatrix->CopyOfMatrix();
    const int verticesNumber = m_incidenceMatrix->GetNumberOfVertices();
    std::vector<std::vector<int>> minimalSpanningTree(verticesNumber);

    visitedVertices.emplace_back(choosenVertex);

    while (visitedVertices.size() < verticesNumber) {
        const int lightestEdge = GetLightestEdge(visitedVertices, copyOfIncidenceMatrix);
        int *connectedVertices = m_incidenceMatrix->GetConnectedVerticesBy(lightestEdge);

        if ( !isVisited(visitedVertices, connectedVertices[0]))
            visitedVertices.emplace_back(connectedVertices[0]);
        else
            visitedVertices.emplace_back(connectedVertices[1]);

        UpdateMST(minimalSpanningTree, connectedVertices);

        copyOfIncidenceMatrix[connectedVertices[0]][lightestEdge] = 0;
        copyOfIncidenceMatrix[connectedVertices[1]][lightestEdge] = 0;
        delete connectedVertices;
    }

    printMST(minimalSpanningTree);
    SaveMSTToFile("MacierzIncydencji.txt", minimalSpanningTree);
    DrawMSTOnScreen();
}

void Graph::printMST(const std::vector<std::vector<int>> &minimalSpanningTree) const {
    const int verticesNumber = minimalSpanningTree.size();
    std::cout << "Minimal Spanning Tree:\n";
    for (int vertex = 0; vertex < verticesNumber; ++vertex) {
        for (int edge = 0; edge < minimalSpanningTree[vertex].size(); ++edge)
            std::cout << minimalSpanningTree[vertex][edge] << "\t";
        std::cout << std::endl;
    }
}

void Graph::UpdateMST(std::vector<std::vector<int>> &minimalSpanningTree, const int *connectedVertices) {
    const int verticesNumber = minimalSpanningTree.size();
    for (int vertex = 0; vertex < verticesNumber; ++vertex)
            if ( vertex == connectedVertices[0] || vertex == connectedVertices[1] )
                minimalSpanningTree[vertex].emplace_back(1);
            else
                minimalSpanningTree[vertex].emplace_back(0);
}

int Graph::GetLightestEdge(std::vector<int> &visited, std::vector<std::vector<int>> &adjacencyMatrix) {
    int lightestEdge = -1;
    int minimalWeight = 10e6;
    const int edgesNumber = static_cast<const int>(m_edgeWeights->size());

    for (int vertex : visited) {
        for (int edge = 0; edge < edgesNumber; ++edge) {
            auto * connectedVertices = m_incidenceMatrix->GetConnectedVerticesBy(edge);
            if( !isVisited(visited, connectedVertices[0]) || !isVisited(visited, connectedVertices[1])) {
                if ( adjacencyMatrix[vertex][edge] && ( *m_edgeWeights )[edge] < minimalWeight ) {
                    lightestEdge = edge;
                    minimalWeight = ( *m_edgeWeights )[lightestEdge];
                }
            }
        }
    }
    return lightestEdge;
}

bool Graph::isVisited(std::vector<int> &visited, const int vertex) const {
    return find(visited.begin(), visited.end(), vertex) != visited.end();
}

void Graph::DrawOnScreen() const {
    m_incidenceMatrix->SaveToFile("MacierzIncydencji.txt");
    SaveWeightsToFile("WektorWag.txt");

    std::__cxx11::string drawing = "python3 GraphWeightsVisualization.py MacierzIncydencji.txt WektorWag.txt";
    system(drawing.c_str());
}

void Graph::SaveMSTToFile(const char fileName[22], std::vector<std::vector<int>> MST) {
    std::ofstream file;

    if (!file.is_open())
    {
        file.open(fileName, std::ios::out);

        if(!file)
        {
            std::cerr << "Failed to open " << fileName << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    file << "MI" << std::endl;

    const int verticesNumber = MST.size();
    for(int i = 0; i < MST.size(); i++) {
        for(int j = 0; j < MST[i].size(); j++)
            file << MST[i][j] << "\t";
        file << std::endl;
    }

    file.close();
}

void Graph::DrawMSTOnScreen() {
    std::__cxx11::string drawing = "python3 GraphVisualization.py MacierzIncydencji.txt";
    system(drawing.c_str());
}

void Graph::SaveWeightsToFile(const char *fileName) const {
        std::ofstream file;

        if (!file.is_open())
        {
            file.open(fileName, std::ios::out);
            if(!file)
            {
                std::cerr << "Failed to open " << fileName << std::endl;
                exit(EXIT_FAILURE);
            }
        }

        for(int i = 0; i < m_edgeWeights->size(); i++) {
                file << (*m_edgeWeights)[i] << "\n";
            file << std::endl;
        }

        file.close();

}

//
// Created by os8 on 10.05.18.
//

#include <iostream>
#include <algorithm>
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

int Graph::FindGraphCenter() {
    std::vector<std::vector<int>> costMatrix = SetCostMatrix();
    std::vector<int> verticesCostSums(costMatrix.size(), 0);

    for(int i=0; i<costMatrix.size(); ++i) {
        std::vector<int> row = costMatrix[i];
        for(int costToVertex : row) {
            verticesCostSums[i] += costToVertex;
        }
    }
    auto centerOfGraph = std::min_element(verticesCostSums.begin(), verticesCostSums.end());
    return static_cast<int>(std::distance(verticesCostSums.begin(), centerOfGraph));
}

int Graph::FindMinimaxGraphCenter() {
    std::vector<std::vector<int>> costMatrix = SetCostMatrix();
    std::vector<int> maxLengths;

    for(std::vector<int> row : costMatrix) {
        int maxLength = 0;
        for(int costToVertex : row) {
            if( maxLength < costToVertex)
                maxLength = costToVertex;
        }
        maxLengths.emplace_back(maxLength);
    }
    auto minimaxCenter = std::min_element(maxLengths.begin(), maxLengths.end());
    return static_cast<int>(std::distance(maxLengths.begin(), minimaxCenter));
}

void Graph::PrimWithPrint(const int choosenVertex) {
    std::vector<int> visitedEdges;
    std::vector<std::vector<int>> copyOfAdjacencyMatrix = m_adjacencyMatrix->CopyOfMatrix();
    const int verticesNumber = m_adjacencyMatrix->GetNumberOfVertices();
    std::vector<std::vector<int>> minimalSpanningTree(verticesNumber);

    visitedEdges.emplace_back(choosenVertex);

    while(visitedEdges.size() < verticesNumber) {
        const int lightestEdge  = GetLightestEdge(visitedEdges, copyOfAdjacencyMatrix);
        int* connectedVertices = m_adjacencyMatrix->GetConnectedVerticesBy(lightestEdge);

        std::cout << "Lekka krawedz: " << lightestEdge << "  Vertexy: "<< connectedVertices[0] << ","
                  << connectedVertices[1] << std::endl;

        // Dodajemy połączony tą krawędzią wierzchołek
        if(std::find(visitedEdges.begin(), visitedEdges.end(), connectedVertices[0]) == visitedEdges.end())
            visitedEdges.emplace_back(connectedVertices[0]);
        else
            visitedEdges.emplace_back(connectedVertices[1]);

        // Dodajemy połaczenie do drzewa
        for(int vertex = 0; vertex < verticesNumber; ++vertex)
            if(vertex == connectedVertices[0] || vertex == connectedVertices[1])
                minimalSpanningTree[vertex].emplace_back(1);
            else
                minimalSpanningTree[vertex].emplace_back(0);

        // Usuwamy połączenie z kopii macierzy incydencji
        copyOfAdjacencyMatrix[connectedVertices[0]][lightestEdge] = 0;
        copyOfAdjacencyMatrix[connectedVertices[1]][lightestEdge] = 0;
        delete connectedVertices;
    }

    std::cout << "Minimal Spanning Tree:\n";
    for(int vertex=0; vertex<verticesNumber; ++vertex) {
        for(int edge=0; edge<minimalSpanningTree[vertex].size(); ++edge)
            std::cout << minimalSpanningTree[vertex][edge] << "\t";
        std::cout << std::endl;
    }
}

int Graph::GetLightestEdge(std::vector<int> &visited, std::vector<std::vector<int>> &adjacencyMatrix) {
    int lightestEdge = -1;
    int minimalWeight = 1000000;
    const int edgesNumber = static_cast<const int>(m_edgeWeights->size());

    for(int vertex : visited) {
        for(int edge=0; edge < edgesNumber; ++edge) {
            if(std::find(visited.begin(), visited.end(), edge) == visited.end()) {
                if(adjacencyMatrix[vertex][edge] && (*m_edgeWeights)[edge] < minimalWeight) {
                    lightestEdge = edge;
                    minimalWeight = (*m_edgeWeights)[lightestEdge];
                }
            }
        }
    }
    return lightestEdge;
}

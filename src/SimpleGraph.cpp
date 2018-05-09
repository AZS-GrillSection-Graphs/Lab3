#include "SimpleGraph.h"
#include <sstream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stack>

SimpleGraph::SimpleGraph(std::string  numberSeries) {
    try{
        if(!IsGraphicSeries(numberSeries))
            throw "Provided number series is not a graphic series!";
    }catch(const char * exceptionText) {
        std::cerr << exceptionText << std::endl;
        exit(EXIT_FAILURE);
    }

    std::vector<int> vertexLinks = getNumbers(numberSeries);
    m_graphRepr = new AdjacencyList(vertexLinks.size());

    ConvertFromNumberSeries(vertexLinks);
}

bool SimpleGraph::IsGraphicSeries(std::string stringToCheck) {
    std::stringstream stream(stringToCheck);
    std::vector<int> seriesToCheck = getNumbers(stringToCheck);

    while(true) {
        if(*seriesToCheck.begin() == 0 && *(--seriesToCheck.end()) == 0)
            return true;

        if(*seriesToCheck.begin() >= seriesToCheck.size() || *(--seriesToCheck.end()) < 0)
            return false;

        int degreeOfVertex = seriesToCheck[0];
        for(int i = 1; i <= degreeOfVertex; ++i)
            --seriesToCheck[i];
        seriesToCheck[0] = 0;

        std::sort(seriesToCheck.begin(), seriesToCheck.end(), std::greater<int>());
    }
}

std::vector<int> SimpleGraph::getNumbers(const std::string numberSeries) {
    std::stringstream stream(numberSeries);
    std::vector<int> vertexLinks;

    int number;
    while(stream >> number) {
            vertexLinks.push_back(number);
    }

    std::sort(vertexLinks.begin(), vertexLinks.end(), std::greater<int>());
    return vertexLinks;
}

void SimpleGraph::ConvertFromNumberSeries(std::vector<int> &vertexLinks) {
    const int verticesNumber = static_cast<const int>(vertexLinks.size());

    for(int vertex=0; vertex < verticesNumber - 1; ++vertex) {
        int vertexToLink = vertex+1;

        while(vertexLinks[vertex]) {
            while(vertexLinks[vertexToLink] == 0 || m_graphRepr->AreVerticesConnected(vertex, vertexToLink)) {
                if(vertexToLink < verticesNumber-1)
                    vertexToLink++;
                else
                    break;
            }
            if(vertexToLink == verticesNumber-1 && !m_graphRepr->AreVerticesConnected(vertex, vertexToLink)) {
                --vertexLinks[vertex];
                --vertexLinks[vertexToLink];
                m_graphRepr->MakeConnectBetween(vertex, vertexToLink);
            } else if(m_graphRepr->AreVerticesConnected(vertex, vertexToLink)) {
                if(vertexLinks[vertex]%2) {
                    // wielokrotna
                    --vertexLinks[vertex];
                    --vertexLinks[vertexToLink];
                    m_graphRepr->MakeConnectBetween(vertex, vertexToLink);
                    RandomizeGraph(vertex, vertexToLink);
                } else {
                    // petla
                    --vertexLinks[vertex];
                    --vertexLinks[vertex];
                    m_graphRepr->MakeConnectBetween(vertex, vertex);
                    RandomizeGraph(vertex, vertex);
                }
            } else {
                // normal case
                --vertexLinks[vertex];
                --vertexLinks[vertexToLink];
                m_graphRepr->MakeConnectBetween(vertex, vertexToLink);
            }
        }
    }

    const int lastVertex = verticesNumber-1;
    while(vertexLinks[lastVertex]) {
        --vertexLinks[lastVertex];
        --vertexLinks[lastVertex];
        m_graphRepr->MakeConnectBetween(lastVertex, lastVertex);
        RandomizeGraph(lastVertex, lastVertex);
    }

}

void SimpleGraph::DoesHamiltonCycleExist() const {
    std::stack <int> vertices;
    const int numberOfVertices = static_cast<const int>(m_graphRepr->GetData().size());
    std::vector <bool> visited(numberOfVertices);

    if(numberOfVertices < 20)
        Hamilton_R(numberOfVertices, 0, visited, vertices);
    else
        std::cout << "Graph is too big." << std::endl;

}

void SimpleGraph::Hamilton_R(const int verticesNumber, int vertex, std::vector<bool> &visited,
                             std::stack<int> &vertices) const {
    vertices.push(vertex);
    if(vertices.size() >= verticesNumber) {
        bool testCycle = false;
        std::vector <int> & neighbours = m_graphRepr->GetData()[vertex];
        for(int neighborIndex = 0; neighborIndex < neighbours.size(); neighborIndex++) {
            if(neighbours[neighborIndex] == 0) {
                testCycle = true;
                break;
            }
        }
        if(testCycle) {
            std::cout << "Hamiltonian Cycle: " << std::endl;
        }

        if(testCycle) {
            std::cout << "1 ";
            PrintStack(vertices);
        }

    } else {
        visited[vertex] = true;

        std::vector <int> & neighbours = m_graphRepr->GetData()[vertex];
        for(int neighborIndex = 0; neighborIndex < neighbours.size(); neighborIndex++)
            if(!visited[neighbours[neighborIndex]])
                Hamilton_R(verticesNumber, neighbours[neighborIndex], visited, vertices);

        visited[vertex] = false;
    }
    vertices.pop();
}

void SimpleGraph::PrintStack(std::stack<int> &stack) const {
    std::stack <int> stackCopy(stack);

    while(stackCopy.size() > 0) {
        std::cout << stackCopy.top() + 1 << " ";
        stackCopy.pop();
    }
    std::cout << std::endl;
}

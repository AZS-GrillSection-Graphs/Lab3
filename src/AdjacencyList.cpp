#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iterator>


AdjacencyList::AdjacencyList(std::ifstream &inputFile) {
    std::vector<std::vector <int> >row;
    std::string line;

    while(getline(inputFile, line))
    {
        std::istringstream streamLine(line);
        std::vector<int> col;

        while(!streamLine.eof())
        {
            int value;
            streamLine >> value;

            if(streamLine.fail())
                break;

            col.push_back(value);
        }

        m_adjList.push_back(col);
    }
    m_initials = "LS";
}

void AdjacencyList::Print() const {
    std::cout << "Adjacency list:\n";
    const int verticesNumber = m_adjList.size();
    for(int i = 0; i < verticesNumber; ++i)
    {
        const int linksNumber = m_adjList[i].size();
        std::cout << i+1 << ": ";
        if(linksNumber)
            for(int j = 0; j < linksNumber; ++j)
                std::cout << m_adjList[i][j] + 1 << " ";
        else
            std::cout << 0 << " ";
        std::cout << std::endl;
    }
}

AdjacencyList::AdjacencyList(const int verticesNumber) {
    srand(time(nullptr));
    for(int i=0; i<verticesNumber; ++i) {
        std::vector<int> row;
        m_adjList.push_back(row);
    }
    m_initials = "LS";
}

void AdjacencyList::MakeConnectBetween(const int firstVertex, const int secondVertex) {
    m_adjList[firstVertex].push_back(secondVertex);
    m_adjList[secondVertex].push_back(firstVertex);
}

void AdjacencyList::DeleteEdge(const int firstVertex, const int secondVertex) {
    m_adjList[firstVertex].erase(
            std::find(m_adjList[firstVertex].begin(), m_adjList[firstVertex].end(), secondVertex));
    m_adjList[secondVertex].erase(
            std::find(m_adjList[secondVertex].begin(), m_adjList[secondVertex].end(), firstVertex));
}

bool AdjacencyList::AreVerticesConnected(const int firstVertex, const int secondVertex) const {
    bool firstInSecondPresent = std::find(m_adjList[secondVertex].begin(), m_adjList[secondVertex].end(), firstVertex)
                         != m_adjList[secondVertex].end();

    bool secondInFirstPresent = std::find(m_adjList[firstVertex].begin(), m_adjList[firstVertex].end(), secondVertex)
                         != m_adjList[firstVertex].end();

    return firstInSecondPresent && secondInFirstPresent;
}

void AdjacencyList::SaveToFile(const char *fileName) const {
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

    file << m_initials << std::endl;

    const int verticesNumber = m_adjList.size();
    for(int i = 0; i < verticesNumber; ++i)
    {
        const int linksNumber = m_adjList[i].size();
        for(int j = 0; j < linksNumber; ++j)
            file << m_adjList[i][j] + 1 << " ";
        file << std::endl;
    }

    file.close();
}

void AdjacencyList::Convert() const {
    ////////// Macierz sasiedztwa //////////
    std::ofstream adjMatrixFile;

    if (!adjMatrixFile.is_open())
    {
        adjMatrixFile.open("MacierzSasiedztwa.txt", std::ios::out);

        if(!adjMatrixFile)
        {
            std::cerr << "Failed to open " << "MacierzSasiedztwa.txt" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    const int verticesNumber = m_adjList.size();
    adjMatrixFile << "MS" << std::endl;

    int ** adjMatrix = new int * [verticesNumber];
    for(int i = 0; i < verticesNumber; ++i) {
        adjMatrix[i] = new int [verticesNumber];
        for(int j = 0; j < verticesNumber; ++j)
            adjMatrix[i][j] = 0;
    }

    for(int i = 0; i < verticesNumber; ++i) {
        if(m_adjList[i].size())
            for(int j = 0; j < m_adjList[i].size(); ++j)
                adjMatrix[i][m_adjList[i][j]] = 1;
        else
            adjMatrix[i][i] = 1;

        for(int j = 0; j < verticesNumber; ++j)
            adjMatrixFile << adjMatrix[i][j] << " ";
        adjMatrixFile << std::endl;
    }
    adjMatrixFile.close();


    ////////// Macierz incydencji //////////
    std::ofstream incMatrixFile;

    if (!incMatrixFile.is_open())
    {
        incMatrixFile.open("MacierzIncydencji.txt", std::ios::out);

        if(!incMatrixFile)
        {
            std::cerr << "Failed to open " << "MacierzIncydencji.txt" << std::endl;
            exit(EXIT_FAILURE);
        }
    }


    int numOfEdges = 0;
    incMatrixFile << "MI" << std::endl;
    for(int i = 0; i < verticesNumber; ++i)
        for(int j = i; j < verticesNumber; ++j)
            numOfEdges += adjMatrix[i][j];

    int ** incMatrix = new int * [numOfEdges];
    for(int i = 0; i < numOfEdges; ++i) {
        incMatrix[i] = new int [verticesNumber];
        for(int j = 0; j < verticesNumber; ++j)
            incMatrix[i][j] = 0;
    }

    int edge = 0;

    for(int i = 0; i < verticesNumber; ++i) {
        for(int j = i; j < verticesNumber; ++j) {
            if(adjMatrix[i][j] == 1)
            {
                incMatrix[edge][i] = 1;
                incMatrix[edge][j] = 1;
                ++edge;
            }
        }
    }

    for(int j = 0; j < verticesNumber; ++j) {
        for(int i = 0; i < edge; ++i) {
            if(incMatrix[i][j] == 1)
                incMatrixFile << "1 ";
            else
                incMatrixFile << "0 ";
        }
        incMatrixFile << std::endl;
    }
    incMatrixFile.close();

    for(int i = 0; i < verticesNumber; ++i)
        delete [] adjMatrix[i];

    delete [] adjMatrix;

    for(int i = 0; i < numOfEdges; ++i)
        delete [] incMatrix[i];

    delete [] incMatrix;
}

GraphRepresentation * AdjacencyList::CovertToAdjacencyMatrix() const {
   Convert();

    std::ifstream inputFile;

    if (!inputFile.is_open())
    {
        inputFile.open("MacierzIncydencji.txt", std::ios::in);

        if(!inputFile)
        {
            std::cerr << "Failed to open " << "MacierzIncydencji.txt"<< std::endl;
            exit(EXIT_FAILURE);
        }
    }

    std::string validType;
    std::getline(inputFile, validType);

    AdjacencyMatrix * newRepresentation;

    try
    {
        if(validType != "MI")
            throw "Not known graph representation";
        newRepresentation = new AdjacencyMatrix(inputFile);
    }
    catch (const char * exceptionName)
    {
        std::cerr << exceptionName;
        exit(EXIT_FAILURE);
    }

    inputFile.close();

    return newRepresentation;
}

void AdjacencyList::RandomizeGraph() {
    int edgeStart = static_cast<int>(rand() % m_adjList.size());
    int edgeEnd = m_adjList[edgeStart][rand() % m_adjList[edgeStart].size()];

    RandomizeGraph(edgeStart, edgeEnd);
}

void AdjacencyList::RandomizeGraph(int edgeStart, int edgeEnd) {
    int spareEdgeStart;
    int spareEdgeEnd;

    int counter = 0;

    do {
        do
            spareEdgeStart = static_cast<int>(rand() % m_adjList.size());
        while (spareEdgeStart == edgeStart || spareEdgeStart == edgeEnd);

        const int spareEdgeStartLinks = m_adjList[spareEdgeStart].size();
        spareEdgeEnd = m_adjList[spareEdgeStart][rand() % spareEdgeStartLinks];

        if (edgeStart == spareEdgeEnd)
            std::swap(edgeStart, edgeEnd);

        counter++;
        if(counter == 10)
            break;
    }
    while(AreVerticesConnected(edgeStart, spareEdgeEnd) || AreVerticesConnected(spareEdgeStart, edgeEnd));

    DeleteEdge(spareEdgeStart, spareEdgeEnd);
    DeleteEdge(edgeStart, edgeEnd);
    MakeConnectBetween(edgeStart, spareEdgeEnd);
    MakeConnectBetween(spareEdgeStart, edgeEnd);
}

std::vector <int> AdjacencyList::Components() {
    int componentNumber = -1;
    std::vector <int> componentsOfVerticles(m_adjList.size(), -1);

    for(int i = 0; i < componentsOfVerticles.size(); i++) {
        if(componentsOfVerticles[i] == -1) {
            componentNumber++;
            componentsOfVerticles[i] = componentNumber;
            Components_R(componentNumber, i, componentsOfVerticles);
        }
    }

    return componentsOfVerticles;
}

void AdjacencyList::Components_R(const int componentNumber, const int index, std::vector<int> &componentsOfVerticles){
    for(int i = 0; i < m_adjList[index].size(); i++) {
        if(componentsOfVerticles[m_adjList[index][i]] == -1) {
            componentsOfVerticles[m_adjList[index][i]] = componentNumber;
            Components_R(componentNumber, m_adjList[index][i], componentsOfVerticles);
        }
    }
}

GraphRepresentation * AdjacencyList::BiggestComponent() {
    std::vector<int> componentsOfVerticles = Components();
    int indexOfBiggestComponent = IndexOfBiggestComponent(componentsOfVerticles);
    AdjacencyList * biggestComponent = new AdjacencyList(*this);

    RemoveOtherComponents(componentsOfVerticles, indexOfBiggestComponent, biggestComponent);

    return biggestComponent;
}

int AdjacencyList::IndexOfBiggestComponent(const std::vector<int> componentsOfVerticles) const {
    int mostOccurrences = 0;
    int mostCommon = 0;

    for(int i = 0; i < componentsOfVerticles.size(); i++) {
        int occurrences = static_cast<int>(count(componentsOfVerticles.begin(), componentsOfVerticles.end(), componentsOfVerticles[i]));

        if(occurrences > mostOccurrences)
        {
            mostOccurrences = occurrences;
            mostCommon = componentsOfVerticles[i];
        }
    }

    return mostCommon;
}

void AdjacencyList::RemoveOtherComponents(std::vector<int> &componentsOfVerticles,const int indexOfBiggestComponent, AdjacencyList *biggestComponent) const {
    int currentSize = static_cast<int>(biggestComponent->GetData().size());
    int numOfIndexChanges = 0;

    for(int i = 0; i < currentSize; i++) {
        if(componentsOfVerticles[i] != indexOfBiggestComponent) {
            biggestComponent->GetData().erase(std::next(biggestComponent->GetData().begin(), i));

            if(componentsOfVerticles[i] < indexOfBiggestComponent)
                numOfIndexChanges++;
            componentsOfVerticles.erase(std::next(componentsOfVerticles.begin(), i));

            currentSize--;
            i--;
        }
    }

    for(int i = 0; i < biggestComponent->GetData().size(); i++) {
        for(int j = 0; j < biggestComponent->GetData()[i].size(); j++) {
            biggestComponent->GetData()[i][j] -= numOfIndexChanges;
        }
    }

}







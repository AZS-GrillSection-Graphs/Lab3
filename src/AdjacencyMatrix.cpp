#include "AdjacencyMatrix.h"


AdjacencyMatrix::AdjacencyMatrix(std::ifstream &inputFile) : m_numOfVer(0)
{
    std::vector<std::vector <int> >row;
    std::string line;

    while(getline(inputFile, line))
    {
        ++m_numOfVer;

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

        m_adjMatrix.push_back(col);
    }
}

void AdjacencyMatrix::Print() const
{
    for(int i = 0; i < m_numOfVer; ++i)
    {
        for(int j = 0; j < m_numOfVer; ++j)
        {
            std::cout << m_adjMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void AdjacencyMatrix::Convert() const
{
    ////////// Lista sasiedztwa //////////
    std::ofstream adjListFile;

    if (!adjListFile.is_open())
    {
        adjListFile.open("ListaSasiedztwa.txt", std::ios::out);

        if(!adjListFile)
        {
            std::cerr << "Failed to open " << "ListaSasiedztwa.txt" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    adjListFile << "LS" << std::endl;

    for(int i = 0; i < m_numOfVer; ++i)
    {
        for(int j = 0; j < m_numOfVer; ++j)
        {
            if(m_adjMatrix[i][j] == 1)
            {
                adjListFile << j + 1 << " ";
            }
        }
        adjListFile << std::endl;
    }
    adjListFile.close();


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
    for(int i = 0; i < m_numOfVer; ++i)
        for(int j = i + 1; j < m_numOfVer; ++j)
            numOfEdges += m_adjMatrix[i][j];

    int ** incMatrix = new int * [numOfEdges];
    for(int i = 0; i < numOfEdges; ++i)
    {
        incMatrix[i] = new int [m_numOfVer];
        for(int j = 0; j < m_numOfVer; ++j)
        {
            incMatrix[i][j] = 0;
        }
    }

    int edge = 0;

    for(int i = 0; i < m_numOfVer; ++i)
    {
        for(int j = i + 1; j < m_numOfVer; ++j)
        {
            if(m_adjMatrix[i][j] == 1)
            {
                incMatrix[edge][i] = 1;
                incMatrix[edge][j] = 1;
                ++edge;
            }
        }
    }

    for(int j = 0; j < m_numOfVer; ++j)
    {
        for(int i = 0; i < edge; ++i)
        {
            if(incMatrix[i][j] == 1)
                incMatrixFile << "1 ";
            else
                incMatrixFile << "0 ";
        }
        incMatrixFile << std::endl;
    }
    incMatrixFile.close();

    for(int i = 0; i < numOfEdges; ++i)
        delete [] incMatrix[i];

    delete [] incMatrix;
}

void AdjacencyMatrix::MakeConnectBetween(const int firstVertex, const int secondVertex) {

}

bool AdjacencyMatrix::AreVerticesConnected(const int firstVertex, const int secondVertex) const {
    return false;
}

void AdjacencyMatrix::RandomizeGraph(int edgeStart, int edgeEnd) {

}

void AdjacencyMatrix::RandomizeGraph() {

}

void AdjacencyMatrix::SaveToFile(const char *fileName) const {

}

std::vector<int> AdjacencyMatrix::Components() {
    return std::vector<int>();
}

GraphRepresentation *AdjacencyMatrix::BiggestComponent() {
    return nullptr;
}

//AdjacencyMatrix::~AdjacencyMatrix() {
//
//}

std::vector<std::vector<int>> &AdjacencyMatrix::GetData() {
    return m_adjMatrix;
}

void
AdjacencyMatrix::Components_R(const int componentNumber, const int index, std::vector<int> &componentsOfVerticles) {

}

int AdjacencyMatrix::IndexOfBiggestComponent(const std::vector<int> componentsOfVerticles) const {
    return 0;
}

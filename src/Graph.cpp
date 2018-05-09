#include <fstream>
#include <iostream>

#include "Graph.h"
#include "AdjacencyList.h"

Graph::Graph(const char * inputFileName) : m_graphRepr(NULL)
{
    std::ifstream inputFile;

    if (!inputFile.is_open())
    {
        inputFile.open(inputFileName, std::ios::in);

        if(!inputFile)
        {
            std::cerr << "Failed to open " << inputFileName << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    std::string validType;
    std::getline(inputFile, validType);
    try
    {
        if(validType != "LS")
            throw "Not known graph representation";
        m_graphRepr = new AdjacencyList(inputFile);
    }
    catch (const char * exceptionName)
    {
        std::cerr << exceptionName;
        exit(EXIT_FAILURE);
    }

    inputFile.close();
}

Graph::~Graph()
{
    delete m_graphRepr;
}

void Graph::Print() const
{
    m_graphRepr->Print();
}

void Graph::ConvertGraph() const {
    m_graphRepr->Convert();
}

void Graph::SaveToFile(const char *fileName) const {
    m_graphRepr->SaveToFile(fileName);
    m_graphRepr->Convert();
}

void Graph::DrawGraph() const {
    std::__cxx11::string drawing = "python3 GraphVisualization.py MacierzIncydencji.txt";
    system(drawing.c_str());
}

void Graph::RandomizeGraph() {
    m_graphRepr->RandomizeGraph();
}

void Graph::RandomizeGraph(const int edgeStart, const int edgeEnd) {
    m_graphRepr->RandomizeGraph(edgeStart, edgeEnd);

}

Graph & Graph::BiggestComponent() const {
    Graph * testGraph = new Graph(m_graphRepr->BiggestComponent());
    return *testGraph;
}

int Graph::NumberOfComponents() const {
    std::vector <int> ComponentsOfVerticles = m_graphRepr->Components();
    int numberOfComponents = 1;
    int acctualComponent = ComponentsOfVerticles[0];

    for(int i = 1; i < ComponentsOfVerticles.size(); i++)
    {
        if(ComponentsOfVerticles[i] != acctualComponent) {
            acctualComponent = ComponentsOfVerticles[i];
            numberOfComponents++;
        }
    }

    return numberOfComponents;
}

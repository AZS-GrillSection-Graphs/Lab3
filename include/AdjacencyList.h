#ifndef LAB1_ADJACENCYLIST_H
#define LAB1_ADJACENCYLIST_H

#include <vector>
#include <string>


#include "GraphRepresentation.h"

class AdjacencyList : public GraphRepresentation
{
public:
    explicit AdjacencyList(const int verticesNumber);
    explicit AdjacencyList(std::ifstream &inputFile);
    void Print() const override;
    void MakeConnectBetween(const int firstVertex, const int secondVertex) override;
    bool AreVerticesConnected(const int firstVertex, const int secondVertex) const override;
    void RandomizeGraph(int edgeStart, int edgeEnd) override;
    void RandomizeGraph() override;
    void SaveToFile(const char *fileName) const override;
    void Convert() const override;
    GraphRepresentation * CovertToAdjacencyMatrix() const;
    std::vector <int> Components() override;
    GraphRepresentation *BiggestComponent() override;
    std::vector< std::vector<int> > & GetData() override {return m_adjList;}
    void DeleteEdge(const int firstVertex, const int secondVertex);   //zmienilem z private, na potrzeby EulerCycle
private:
    void Components_R(const int componentNumber, const int index, std::vector<int> &componentsOfVerticles);
    virtual int IndexOfBiggestComponent(const std::vector <int> componentsOfVerticles) const override;
    void RemoveOtherComponents(std::vector<int> &componentsOfVerticles, const int indexOfBiggestComponent, AdjacencyList *biggestComponent) const;

    std::string m_initials;

    std::vector< std::vector<int> > m_adjList;
};

#endif

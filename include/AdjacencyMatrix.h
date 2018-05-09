#ifndef LAB1_ADJACENCYMATRIX_H
#define LAB1_ADJACENCYMATRIX_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "GraphRepresentation.h"

class AdjacencyMatrix : public GraphRepresentation
{
public:
    explicit AdjacencyMatrix(std::ifstream &inputFile);
    void Print() const override;
    void Convert() const override;

    void MakeConnectBetween(const int firstVertex, const int secondVertex) override;

    bool AreVerticesConnected(const int firstVertex, const int secondVertex) const override;

    void RandomizeGraph(int edgeStart, int edgeEnd) override;

    void RandomizeGraph() override;

    void SaveToFile(const char *fileName) const override;

    std::vector<int> Components() override;

    GraphRepresentation *BiggestComponent() override;

    ~AdjacencyMatrix() override = default;

    std::vector<std::vector<int>> &GetData() override;

protected:
    void Components_R(const int componentNumber, const int index, std::vector<int> &componentsOfVerticles) override;

    int IndexOfBiggestComponent(const std::vector<int> componentsOfVerticles) const override;

private:
    std::vector<std::vector<int> > m_adjMatrix;
    int m_numOfVer;
};

#endif //LAB1_ADJACENCYMATRIX_H

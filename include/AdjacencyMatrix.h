//
// Created by os8 on 10.05.18.
//

#ifndef GRAPHS3_NEWSTRUCTURE_ADJACENCYMATRIX_H
#define GRAPHS3_NEWSTRUCTURE_ADJACENCYMATRIX_H

#include <vector>

class AdjacencyMatrix {
public:
    AdjacencyMatrix(const int numberOfVerices, const int numberOfEdges);

    void Print() const;

    bool DoesEdgeExist(const int firstVerticle, const int secondVerticle) const;
    void MakeEdge(const int firstVerticle, const int secondVerticle);

private:
    std::vector<std::vector<int>> m_matrix;

    int FindNotConnectedEdge() const;

};


#endif //GRAPHS3_NEWSTRUCTURE_ADJACENCYMATRIX_H

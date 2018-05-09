#ifndef LAB1_GRAPHREPRESENTATION_H
#define LAB1_GRAPHREPRESENTATION_H


class GraphRepresentation
{
public:
    virtual void Print() const = 0;
    virtual void MakeConnectBetween(const int firstVertex, const int secondVertex) = 0;
    virtual bool AreVerticesConnected(const int firstVertex, const int secondVertex) const = 0;
    virtual void RandomizeGraph(int edgeStart, int edgeEnd) = 0;
    virtual void RandomizeGraph() = 0;
    virtual void SaveToFile(const char *fileName) const = 0;
    virtual void Convert() const = 0;
    virtual std::vector <int> Components() = 0;
    virtual GraphRepresentation *BiggestComponent() = 0;
    virtual ~GraphRepresentation() = default;
    virtual std::vector< std::vector<int> > & GetData() = 0;

protected:
    virtual void Components_R(const int componentNumber, const int index, std::vector<int> &componentsOfVerticles) = 0;
    virtual int IndexOfBiggestComponent(const std::vector <int> componentsOfVerticles) const = 0;
};

#endif //LAB1_GRAPHREPRESENTATION_H

#include "list.h"
#include <string>
#include <fstream>

#ifndef DIGRAPH_HEADER
#define DIGRAPH_HEADER

class DiGraph;
class Node;
class Edge;
class GraphVisualizer;



class DiGraph{
private:
    Node**  nodes;
    bool isFull();
    void increase();
    int index ,size;
    List<Edge*> result;
    GraphVisualizer* graphviz;
    std::string startnode;
    std::string endnode;

public:

    DiGraph();
    ~DiGraph();
    void loadData(std::string);
    void addNode(std::string);
    void addEdge(std::string, std::string, float);
    List<Node*> getNeighbours(std::string);
    List<Edge*> getEdges(std::string);
    List<Node*> getNodes();

    void deleteNode(std::string);
    void deleteEdge(std::string, std::string, float);
    void changeWeight(std::string, std::string, float, float);
    void delAllNodes();
    void saveData(std::string);
    void visualize(std::string);
    void setstartnode(std::string startnodes);
    std::string getstartnode();
    void setendnode(std::string endnotes);
    std::string getendnote();
    List<Edge*> getresult();
    void setVisualizer(GraphVisualizer* graphviz);
    GraphVisualizer* getVisualizer();
    List<Edge*> dijkstraShortestPath(std::string, std::string);
};

class Node{
private:
    std::string key;
    List<Edge*> edges;

public:
    Node(std::string);
    std::string getKey();
    List<Edge*> getEdges();
    void setKey(std::string);
    void setNewEdge(Edge*);

    void delete_Edge(std::string, float); //key2, weight
    void changeWeight(std::string, float, float); //key2, oldweight, newweight
    void delAllEdges();
};

class Edge {
private:
    Node *startNode, *endNode;
    float weight;

public:
    Edge(Node*, float);
    Edge(Node*, Node*, float);
    float getWeight();
    Node* getStartNode();
    Node* getEndNode();
    void setWeight(float);
    void setStartNode(Node* n);
    void setEndNode(Node* n);
};

class GraphVisualizer{
public:
    GraphVisualizer();
    ~GraphVisualizer();
    virtual void visualize(DiGraph &graph, std::string);
};

class DotGraphVisualizer : public GraphVisualizer {
public:
    DotGraphVisualizer();

    ~DotGraphVisualizer();

    void visualize(DiGraph &graph, std::string filename);
};

class DiDotGraphVisualizer : public GraphVisualizer {
public:
    DiDotGraphVisualizer();

    ~DiDotGraphVisualizer();

    void visualize(DiGraph &graph, std::string filename);
};


#endif
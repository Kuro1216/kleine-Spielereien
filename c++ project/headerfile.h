#include "liste.hpp"
#include <string>
using namespace std;

typedef class Node Node;
typedef class Edge Edge;

class DiGraph{
private:
    Liste<Node*> _nodes;
public:
    void addNode(string key);
    void addEdge(string key1, string key2, float weight);
    void delNode(string key);
    void delEdge(string key1, string key2, float weight);
    void chWeight(string key1, string key2, float oweight, float nweight);
    void killNodes(void);
    Liste<Node*> getNeighbours(string key);
    Liste<Edge*> getEdges(string key);
    Liste<Node*> getNodes(void);

    DiGraph(void);
    DiGraph(string filename);

    void save(string filename);

    ~DiGraph(void);
};

class Node{
private:
    Liste<Edge*> _edges;
    string _key;
public:
    string getKey(void);
    Liste<Edge*> getEdges(void);
    void setKey(string key);
    void setNewEdge(Edge *edge);
    void delEdge(string key2, float weight);
    void chWeight(string key2, float oweight, float nweight);
    void killEdges(void);
    Node(string key);
    ~Node(void);

    int operator==(const Node &n);
    Node operator=(const Node &n);
};

class Edge{
private:
    Node *_startnode, *_endnode;
    float _weight;
public:
    float getWeight(void);
    Node *getStartNode(void);
    Node *getEndNode(void);
    void setWeight(float weight);
    void setStartNode(Node *node);
    void setEndNode(Node *node);

    Edge(Node *startnode, Node *endnode, float weight);
    ~Edge(void);

    int operator==(const Edge &e);
    Edge operator=(const Edge &e);
};

class DiGraphVisualizer{
private:
public:
    DiGraphVisualizer(void);
    ~DiGraphVisualizer(void);
    void visualize(DiGraph &graph, string filename = "_graph");
};

class DigraphExeption{
private:
    string _involved, _error, _hint;
    int _code;
public:
    string getInvolved(void);
    string getError(void);
    string getHint(void);
    int getCode(void);
    void setInvolved(string involved);
    void setError(string error);
    void setHint(string hint);
    void setCode(int code);
    DigraphExeption(void);
    ~DigraphExeption(void);
};

using namespace std;

class Tokenizer {
private:
    unsigned int _pos;
    Liste<string> _tokens;

public:
    Tokenizer(string data, string separators);
    int countTokens();
    string nextToken();
    bool hasMoreTokens();
};



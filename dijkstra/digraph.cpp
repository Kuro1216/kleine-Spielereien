#include "list.h"
#include "digraph.h"
#include "tokenizer.h"
#include "priorityQueue.h"
#include "visualizer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <string>


DiGraph::DiGraph() : result(10) {
    index = 0;
    size = 20;
    nodes = new Node *[size];
}

DiGraph::~DiGraph() {
    for (int i = 0; i < index; i++) {
        delete nodes[i];
    }
    delete[] nodes;
}

bool DiGraph::isFull() {
    return index == size;
}

void DiGraph::increase() {
    Node **temp = new Node *[size * 2];

    for (int i = 0; i <= index; i++) {
        temp[i] = nodes[i];
    }

    size *= 2;

    nodes = temp;
}

void DiGraph::addNode(std::string input) {

    List<Node *> nodes = this->getNodes();
    for (int i = 0; i < nodes.getSize(); i++) {
        if (this->nodes[i]->getKey() == input) {
            throw std::invalid_argument("Node already exists!");
        }
    }

    Node *temp = new Node(input);
    if (isFull()) {
        increase();
    }
    this->nodes[index] = temp;
    index++;
}

void DiGraph::addEdge(std::string key1, std::string key2, float weight) {
    for (int i = 0; i < index; i++) {
        if (nodes[i]->getKey() == key1) {
            for (int j = 0; j < index; j++) {
                if (nodes[j]->getKey() == key2) {
                    Edge *temp = new Edge(nodes[i], weight);
                    temp->setEndNode(nodes[j]);
                    nodes[i]->setNewEdge(temp);
                    return;
                }
            }
            throw std::invalid_argument("Key2");
        }
    }
    throw std::invalid_argument("Key1");
}

List<Node *> DiGraph::getNeighbours(std::string key1) {
    List<Node *> temp(10);
    for (int i = 0; i < index; i++) {
        if (nodes[i]->getKey() == key1) {
            List<Edge *> edges = nodes[i]->getEdges();
            for (int j = 0; j < edges.getSize(); j++) {
                if (temp.find(edges.getValueAt(j)->getEndNode()) == -1) {
                    temp.append(edges.getValueAt(j)->getEndNode());
                }
            }
            return temp;
        }
    }
    throw std::invalid_argument("Key");
    return temp;
}

List<Edge *> DiGraph::getEdges(std::string key1) {
    for (int i = 0; i < index; i++) {
        if (nodes[i]->getKey() == key1) {
            return nodes[i]->getEdges();
        }
    }
    std::cout << "Key wurde nicht gefunden" << std::endl;
    List<Edge *> temp(10);
    return temp;
}

List<Node *> DiGraph::getNodes() {
    List<Node *> temp(10);
    for (int i = 0; i < index; i++) {
        temp.append(nodes[i]);
    }
    return temp;
}

void DiGraph::deleteNode(std::string key1) {
    for (int i = 0; i < index; i++) {
        List<Edge *> edges = nodes[i]->getEdges();
        for (int j = 0; j < edges.getSize(); j++) {
            if (edges.getValueAt(j)->getEndNode()->getKey() == key1) {
                throw std::invalid_argument("Node has incoming Edges");
            }
        }

        if (this->nodes[i]->getKey() == key1) {
            nodes[i] = nodes[index - 1];
            delete nodes[index - 1];
            index--;
            std::cout << "----------------------" << "\n";
            std::cout << "Node has been deleted!" << "\n";
            std::cout << "----------------------" << std::endl;
            return;
        }
    }
    throw std::invalid_argument("Key not found");
}

void DiGraph::deleteEdge(std::string key1, std::string key2, float weight) {
    for (int i = 0; i < index; i++) {
        if (this->nodes[i]->getKey() == key1) {
            try {
                this->nodes[i]->delete_Edge(key2, weight);
                return;
            }
            catch (std::exception &e) {
                throw std::invalid_argument(e.what());
            }
        }
    }
    throw std::invalid_argument("Start node does not exist.");
}

void DiGraph::changeWeight(std::string key1, std::string key2, float oldweight, float newweight) {
    for (int i = 0; i < index; i++) {
        if (this->nodes[i]->getKey() == key1) {
            try {
                this->nodes[i]->changeWeight(key2, oldweight, newweight);
            }
            catch (std::exception &e) {
                throw std::invalid_argument(e.what());
            }

        }
    }
    throw std::invalid_argument("Start node does not exist.");
}

void DiGraph::delAllNodes() {
    for (int i = 0; i < index; i++) {
        delete nodes[i];
    }
    delete[] nodes;
    Node **temp = new Node *[10];
    nodes = temp;
    size = 10;
    index = 0;
}

void Node::delAllEdges(void) {
    List<Edge *> edges = getEdges();
    while (edges.getSize() > 0) {
        edges.remove(1);
    }
}

void DiGraph::saveData(std::string filename) {
    std::ofstream file;
    file.open(filename);

    file << "# Alle Knoten\n";

    List<Node *> nodes = this->getNodes();
    for (int i = 0; i < nodes.getSize(); i++) {
        file << this->nodes[i]->getKey() << "\n";
    }

    file << "# Alle Kanten\n";

    for (int i = 0; i < nodes.getSize(); i++) {
        List<Edge *> edges = nodes.getValueAt(i)->getEdges();
        if (edges.getSize() != 0) {
            for (int j = 0; j < edges.getSize(); j++) {

                file << edges.getValueAt(j)->getStartNode()->getKey();
                file << " " << edges.getValueAt(j)->getEndNode()->getKey();
                file << " " << edges.getValueAt(j)->getWeight() << "\n";
            }
        }
    }

    file << "#ende\n";
    file.close();
}


void DiGraph::visualize(std::string filename) {
    std::ofstream file;
    file.open(filename, std::ios::out);

    file << "digraph {\n\n";
    file << "  rankdir=RL;\n\n";

    List<Node *> nodes = this->getNodes();

    for (int i = 0; i < nodes.getSize(); i++) {
        List<Edge *> edges = nodes.getValueAt(i)->getEdges();
        if (edges.getSize() != 0) {
            for (int j = 0; j < edges.getSize(); j++) {

                file << "\"" << edges.getValueAt(j)->getStartNode()->getKey();
                file << "\"   ->   \"" << edges.getValueAt(j)->getEndNode()->getKey();
                file << "\"    [label = " << edges.getValueAt(j)->getWeight() << "];\n";
            }
        }
    }

    file << "}\n";
    file.close();
}

void DiGraph::loadData(std::string filename) {
    int nodes = 0;

    std::ifstream file;
    file.open(filename);

    if (!file.is_open()) {
        std::cerr << " failed to open input.txt \n";
        return;
    }

    std::string fileContent((std::istreambuf_iterator<char>(file)),
                            (std::istreambuf_iterator<char>()));

    file.close();

    Tokenizer tok(fileContent, "\n");

    while (tok.hasMoreTokens()) {
        std::string line = tok.nextToken();
        if (line == "# Alle Knoten") {
            nodes = 1;
            line = tok.nextToken();
        }

        if (line == "# Alle Kanten") {
            nodes = 2;
            line = tok.nextToken();
        }

        if (line == "#ende") break;

        Tokenizer words(line, " ");
        if (nodes == 1 && words.countTokens() != 1) {
            throw std::invalid_argument("Node input has wrong format");
        } else if (nodes == 1 && words.countTokens() == 1) {
            try {
                addNode(words.nextToken());
            } catch (std::exception &e) {
                if ((std::string) e.what() == "Node already exists!") {
                    std::cout << "Skipping existing Node" << std::endl;
                }
            }
        } else if (nodes == 2 && words.countTokens() != 3) {
            throw std::invalid_argument("Edge input has wrong formatting");
        } else if (nodes == 2 && words.countTokens() == 3) {
            std::string startNode = words.nextToken();
            std::string endNode = words.nextToken();
            int weight = std::stoi(words.nextToken());
            try {
                addEdge(startNode, endNode, weight);
            } catch (std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
}

List<Edge *> DiGraph::dijkstraShortestPath(std::string start, std::string end) {
    while (result.getSize() != 0) {
        result.remove(1);
    }
    startnode = start;
    endnode = end;
    if (index < 1) {
        throw std::length_error("Graph ist Leer");
    }
    for (int i = 0; i <= index; i++) {
        if (i == index) {
            throw std::invalid_argument("Startpunkt nicht gefunden");
        }
        if (nodes[i]->getKey() == start) {
            break;
        }
    }

    for (int i = 0; i <= index; i++) {
        if (i == index) {
            throw std::invalid_argument("Zielpunkt nicht gefunden");
        }
        if (nodes[i]->getKey() == end) {
            break;
        }
    }

    int used = index - 1;
    // pQueuey pq = pQueue();
    pQueue<Node *> pq;

    float dist[used];
    Node *previous[used];

    for (int i = 0; i <= used; i++) {
        if (nodes[i]->getKey() != start) {
            dist[i] = std::numeric_limits<float>::infinity();
        } else {
            dist[i] = 0;
        }

        previous[i] = NULL;

        pq.insert(nodes[i], dist[i]);
    }

    while (!pq.isEmpty()) {
        Node *u = pq.extractMin();
        int indexOfU = 0;

        for (int i = 0; i < used; i++) {
            if (nodes[i]->getKey() == u->getKey()) {
                indexOfU = i;
            }
        }

        List<Edge *> outEdgesList = u->getEdges();
        Edge *outEdges[outEdgesList.getSize()];

        int size = 0;

        for (int i = 0; i < outEdgesList.getSize(); i++) {
            outEdges[i] = outEdgesList.getValueAt(i);
            size++;
        }

        for (int i = 0; i < size; i++) {
            Node *v = outEdges[i]->getEndNode();
            int indexOfV = 0;

            for (int i = 0; i < used; i++) {
                if (nodes[i]->getKey() == v->getKey()) {
                    indexOfV = i;
                }
            }

            float alt = dist[indexOfU] + outEdges[i]->getWeight();

            if (alt < dist[indexOfV]) {
                dist[indexOfV] = alt;
                previous[indexOfV] = u;
                pq.decreaseKey(v, alt);
            }
        }
    }

    int u = 0;

    for (int i = 0; i < used; i++) {
        if (nodes[i]->getKey() == end) {
            u = i;
        }
    }

    while (previous[u] != NULL) {
        List<Edge *> edgesOfU = previous[u]->getEdges();

        for (int i = 0; i < previous[u]->getEdges().getSize(); i++) {
            if (edgesOfU.getValueAt(i)->getEndNode()->getKey() == nodes[u]->getKey()) {
                result.append(edgesOfU.getValueAt(i));
            }
        }

        for (int i = 0; i < used; i++) {
            if (nodes[i]->getKey() == previous[u]->getKey()) {
                u = i;
                break;
            }
        }
    }

    if (result.getSize() == 0) {
        throw std::logic_error("Es wurde kein Weg gefunden");
    }

    return result;
}

Node::Node(std::string key) : edges(10) {
    this->key = key;
}

std::string Node::getKey() {
    return key;
}

List<Edge *> Node::getEdges() {
    return edges;
}

void Node::setKey(std::string key1) {
    key = key1;
}

void Node::setNewEdge(Edge *inputEdge) {
    edges.append(inputEdge);
}

void Node::delete_Edge(std::string key2, float weight) {
    for (int i = 0; i < edges.getSize(); i++) {
        Edge *edge = edges.getValueAt(i);
        if ((edge->getEndNode()->getKey() == key2) && (edge->getWeight() == weight)) {
            edges.remove(i);
            return;
        }
        if ((edge->getEndNode()->getKey() == key2) && (edge->getWeight() != weight)) {
            throw std::invalid_argument("Edge with that weight does not exist.");
        }
        if (edge->getEndNode()->getKey() != key2) {
            throw std::invalid_argument("End node does not exist.");
        }
    }
}

void Node::changeWeight(std::string key2, float oldweight, float newweight) {
    for (int i = 0; i < edges.getSize(); i++) {
        Edge *edge = edges.getValueAt(i);
        if (edge->getEndNode()->getKey() == key2) {
            if (edge->getWeight() == oldweight) {
                edges.getValueAt(i)->setWeight(newweight);
                return;
            }
            throw std::invalid_argument("No edge with that weight found.");
        }
    }
    throw std::invalid_argument("End node does not exist.");
}

Edge::Edge(Node *startnode, Node *endnode, float weight) {
    startNode = startnode;
    endNode = endnode;
    this->weight = weight;
}

Edge::Edge(Node *node, float w) {
    setStartNode(node);
    setWeight(w);
}

float Edge::getWeight() {
    return weight;
}

Node *Edge::getStartNode() {
    return startNode;
}

Node *Edge::getEndNode() {
    return endNode;
}

void Edge::setWeight(float w) {
    weight = w;
}

void Edge::setStartNode(Node *n) {
    startNode = n;
}

void Edge::setEndNode(Node *n) {
    endNode = n;
}

GraphVisualizer::GraphVisualizer() {

}

GraphVisualizer::~GraphVisualizer() {

}

DotGraphVisualizer::DotGraphVisualizer() {
}

DotGraphVisualizer::~DotGraphVisualizer() {
}


List<Edge *> DiGraph::getresult() {
    return this->result;
}

void DiGraph::setendnode(std::string end) {
    this->endnode = end;
}

std::string DiGraph::getendnote() {
    return this->endnode;
}

void DiGraph::setstartnode(std::string startnodes) {
    this->startnode = startnodes;
}

std::string DiGraph::getstartnode() {
    return this->startnode;
}

void DiGraph::setVisualizer(GraphVisualizer *graphviz) {
    this->graphviz = graphviz;
}

GraphVisualizer *DiGraph::getVisualizer() {
    return this->graphviz;
}

void DotGraphVisualizer::visualize(DiGraph &graph, std::string filename) {
    std::ofstream file;
    file.open(filename, std::ios::out);
    List<Edge *> weg = graph.getresult();
    std::string startnode = graph.getstartnode();
    std::string entnode = graph.getendnote();
    file << "digraph {\n\n";
    file << "  rankdir=LR;\n\n";
    file << "  " << "node" << " " << "[color=green ] \"" << startnode << "\";" << std::endl;
    for (int a = 0; a < weg.getSize(); a++) {
        file << "  " << "node" << " " << "[color=red ] \"" << weg.getValueAt(a)->getEndNode()->getKey() << "\";"
             << std::endl;
    }

    file << "  " << "node" << " " << "[shape = circle, color=black];" << std::endl;
    List<Node *> nodes = graph.getNodes();

    for (int i = 0; i < nodes.getSize(); i++) {
        List<Edge *> edges = nodes.getValueAt(i)->getEdges();
        if (edges.getSize() != 0) {
            for (int j = 0; j < edges.getSize(); j++) {
                int c = 0;
                for (int a = 0; a < weg.getSize(); a++) {
                    if (edges.getValueAt(j)->getStartNode()->getKey() == weg.getValueAt(a)->getStartNode()->getKey() &&
                        edges.getValueAt(j)->getEndNode()->getKey() == weg.getValueAt(a)->getEndNode()->getKey() &&
                        edges.getValueAt(j)->getWeight() == weg.getValueAt(a)->getWeight()) {
                        file << "\"" << edges.getValueAt(j)->getStartNode()->getKey();
                        file << "\"   ->   \"" << edges.getValueAt(j)->getEndNode()->getKey();
                        file << "\"    [label = " << edges.getValueAt(j)->getWeight()
                             << ", style=bold, color=orange];\n";
                        c = 1;
                    }
                }
                if (c != 1) {
                    file << "\"" << edges.getValueAt(j)->getStartNode()->getKey();
                    file << "\"   ->   \"" << edges.getValueAt(j)->getEndNode()->getKey();
                    file << "\"    [label = " << edges.getValueAt(j)->getWeight() << ", dir=none];\n";
                }
            }
        }
    }
    file << "}\n";
    file.close();
}

DiDotGraphVisualizer::DiDotGraphVisualizer() {
}

DiDotGraphVisualizer::~DiDotGraphVisualizer() {
}

void DiDotGraphVisualizer::visualize(DiGraph &graph, std::string filename) {
    std::ofstream file;
    file.open(filename, std::ios::out);

    file << "digraph {\n\n";
    file << "  rankdir=RL;\n\n";

    List<Node *> nodes = graph.getNodes();

    for (int i = 0; i < nodes.getSize(); i++) {
        List<Edge *> edges = nodes.getValueAt(i)->getEdges();
        if (edges.getSize() != 0) {
            for (int j = 0; j < edges.getSize(); j++) {

                file << "\"" << edges.getValueAt(j)->getStartNode()->getKey();
                file << "\"   ->   \"" << edges.getValueAt(j)->getEndNode()->getKey();
                file << "\"    [label = " << edges.getValueAt(j)->getWeight() << "];\n";
            }
        }
    }

    file << "}\n";
    file.close();
}


void GraphVisualizer::visualize(DiGraph &graph, std::string filename) {
}




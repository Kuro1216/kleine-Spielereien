#include "headerfile.hpp"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;


string Node::getKey(void){
    return _key;
}

Liste<Edge*> Node::getEdges(void){
    return _edges;
}

void Node::setKey(string key){
    _key = key;
}

void Node::setNewEdge(Edge *edge){
    _edges.append(edge);
}

void Node::delEdge(string key2, float weight){
    Edge *e;
    for(int i = 0; i < _edges.size(); i++){
        e = _edges[i];
        if((e->getEndNode()->getKey() == key2) && (e->getWeight() == weight)){
            _edges.remove(i);
            return;
        }
    }
    throw "NoEdgeToDelete";
}


void Node::chWeight(string key2, float oweight, float nweight){
    for(int i = 0; i < _edges.size(); i++){
        Edge *e = _edges[i];
        if((e->getEndNode()->getKey() == key2) && (e->getWeight() == oweight)){
            _edges[i]->setWeight(nweight);
            return;
        }
    }
    throw "NoEdgeToChangeWeight";
}

void Node::killEdges(void){
    while(_edges.size() != 0){
        _edges.remove(0);
    }
}

Node::Node(string key){
    _key = key;
}

Node::~Node(void){

}

int Node::operator==(const Node &n){
    return (this->_key == n._key);
}

Node Node::operator=(const Node &n){
    this->_key = n._key;
    return *this;
}

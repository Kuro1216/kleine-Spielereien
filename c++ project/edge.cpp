#include "headerfile.hpp"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;


float Edge::getWeight(void){
    return _weight;
}

Node *Edge::getStartNode(void){
    return _startnode;
}

Node *Edge::getEndNode(void){
    return _endnode;
}

void Edge::setWeight(float weight){
    _weight = weight;
}

void Edge::setStartNode(Node *node){
    _startnode = node;
}

void Edge::setEndNode(Node *node){
    _endnode = node;
}

Edge::Edge(Node *startnode, Node *endnode, float weight){
    _startnode = startnode;
    _endnode = endnode;
    _weight = weight;
}

Edge::~Edge(void){

}

int Edge::operator==(const Edge &e){
    return ((this->_startnode->getKey() == e._startnode->getKey()) &&
            (this->_endnode->getKey() == e._endnode->getKey()) &&
            (this->_weight == e._weight));
}

Edge Edge::operator=(const Edge &e){
    this->_startnode = e._startnode;
    this->_endnode = e._endnode;
    this->_weight = e._weight;
    return *this;
}

#include "headerfile.hpp"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;


DiGraphVisualizer::DiGraphVisualizer(void){

}

DiGraphVisualizer::~DiGraphVisualizer(void){

}

void DiGraphVisualizer::visualize(DiGraph &graph, string filename){
    ofstream file;
    file.open(filename + ".dot");
    file << "digraph{" << endl << "  reankdir=RL;" << endl;
    for(int i = 0; i < graph.getNodes().size(); i++){
        for(int j = 0; j < graph.getEdges(graph.getNodes()[i]->getKey()).size(); j++){
            file << "  " << '\"';
            file << graph.getEdges(graph.getNodes()[i]->getKey())[j]->getStartNode()->getKey();
            file << '\"' << "  ->  " << '\"';
            file << graph.getEdges(graph.getNodes()[i]->getKey())[j]->getEndNode()->getKey();
            file << '\"' << "  " << "[label=";
            file << graph.getEdges(graph.getNodes()[i]->getKey())[j]->getWeight();
            file << "];" << endl;
        }
    }
    file << "}" << endl;
    string command = "dot -Tpng " + filename + ".dot -o " + filename + ".png";
    system(command.c_str());
    file.close();
}

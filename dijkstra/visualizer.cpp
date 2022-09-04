#include "visualizer.h"
#include "digraph.h"
#include <string>
#include <fstream>
#include <iostream>
/*
using namespace std;


GraphVisualizer::GraphVisualizer(void) {

}

GraphVisualizer::~GraphVisualizer(void) {
}


void GraphVisualizer::visualize(DiGraph &graph, string filename, string startnode, string entnode, List<Edge *> weg) {
    std::ofstream file;
    file.open(filename, std::ios::out);

    file << "digraph {\n\n";
    file << "  rankdir=LR;\n\n";
    file << "  " << "node" << " " << "[color=green ] \"" << startnode << "\";" << endl;
    file << "  " << "node" << " " << "[color=red ] \"" << entnode << "\";" << endl;
    file << "  " << "node" << " " << "[shape = circle, color=black];" << endl;
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
                } if( c != 1 ) {
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


DotGraphVisualizer::DotGraphVisualizer(void) {

}

DotGraphVisualizer::~DotGraphVisualizer(void) {

}


void DotGraphVisualizer::visualize(DiGraph &graph, string filename) {
    std::ofstream file;
    file.open(filename, std::ios::out);

    file << "digraph {\n\n";
    file << "  rankdir=LR;\n\n";

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
*/
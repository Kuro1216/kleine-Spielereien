#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <cstdio>
#include <cctype>
#include "list.h"
#include "digraph.h"
#include "tokenizer.h"
#include "visualizer.h"

int getMenue(){

    int choice;

    std::cout << "Menü:" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;
    std::cout << "1 - weitere Knoten hinzufuegen" << std::endl;
    std::cout << "2 - weitere Knoten entfernen" << std::endl;
    std::cout << "3 - Kanten entfernen" << std::endl;
    std::cout << "4 - weitere Kanten aufnehmen" << std::endl;
    std::cout << "5 - Gewicht von Kanten veraendern" << std::endl;
    std::cout << "6 - aktuellen Graphen in einer Datei speichern" << std::endl;
    std::cout << "7 - einen gespeicherten Graphen laden" << std::endl;
    std::cout << "8 - Knoten und Kanten loeschen" << std::endl;
    std::cout << "9 - Kuerzesten Weg finden" << std::endl;
    std::cout << "10- Graph visualize" << std::endl;
    std::cout << "11 - Programm verlassen" << std::endl;

    std::cin >> choice;
    return choice;
}

int main(void) {



    DiGraph testGraph = DiGraph();

    int menue;

    menue = getMenue();

    while(menue !=11){
        switch(menue){

            case 1: {
                // Knoten hinzufügen
                std::string new_node;
                std::cout << "New Node: ";
                std::cin >> new_node;
                try{
                    testGraph.addNode(new_node);
                }catch(std::exception &e){
                    std::cout << "-----------------------------------------------" << std::endl;
                    std::cout << "Error: "<< e.what() << std::endl;
                    std::cout << "-----------------------------------------------" << std::endl << std::endl;
                }
                break;
            }

            case 2: {
                // Node entfernen
                std::string del_node;
                std::cout << "Delete Node: ";
                std::cin >> del_node;
                try{
                    testGraph.deleteNode(del_node);
                }
                catch(std::exception &e){
                    std::cout << "-----------------------------------------------" << std::endl;
                    std::cout << e.what() << std::endl;
                    std::cout << "-----------------------------------------------" << std::endl << std::endl;
                }

                break;
            }

            case 3: {
                // Kante entfernen
                std::string start_node, end_node;
                float the_weight;
                std::cout << "Start Node: ";
                std::cin >> start_node;
                std::cout << "End Node: ";
                std::cin >> end_node;
                std::cout << "Weight: ";
                std::cin >> the_weight;
                try{
                    testGraph.deleteEdge(start_node, end_node, the_weight);
                }
                catch(std::exception &e){
                    std::cout << "-----------------------------------------------" << std::endl;
                    std::cout << e.what() << std::endl;
                    std::cout << "-----------------------------------------------" << std::endl << std::endl;
                }
                break;
            }

            case 4: {
                // Weitere Kante hinzufügen
                std::string start_node, end_node;
                float the_weight;
                std::cout << "Start Node: ";
                std::cin >> start_node;
                std::cout << "End Node: ";
                std::cin >> end_node;
                std::cout << "Weight: ";
                std::cin >> the_weight;
                try{
                    testGraph.addEdge(start_node, end_node, the_weight);
                } catch(std::exception &e) {
                    std::cout << "-----------------------------------------------" << std::endl;
                    std::cout << "Error: Key not found: " << e.what() << std::endl;
                    std::cout << "-----------------------------------------------" << std::endl << std::endl;
                }
                break;
            }

            case 5: {
                // Gewicht einer Kante veraendern
                std::string start_node, end_node;
                float old_weight, new_weight;
                std::cout << "Start Node: ";
                std::cin >> start_node;
                std::cout << "End Node: ";
                std::cin >> end_node;
                std::cout << "Old Weight: ";
                std::cin >> old_weight;
                std::cout << "New Weight: ";
                std::cin >> new_weight;
                try{
                    testGraph.changeWeight(start_node, end_node, old_weight, new_weight);
                }catch(std::exception &e){
                    std::cout << "-----------------------------------------------" << std::endl;
                    std::cout << e.what() << std::endl;
                    std::cout << "-----------------------------------------------" << std::endl << std::endl;
                }
                break;
            }

            case 6: {
                // aktuellen Graphen in einer Datei speichern
                testGraph.saveData("input.txt");
                std::cout << "-----------------------------------------------" << std::endl;
                std::cout << "Graph has been saved!" << std::endl;
                std::cout << "-----------------------------------------------" << std::endl << std::endl;
                break;
            }

            case 7: {
                // einen gespeicherten Graphen laden
                testGraph.loadData("input.txt");
                std::cout << "-----------------------------------------------" << std::endl;
                std::cout << "Graph has been loaded!" << std::endl;
                std::cout << "-----------------------------------------------" << std::endl << std::endl;
                break;
            }

            case 8: {
                // Alle Knoten löschen
                testGraph.delAllNodes();
                break;
            }
                //void GraphVisualizer::visualize(DiGraph &graph, string filename, string startnode, string entnode, List<Edge*> weg)
            case 9: {
                std::string start_node, end_node;
                std::cout << "Start eingeben" << std::endl;
                std::cin >> start_node;
                std::cout << "Ziel eingeben" << std::endl;
                std::cin >> end_node;
                DotGraphVisualizer v;
                GraphVisualizer* graphvizz = &v;
                testGraph.setVisualizer(graphvizz);



                try {
                    testGraph.dijkstraShortestPath(start_node, end_node);
                    List<Edge*> shortest = testGraph.getresult();
                    std::cout << "-----------------------------------------------" << std::endl;
                    for(int i = shortest.getSize() - 1; i >= 0; i--) {
                                              std::cout << shortest.getSize() << " ";
                        std::cout << shortest.getValueAt(i)->getStartNode()->getKey() << " ";
                        std::cout << shortest.getValueAt(i)->getEndNode()->getKey() << " ";
                        std::cout << shortest.getValueAt(i)->getWeight() << std::endl;

                    }
                    testGraph.getVisualizer()->visualize(testGraph,"weg.dot");
                    std::cout << "-----------------------------------------------" << std::endl << std::endl;
                } catch(std::exception &e) {
                    std::cout << "-----------------------------------------------" << std::endl;
                    std::cout << e.what() << std::endl;
                    std::cout << "-----------------------------------------------" << std::endl << std::endl;
                }
                break;
            }

            default: {
                std::cout << "-----------------------------------------------" << std::endl;
                std::cout << "Kommando wurde nicht gefunden" << std::endl;
                std::cout << "-----------------------------------------------" << std::endl << std::endl;
                break;
            }
                 case 10: {
                     //graph visualize
                     DiDotGraphVisualizer visualizer ;
                     GraphVisualizer* graphvizz = &visualizer;
                     testGraph.setVisualizer(graphvizz);
                    testGraph.getVisualizer()->visualize(testGraph, "_graph.txt");
                     std::cout << "-----------------------------------------------" << std::endl;
                     std::cout << "Graph has been visualized!" << std::endl;
                     std::cout << "-----------------------------------------------" << std::endl << std::endl;
                     break;
                 }
        }
        menue = getMenue();
    }

    return 0;

}

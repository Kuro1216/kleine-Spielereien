#include "headerfile.hpp"
#include <iostream>
using namespace std;

int test1(void){
    DiGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addNode("D");
    g.addNode("E");
    g.addNode("F");
    try{
        g.addNode("A");
    }catch(DigraphExeption e){
        if(e.getCode() != 1) return -1;
        else return 0;
    }
    return -1;
}

int test2(void){
    DiGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addNode("D");
    g.addNode("E");
    g.addNode("F");
    try{
        g.addEdge("G", "H", 0.1);
    }catch(DigraphExeption e){
        if(e.getCode() != 2) return -1;
        else return 0;
    }
    return -1;
}

int test3(void){
    DiGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addNode("D");
    g.addNode("E");
    g.addNode("F");
    g.addEdge("A", "B", 3.5);
    try{
        g.addEdge("A", "B", 3.5);
    }catch(DigraphExeption e){
        if(e.getCode() != 3) return -1;
        else return 0;
    }
    return -1;
}

int test5(void){
    DiGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addNode("D");
    g.addNode("E");
    g.addNode("F");
    try{
        g.getEdges("G");
    }catch(DigraphExeption e){
        if(e.getCode() != 5) return -1;
        else return 0;
    }
    return -1;
}

int test4(void){
    DiGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addNode("D");
    g.addNode("E");
    g.addNode("F");
    try{
        g.getNeighbours("G");
    }catch(DigraphExeption e){
        if(e.getCode() != 4) return -1;
        else return 0;
    }
    return -1;
}

int test6(void){
    try{
        DiGraph g("notexistingfile.txt");
    }catch(DigraphExeption e){
        if(e.getCode() != 6) return -1;
        else return 0;
    }
    return -1;
}

int test7(void){
    try{
        DiGraph g("test7.txt");
    }catch(DigraphExeption e){
        if(e.getCode() != 7) return -1;
        else return 0;
    }
    return -1;
}

int test8(void){
    try{
        DiGraph g("test8.txt");
    }catch(DigraphExeption e){
        if(e.getCode() != 8) return -1;
        else return 0;
    }
    return -1;
}

int test9(void){
    try{
        DiGraph g("test9.txt");
    }catch(DigraphExeption e){
        if(e.getCode() != 9) return -1;
        else return 0;
    }
    return -1;
}

int test10(void){
    DiGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addEdge("B", "A", 0.2);
    g.addEdge("C", "A", 0.3);
    try{
        g.delNode("A");
    }catch(DigraphExeption e){

        if(e.getCode() != 10) return -1;
        else return 0;
    }
    return -1;
}

int test11(void){
    DiGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addEdge("A", "B", 0.2);
    g.addEdge("A", "C", 0.3);
    try{
        g.delNode("A");
    }catch(DigraphExeption e){
        if(e.getCode() != 11) return -1;
        else return 0;
    }
    return -1;
}

int test12(void){
    DiGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addEdge("A", "B", 0.2);
    g.addEdge("A", "C", 0.3);
    try{
        g.delNode("D");
    }catch(DigraphExeption e){
        if(e.getCode() != 12) return -1;
        else return 0;
    }
    return -1;
}

int test13(void){
    DiGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addEdge("A", "B", 0.2);
    g.addEdge("A", "C", 0.3);
    try{
        g.delEdge("D", "A", 0.4);
    }catch(DigraphExeption e){
        if(e.getCode() != 13) return -1;
        else return 0;
    }
    return -1;
}

int test14(void){
    DiGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addEdge("A", "B", 0.2);
    g.addEdge("A", "C", 0.3);
    try{
        g.delEdge("A", "D", 0.4);
    }catch(DigraphExeption e){
        if(e.getCode() != 14) return -1;
        else return 0;
    }
    return -1;
}

int test15(void){
    DiGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addEdge("A", "B", 0.2);
    g.addEdge("B", "C", 0.3);
    try{
        g.chWeight("A", "D", 0.4 , 0.5);
    }catch(DigraphExeption e){
        if(e.getCode() != 15) return -1;
        else return 0;
    }
    return -1;
}

int test16(void){
    DiGraph g;
    g.addNode("A");
    g.addNode("B");
    g.addNode("C");
    g.addEdge("A", "B", 0.2);
    g.addEdge("B", "C", 0.3);
    try{
        g.chWeight("D", "B", 0.2 , 0.5);
    }catch(DigraphExeption e){
        if(e.getCode() != 16) return -1;
        else return 0;
    }
    return -1;
}


int main(){
    string tester;
    cout << "run the test? (y = yes)" << endl;
    cin >> tester;
    if(tester == "y") {
        std::cout << "Test 1  : Add one node twice" << endl;
        cout << "Test 2  : Add an edge with nodes that dont exists" << endl;
        cout << "Test 3  : Add one edge twice" << endl;
        cout << "Test 4  : Get edges of an not existing node" << endl;
        cout << "Test 5  : Get neighbour of an not existing node" << endl;
        cout << "Test 6  : Open an not existing file" << endl;
        cout << "Test 7  : Opening a file with wrong syntax to add a node" << endl;
        cout << "Test 8  : Opening a file with wrong float to add an edge " << endl;
        cout << "Test 9  : Opening a file with wrong syntax to add an edge" << endl;
        cout << "Test 10 : Delete node with incoming edges" << endl;
        cout << "Test 11 : Delete node with outgoing edges" << endl;
        cout << "Test 12 : Delete node with wrong key" << endl;
        cout << "Test 13 : Delete edge with wrong startnode" << endl;
        cout << "Test 14 : Delete edge with wrong endnode and wrong weight" << endl;
        cout << "Test 15 : Change weight with wrong endnode and wrong oldweight" << endl;
        cout << "Test 16 : change weight with wrong startnode" << endl;
        cout << endl << "Press Enter To Start Tests";
        cin.ignore();
        cout << endl;

        if (test1() == 0) cout << "Test 1            succeeded" << endl;
        else cout << "\nTest 1            failed\n" << endl;
        if (test2() == 0) cout << "Test 2            succeeded" << endl;
        else cout << "\nTest 2            failed\n" << endl;
        if (test3() == 0) cout << "Test 3            succeeded" << endl;
        else cout << "\nTest 3            failed\n" << endl;
        if (test4() == 0) cout << "Test 4            succeeded" << endl;
        else cout << "\nTest 4            failed\n" << endl;
        if (test5() == 0) cout << "Test 5            succeeded" << endl;
        else cout << "\nTest 5            failed\n" << endl;
        if (test6() == 0) cout << "Test 6            succeeded" << endl;
        else cout << "\nTest 6            failed\n" << endl;
        if (test7() == 0) cout << "Test 7            succeeded" << endl;
        else cout << "\nTest 7            failed\n" << endl;
        if (test8() == 0) cout << "Test 8            succeeded" << endl;
        else cout << "\nTest 8            failed\n" << endl;
        if (test9() == 0) cout << "Test 9            succeeded" << endl;
        else cout << "\nTest 9            failed\n" << endl;
        if (test10() == 0) cout << "Test 10           succeeded" << endl;
        else cout << "\nTest 10           failed\n" << endl;
        if (test11() == 0) cout << "Test 11           succeeded" << endl;
        else cout << "\nTest 11           failed\n" << endl;
        if (test12() == 0) cout << "Test 12           succeeded" << endl;
        else cout << "\nTest 12           failed\n" << endl;
        if (test13() == 0) cout << "Test 13           succeeded" << endl;
        else cout << "\nTest 13           failed\n" << endl;
        if (test14() == 0) cout << "Test 14           succeeded" << endl;
        else cout << "\nTest 14           failed\n" << endl;
        if (test15() == 0) cout << "Test 15           succeeded" << endl;
        else cout << "\nTest 15           failed\n" << endl;
        if (test16() == 0) cout << "Test 16           succeeded" << endl;
        else cout << "\nTest 16           failed\n" << endl;
    }
    string restore;
    DiGraph *g;
    cout << "restore graph from file (y = yes)";
    cin >> restore;
    if(restore == "y"){
        try{
            g = new DiGraph("_graph.txt");
        }catch(DigraphExeption e){
            cout << endl << "Error : " << e.getError() << endl << e.getInvolved() << endl;
            cout << e.getHint() << endl << endl;
            exit(-1);
        }
    }else{
        g = new DiGraph;
    }
    DiGraphVisualizer v;
    while(1){
        string ein;
        cout << "------------------------------------------" << endl;
        cout << " n : new node\n e : new edge\n v : visualize\n w : change weight\n";
        cout << " s : save\ndn : delete node\nde : delete edge\n";
        cout << "ka : killall Nodes and Edges\n q : quit\n ";
        cin >> ein;
        if(ein == "n"){
            cout << "------------------------------------------" << endl;
            string key;
            cout << "New Node         Key     : ";
            cin >> key;
            try{
                g->addNode(key);
            }catch(DigraphExeption e){
                cout << endl << "Error : " << e.getError() << endl << e.getInvolved() << endl;
                cout << e.getHint() << endl << endl;
            }
        }else if(ein == "e"){
            cout << "------------------------------------------" << endl;
            string snode, enode;
            float weight;
            cout << "New Edge         Startnode : ";
            cin >> snode;
            cout << "                 Endnode   : ";
            cin >> enode;
            cout << "                 Weight    : ";
            cin >> weight;
            try{
                g->addEdge(snode, enode, weight);
            }catch(DigraphExeption e){
                cout << endl << "Error : " << e.getError() << endl << e.getInvolved() << endl;
                cout << e.getHint() << endl << endl;
            }
        }else if(ein == "v"){
            v.visualize(*g, "_graph");
            system("open _graph.png");
        }else if(ein == "s"){
            g->save("_graph.txt");
        }else if(ein == "dn"){
            cout << "------------------------------------------" << endl;
            string key2;
            cout << "Delete Node      Key     : ";
            cin >> key2;
            try{
                g->delNode(key2);
            }catch(DigraphExeption e){
                cout << endl << "Error : " << e.getError() << endl << e.getInvolved() << endl;
                cout << e.getHint() << endl << endl;
            }
        }else if(ein == "de"){
            cout << "------------------------------------------" << endl;
            string snode2, enode2;
            float weigt2;
            cout << "Delete Edge      Startnode : ";
            cin >> snode2;
            cout << "                 Endnode   : ";
            cin >>  enode2;
            cout << "                 Weight    : ";
            cin >> weigt2;
            try{
                g->delEdge(snode2, enode2, weigt2);
            }catch(DigraphExeption e){
                cout << endl << "Error : " << e.getError() << endl << e.getInvolved() << endl;
                cout << e.getHint() << endl << endl;
            }
        }else if(ein == "w"){
            cout << "------------------------------------------" << endl;
            string snode3, enode3;
            float oweight, nweigth;
            cout << "Edge            Startnode  : ";
            cin >> snode3;
            cout << "                Endnode    : ";
            cin >> enode3;
            cout << "                Old Weight : ";
            cin >> oweight;
            cout << "                New Weight : ";
            cin >> nweigth;
            try{
                g->chWeight(snode3, enode3, oweight, nweigth);
            }catch(DigraphExeption e){
                cout << endl << "Error : " << e.getError() << endl << e.getInvolved() << endl;
                cout << e.getHint() << endl << endl;
            }
        }else if(ein == "ka"){
            g->killNodes();
        }else if(ein == "q"){
            cout << "delete _graph.dot and _graph.png (y = yes, else = no)";
            cin >> ein;
            if(ein == "y"){
                system("rm _graph.dot _graph.png");
            }
            break;
        }
    }
    return 0;
}

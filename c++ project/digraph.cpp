#include "headerfile.hpp"
#include <string>
#include <fstream>
#include <iostream>


using namespace std;

void DiGraph::addNode(string key){
    for(int i = 0; i < _nodes.size(); i++){
        if(_nodes[i]->getKey() == key){
            DigraphExeption e;
            e.setError("node with key already exists");
            e.setInvolved(key + " | addNode");
            e.setCode(1);
            throw e;
        }
    }
    _nodes.append(new Node(key));
}

void DiGraph::addEdge(string key1, string key2, float weight){
    Node *start = NULL;
    Node *end = NULL;
    for(int i = 0; i < _nodes.size(); i++){
        if(_nodes[i]->getKey() == key1){
            start = _nodes[i];
        }else if(_nodes[i]->getKey() == key2){
            end = _nodes[i];
        }
    }
    if((start == NULL) || (end == NULL)){
        DigraphExeption e;
        e.setInvolved(key1 + " | " + key2 + " | addEdge");
        e.setError("no node with that key");
        e.setCode(2);
        throw e;
    }
    for(int i = 0; i < start->getEdges().size(); i++){
        if((start->getEdges()[i]->getEndNode() == end) && (start->getEdges()[i]->getWeight() == weight)){
            DigraphExeption e;
            e.setInvolved(key1 + " | " + key2 + " | " + to_string(weight) + " | addEdge");
            e.setError("edge already exists");
            e.setCode(3);
            throw e;
        }
    }
    start->setNewEdge(new Edge(start, end, weight));
}

Liste<Node*> DiGraph::getNeighbours(string key){
    Liste<Node*> ret;
    for(int i = 0; i < _nodes.size(); i++){
        if(_nodes[i]->getKey() == key)break;
        if(i == (_nodes.size() - 1)){
            DigraphExeption e;
            e.setInvolved(key + " | getNeighbours");
            e.setError("no node with that key");
            e.setCode(4);
            throw e;
        }
    }
    for(int i = 0; i < _nodes.size(); i++){
        if(_nodes[i]->getKey() == key){
            for(int j = 0; j < _nodes[i]->getEdges().size(); j++){
                ret.append(_nodes[i]->getEdges()[j]->getEndNode());
            }
        }else{
            for(int j = 0; j < _nodes[i]->getEdges().size(); j++){
                if(_nodes[i]->getEdges()[j]->getEndNode()->getKey() == key){
                    ret.append(_nodes[i]);
                }
            }
        }
    }
    return ret;
}

Liste<Edge*> DiGraph::getEdges(string key){
    for(int i = 0; i < _nodes.size(); i++){
        if(_nodes[i]->getKey() == key){
            return _nodes[i]->getEdges();
        }
    }
    DigraphExeption e;
    e.setInvolved(key + " | getEdges");
    e.setError("no node with that key");
    e.setCode(5);
    throw e;
}

Liste<Node*> DiGraph::getNodes(void){
    return _nodes;
}

DiGraph::DiGraph(void){

}

DiGraph::DiGraph(string filename){
    ifstream file;
    file.open(filename);
    if(!file.is_open()){
        DigraphExeption e;
        e.setInvolved(filename  + " | openFile Constructor");
        e.setError("unable to open file");
        e.setCode(6);
        throw e;
    }
    string line;
    string operation;
    while(getline(file, line)){
        Tokenizer tokenizer(line, " ");
        Tokenizer edgetoken(line, " ");
        if(line == "#ende"){
            break;
        }else if("*" == tokenizer.nextToken()){
            try{
                this->addNode(tokenizer.nextToken());
            }catch(DigraphExeption e){
                throw e;
            }catch(...){
                DigraphExeption e;
                e.setInvolved(filename + " | " + line + " | " + "openFile Constructor");
                e.setError("wrong synthax!");
                e.setHint("To make node use format\n*");
                e.setCode(7);
                throw e;
            }
        }else if("-" == edgetoken.nextToken()){
            float weight;
            string key1, key2, w;
            int j = 0;
            try{
                for(int i = 0; line.find(" ", i + 1) != -1; i = line.find(" ", i + 1)){
                    j++;
                }
                if(j != 3){
                    throw " ";
                }
                key1 = edgetoken.nextToken();
                // cout << key1 << endl;
                key2 = edgetoken.nextToken();
                //cout << key2 << endl;
                w = edgetoken.nextToken();
                //cout << w << endl;
                try{
                    weight = stof(w.c_str());
                }catch(...){
                    DigraphExeption e;
                    e.setInvolved(filename + " | " + line + " | " + "openFile Constructor");
                    e.setError("cant make float from 3rd argument!");
                    e.setHint("To make edge use format\n- key1 key2 weight");
                    e.setCode(8);
                    throw e;
                }
            }catch(DigraphExeption e){
                throw e;
            }catch(...){
                DigraphExeption e;
                e.setInvolved(filename + " | " + line + " | " + "openFile Constructor");
                e.setError("wrong synthax!");
                e.setHint("To make edge use format\n- key1 key2 weight");
                e.setCode(9);
                throw e;
            }
            try{
                this->addEdge(key1, key2, weight);
            }catch(DigraphExeption e){
                throw e;
            }
        }else{
            cout << "--------------------------------------------" << endl;
            cout << "Warning | Comentary belongs after (#ende)" << endl;
            cout << "        | Not use empty lines before (#ende)"<< endl;
            cout << "\"" << line << "\"" << endl;
            cout << "--------------------------------------------" << endl;
        }
    }
    file.close();
}

/*
void DiGraph::save(string filename){
    ofstream file;
    file.open(filename);
    file << "#" << " "<< "Alle" <<" "<< "Knoten" << endl;
    for(int i = 0; i < this->getNodes().size(); i++) {
        file << this->getNodes()[i]->getKey() << endl;
    }
    file << "#" << " "<< "Alle" <<" "<< "Kante" << endl;
    for(int j = 0; j < this->getNodes().size(); j++){
        string key = this->getNodes()[j]->getKey();
        for(int i = 0; i < this->getEdges(key).size(); i++){
            file << this->getEdges(key)[i]->getStartNode()->getKey() << " ";
            file << this->getEdges(key)[i]->getEndNode()->getKey() << " ";
            file << this->getEdges(key)[i]->getWeight() << endl;
        }
    }
    file << "#ende" << endl;
    file.close();
} */


void DiGraph::save(string filename){
    ofstream file;
    file.open(filename);
    for(int i = 0; i < this->getNodes().size(); i++){
        file << "* " << this->getNodes()[i]->getKey() << endl;
    }
    for(int j = 0; j < this->getNodes().size(); j++){
        string key = this->getNodes()[j]->getKey();
        for(int i = 0; i < this->getEdges(key).size(); i++){
            file << "- " << this->getEdges(key)[i]->getStartNode()->getKey() << " ";
            file << this->getEdges(key)[i]->getEndNode()->getKey() << " ";
            file << this->getEdges(key)[i]->getWeight() << endl;
        }
    }
    file << "#ende" << endl;
    file << "\n--------------------------------------\n" << endl;
    file << "LEGENDE:" << endl;
    file << "*" << " " << "steht für nodes" << endl;
    file << "-" << " " << "steht für edges" << endl;
    file.close();
}

DiGraph::~DiGraph(void){
}

void DiGraph::delNode(string key){
    for(int i = 0; i < _nodes.size(); i++){
        for(int j = 0; j < _nodes[i]->getEdges().size(); j++){
            if(_nodes[i]->getEdges()[j]->getEndNode()->getKey() == key){
                DigraphExeption e;
                e.setInvolved(key + " | delNode");
                e.setError("node cant be deleted because it has incomming edges");
                e.setHint("delete all incomming edges first\nNode may has outgoing edges too");
                e.setCode(10);
                throw e;
            }
        }
    }
    for(int i = 0; i < _nodes.size(); i++){
        if((_nodes[i]->getKey() == key) && (_nodes[i]->getEdges().size() > 0)){
            DigraphExeption e;
            e.setInvolved(key + " | delNode");
            e.setError("node cant be deleted because it has outgoing edges");
            e.setHint("delete all outgoing edges first");
            e.setCode(11);
            throw e;
        }
        if(_nodes[i]->getKey() == key){
            _nodes.remove(_nodes[i]);
            return;
        }
    }
    DigraphExeption e;
    e.setInvolved(key + "| delNode");
    e.setError("not existing node cant be deleted");
    e.setHint("check for node spelling");
    e.setCode(12);
    throw e;
}

void DiGraph::delEdge(string key1, string key2, float weight){
    for(int i = 0; i < _nodes.size(); i++){
        if(_nodes[i]->getKey() == key1){
            try{
                _nodes[i]->delEdge(key2, weight);
            }catch(...){
                DigraphExeption e;
                e.setInvolved(key2 + " | " + to_string(weight) + " | delEdge");
                e.setError("not existing edge cant be delete");
                e.setHint("check for endnode spelling and correct weight");
                e.setCode(14);
                throw e;
            }
            return;
        }
    }
    DigraphExeption e;
    e.setInvolved(key1 + " | delEdge");
    e.setError("not existing edge cant be delete");
    e.setHint("check for startnode spelling");
    e.setCode(13);
    throw e;
}

void DiGraph::killNodes(void){
    while(_nodes.size() != 0){
        _nodes[0]->killEdges();
        _nodes.remove(0);
    }
}

void DiGraph::chWeight(string key1, string key2, float oweight, float nweight){
    for(int i = 0; i < _nodes.size(); i++){
        if(_nodes[i]->getKey() == key1){
            try{
                _nodes[i]->chWeight(key2, oweight, nweight);
            }catch(...){
                DigraphExeption e;
                e.setInvolved(key2 +" | "+ to_string(oweight) +" | "+ to_string(nweight) +" | chWeight");
                e.setError("not existing edge cant be changed");
                e.setHint("check for endnode spelling and correct old weight");
                e.setCode(15);
                throw e;
            }
            return;
        }
    }
    DigraphExeption e;
    e.setInvolved(key1 +" | "+ key2 +" | "+ to_string(oweight) +" | "+ to_string(nweight) +" | chWeight");
    e.setError("not existing edge cant be changed");
    e.setHint("check for startnode spelling");
    e.setCode(16);
    throw e;
}

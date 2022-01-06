#include <iostream>
#include <fstream>
#include "graphgenerator.h"
#include "graphoperator.h"

using namespace std;

int main(int argc, char** argv){
    GraphGenerator g;
    GraphOperator o;
    fstream infile;
    string line;
    infile.open(argv[1]);
    while(getline(infile, line)){
        g.insertEdge(line);
    }

    cout << "The in order traversal:" << endl;
    g.inOrder();
    cout << "The pre order traversal:" << endl;
    g.preOrder();
    cout << "Is acyclic(Yes/No):" << endl;
    bool acyc = o.isAcyclic(g);
    if(acyc == true){
        cout << "Yes" << endl;
    }
    else{
        cout << "No" << endl;
    }
    cout << "Connected Components:" << endl;
    o.connectedComponents(g);
}
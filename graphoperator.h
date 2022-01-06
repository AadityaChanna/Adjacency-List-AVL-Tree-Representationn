#ifndef GRAPHOPERATOR_H
#define GRAPHOPERATOR_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include "graphgenerator.h"

using namespace std;

class GraphOperator{
    public:
    bool isAcyclic(GraphGenerator g){
        Node<int>* n1 = g.getHead();
        vector<bool> visited;
        visited.reserve(10);
        //return depthFirstSearch(n1, visited, n1);
        bool acyc = true;
        for(int i = 1; i < visited.capacity(); i++){
            if(visited[i] != true && g.lookup(i) != nullptr){
                Node<int>* node = g.lookup(i);
                acyc = acyc && depthFirstSearch(node, visited, nullptr);
                if(!acyc){
                    return false;
                }
            }
        }
        return true;
    }

    bool depthFirstSearch(Node<int>* node, vector<bool>& visited, Node<int>* parent){
        //cout << node->data << endl;
        while(node->data > visited.capacity()){
            int size = visited.capacity();
            visited.resize(size * 2);
        }
        if(visited[node->data] == true){
            return false;
        }
        visited[node->data] = true;

        LinkedListNode<Node<int>*>* p = node->head;
        bool acyc = true;
        while(p != nullptr){
            if(p->data != parent)
                acyc = acyc && depthFirstSearch(p->data, visited, node);
                if(!acyc){
                    return false;
                }

            p = p->next;
        }

        return true;
    }

    
    void connectedComponents(GraphGenerator g){
        Node<int>* n1 = g.getHead();
        vector<bool> visited(100, false);
        //breathFirstSearch(n1, visited);
        for(int i = 1; i < visited.capacity(); i++){
            if(visited[i] != true && g.lookup(i) != nullptr){
                Node<int>* node = g.lookup(i);
                breathFirstSearch(node, visited);
            }
        }
    }

    void breathFirstSearch(Node<int>* node, vector<bool>& visited){
        while(node->data > visited.capacity()){
            int size = visited.capacity();
            visited.resize(size * 2, false);
        }

        list<Node<int>*> queue;
        visited[node->data] = true;
        queue.push_back(node);
        
        LinkedListNode<Node<int>*>* headP;
        vector<int> connectedList;
        while(!queue.empty()){
            Node<int>* value = queue.front();
            connectedList.push_back(value->data);
            queue.pop_front();
            headP = value->head;
            while(headP != nullptr){
                //cout << node->data << "conns" << endl;
                if(visited[headP->data->data] != true){
                    visited[headP->data->data] = true;
                    queue.push_back(headP->data);
                }
                headP = headP->next;
            }
        }

        sort(connectedList.begin(), connectedList.end());
        for(int i = 0; i < connectedList.size(); i++){
            cout << connectedList[i] << " ";
        }

        cout << endl;

        return;
    }
};

#endif
#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "avltree.h"

using namespace std;

class GraphGenerator{
    private:
    AVLTree<int> graph;

    public:
    void insertVertex(int vertex){
        graph.insert(vertex);
    }

    void insertEdge(string edge){
        //cout << edge << endl;
        std::string::size_type pos = edge.find(',');
        int vertex1 = stoi(edge.substr(0, pos));
        int vertex2 = stoi(edge.substr(pos+1));
    
        if(graph.lookup(vertex1) == nullptr){
            //cout << vertex1 << endl;
            graph.insert(vertex1);
        }
        if(graph.lookup(vertex2) == nullptr){
            //cout << vertex2 << endl;
            graph.insert(vertex2);
            
        }
        //cout << "here" << endl;
        Node<int>* node1 = graph.lookup(vertex1);
        Node<int>* node2 = graph.lookup(vertex2);

        // if(node1->head == nullptr){
        //     cout << node1->data << endl;
        // }

        // if(node2->head == nullptr){
        //     cout << node2->data << endl;
        // }
        if(node1->head == nullptr){
            LinkedListNode<Node<int>*>* newNode = new LinkedListNode<Node<int>*>;
            newNode->data = node2;
            newNode->next = nullptr;
            node1->head = newNode;
        }
        else{
            LinkedListNode<Node<int>*>* temp = node1->head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            LinkedListNode<Node<int>*>* newNode = new LinkedListNode<Node<int>*>;
            newNode->data = node2;
            newNode->next = nullptr;
            temp->next = newNode; 
        }
        if(node2->head == nullptr){
            LinkedListNode<Node<int>*>* newNode = new LinkedListNode<Node<int>*>;
            newNode->data = node1;
            newNode->next = nullptr;
            node2->head = newNode;
        }
        else{
            LinkedListNode<Node<int>*>* temp = node2->head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            LinkedListNode<Node<int>*>* newNode = new LinkedListNode<Node<int>*>;
            newNode->data = node1;
            newNode->next = nullptr;
            temp->next = newNode; 
        }

     
    }

    Node<int>* lookup(int data){
        Node<int>* node1 = graph.lookup(data);
        return node1;
    }

    void inOrder(){
        graph.inOrder();
    }

    void preOrder(){
        graph.preOrder();
    }

    Node<int>* getHead(){
        return graph.getHead();
    }

};

#endif
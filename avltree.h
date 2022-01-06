#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
struct LinkedListNode{
    T data;
    LinkedListNode<T>* next;
};

template <typename T>
struct Node{
    T data;
    Node<T>* left = nullptr;
    Node<T>* right = nullptr;
    Node<T>* parent = nullptr;
    int height = 1;
    LinkedListNode<Node<T>*>* head = nullptr;
};


template <typename T>
class AVLTree{
    private:
    Node<T>* head = nullptr;

    public:

    AVLTree(){
        head = nullptr;
    }

    void insert(T data){
        Node<T>* n1 = new Node<T>;
        n1->data = data;
        if(head == nullptr){
            head = n1;
            return;
        }
        Node<T>* parent = nullptr;
        Node<T>* compareTo = head;
        
        while(compareTo != nullptr){
            if(n1->data > compareTo->data){
                parent = compareTo;
                compareTo = compareTo->right;
            }
            else if(n1->data < compareTo->data){
                parent = compareTo;
                compareTo = compareTo->left;
            }
            else{
                cout << "No duplicates in AVL Tree." << endl;
                return;
            }
        }
        
        if(n1->data > parent->data){
            parent->right = n1;
        }
        else{
            parent->left = n1;
        }
        n1->parent = parent;
        n1->left = nullptr;
        n1->right = nullptr;
        
        Node<T>* p = n1->parent;
        while(p != nullptr){
            setHeight(p);
        
            p = p->parent;
        }
        
        balanceTree(n1, data);
    }

    Node<T>* rightRotate(Node<T>* node){
        Node<T>* temp = node->left;
        Node<T>* temp2 = temp->right;

        temp->right = node;
        node->left = temp2;

        temp->parent= node->parent;
        node->parent = temp;
        if(temp2 != nullptr){
            temp2->parent = node;
        }

        return temp;
    }

    Node<T>* leftRotate(Node<T>* node){
        Node<T>* temp = node->right;
        Node<T>* temp2 = temp->left;

        temp->left = node;
        node->right = temp2;

        temp->parent = node->parent;
        node->parent = temp;
        if(temp2 != nullptr){
            temp2->parent = node;
        }

        return temp;
    }

    int getBalance(Node<T>* node){
        if(node == nullptr)
            return 0;


        return getHeight(node->left) - getHeight(node->right);
    }

    int getHeight(Node<T>* node){
        if(node == nullptr)
            return 0;
        return node->height;
    }

    void setHeight(Node<T>* node){
        if(node!= nullptr)
            node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    }


    void balanceTree(Node<T>* node, T dataInsert){
        if(node == nullptr){
            return;
        }
        //cout << node->data <<endl;
        Node<T>* rootNode = node;
        setHeight(node);
        int balance = getBalance(node);
        if(balance > 1 && dataInsert < node->left->data){
            rightRotate(node);
            rootNode = node->parent;
            if(rootNode->parent != nullptr)
                setParent(node);
            else
                head = rootNode;

            setTreeHeight(rootNode);
        }
        else if(balance < -1 && dataInsert > node->right->data){
            leftRotate(node);
            rootNode = node->parent;
            if(rootNode->parent != nullptr)
                setParent(node);
            else{
                head = rootNode;
            }

            setTreeHeight(rootNode);
        }
        else if(balance > 1 && dataInsert > node->left->data){
            node->left = leftRotate(node->left);
            rightRotate(node);
            rootNode = node->parent;
            if(rootNode->parent != nullptr)
                setParent(node);
            else
                head = rootNode;

            setTreeHeight(rootNode);
        }
        else if(balance < -1 && dataInsert < node->right->data){
            node->right = rightRotate(node->right);
            leftRotate(node);
            rootNode = node->parent;
            if(rootNode->parent != nullptr)
                setParent(node);
            else
                head = rootNode;

            setTreeHeight(rootNode);
        }
        setHeight(rootNode->left);
        setHeight(rootNode->right);
        setHeight(rootNode);

        // if(rootNode->left != nullptr && rootNode->right != nullptr){
        //     cout << rootNode->left->height << " " << rootNode->right->height <<" " << rootNode->height << endl;
        //     cout << rootNode->left->data << " " << rootNode->right->data << " " << rootNode->data << endl;
        // }
        balanceTree(rootNode->parent, dataInsert);
    }

    void setTreeHeight(Node<T>* node){
        if(node == nullptr){
            return;
        }
        setTreeHeight(node->left);
        setTreeHeight(node->right);
        setHeight(node);
    }

    void setParent(Node<T>* node){
        if(node->parent->parent->left == node){
            node->parent->parent->left = node->parent;
        }
        else{
            node->parent->parent->right = node->parent;
        }
    }

    Node<T>* lookup(int data){
        Node<T>* currNode = head;
        while(currNode != nullptr && currNode->data != data){
            if(data > currNode->data){
                currNode = currNode->right;
            }
            else{
                currNode = currNode->left;
            }
        }
        if(currNode == nullptr){
            return nullptr;
        }
        else{
            return currNode;
        }
    }

    void inOrder(){
        printInOrder(head);
        cout << endl;
    }

    void printInOrder(Node<T>* node){
        if(node == nullptr){
            return;
        }
        printInOrder(node->left);
        cout << node->data << " ";
        printInOrder(node->right);
    }

    void preOrder(){
        printPreOrder(head);
        cout << endl;
    }

    void printPreOrder(Node<T>* node){
        if(node == nullptr){
            return;
        }

        cout << node->data << " ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }

    Node<T>* getHead(){
        return head;
    }
};
#endif
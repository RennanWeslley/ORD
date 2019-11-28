#ifndef TREE_H
#define TREE_H

#include <sstream>
#include <iostream>

typedef struct data {
    char c;
    int f;
} data_t;

class Node {
    public:
        data_t data;
        Node *left;
        Node *right;
        
        Node();
        Node(data_t);
        
        void setData(data_t);
        void setC(char);
        void setF(int);
        void setSumF();
        void setL(Node *);
        void setR(Node *);
        
        bool isLeaf();
        
        data_t getData();
        char getC();
        int getF();
        Node *getL();
        Node *getR();
};

typedef Node *Tree;

/*  PREORDER TRAVERSAL */
bool empty(Tree);
void preOrder(Tree);

#endif //TREE_H

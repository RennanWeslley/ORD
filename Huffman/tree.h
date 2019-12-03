#ifndef TREE_H
#define TREE_H

#include <sstream>
#include <iostream>

typedef struct data {
    unsigned char c;
    int f;
} data_t;

class Node {
    private:
        bool emptyT(Node *);
        void preOrderT(Node *); /* PREORDER TRAVERSAL */
        
    public:
        data_t data;
        Node *left;
        Node *right;
        
        Node();
        Node(data_t);
        
        void setData(data_t);
        void setC(unsigned char);
        void setF(int);
        void setSumF();
        void setL(Node *);
        void setR(Node *);
        
        void preOrder();
        bool empty();
        bool isLeaf();
        
        data_t getData();
        unsigned char getC();
        int getF();
        Node *getL();
        Node *getR();
};

typedef Node *Tree;

bool isEqual(Tree, Tree);

#endif //TREE_H

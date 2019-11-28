#include "tree.h"

Node::Node() {
    data.c = '/';
    data.f = 0;
    left = NULL;
    right = NULL;
}

Node::Node(data_t data) {
    this->data = data;
    left = NULL;
    right = NULL;
}

void Node::setData(data_t data) {
    this->data = data;
}

void Node::setC(char c) {
    data.c = c;
}

void Node::setF(int f) {
    data.f = f;
}

void Node::setSumF() {
    int sum = 0;
    
    if(left)
        sum += left->data.f;
    
    if(right)
        sum += right->data.f;
    
    if(sum)
        data.f = sum;
}

void Node::setL(Node *left) {
    this->left = left;
}

void Node::setR(Node *right) {
    this->right = right;
}

bool Node::isLeaf() {
    return !left && !right;
}

data_t Node::getData() {
    return data;
}

char Node::getC() {
    return data.c;
}

int Node::getF() {
    return data.f;
}

Node* Node::getL() {
    return left;
}

Node* Node::getR() {
    return right;
}

bool empty(Tree root) {
    return !root;
}

void preOrder(Tree root) {
    if(empty(root))
        return;
    
    char c[5] = {'\0'};
    c[0] = root->data.c;
    
    if(c[0] == '\0') {
        c[0] = 'N';
        c[1] = 'U';
        c[2] = 'L';
        c[3] = 'L';
    }
    
    std::cout << "(" << c << ", " << root->data.f << ", " << "["; 
    
    if(root->left) {
        char cl[5] = {'\0'};
        cl[0] = root->left->data.c;
        
        if(cl[0] == '\0') {
            cl[0] = 'N';
            cl[1] = 'U';
            cl[2] = 'L';
            cl[3] = 'L';
        }
        
        std::cout << "{" << cl << ", " << root->left->data.f << "}";
    }
    
    if(root->right) {
        char cr[5] = {'\0'};
        cr[0] = root->right->data.c;
        
        if(cr[0] == '\0') {
            cr[0] = 'N';
            cr[1] = 'U';
            cr[2] = 'L';
            cr[3] = 'L';
        }
        
        std::cout << ", {" << cr << ", " << root->right->data.f << "}";
    }
        
        
    std::cout << "])" << std::endl << std::endl;
    
    preOrder(root->left);
    
    preOrder(root->right);
}

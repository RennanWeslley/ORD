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

void Node::setC(unsigned char c) {
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

void Node::increaseF() {
    data.f++;
}

bool Node::isLeaf() {
    return !left && !right;
}

data_t Node::getData() {
    return data;
}

unsigned char Node::getC() {
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
    
    unsigned char c[5] = {'\0'};
    c[0] = root->data.c;
    
    if(c[0] == '\0') {
        c[0] = 'N';
        c[1] = 'U';
        c[2] = 'L';
        c[3] = 'L';
    }
    
    std::cout << "(" << c << ", " << root->data.f << ", " << "["; 
    
    if(root->left) {
        unsigned char cl[5] = {'\0'};
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
        unsigned char cr[5] = {'\0'};
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

bool isEqual(Tree r, Tree t) {
    if((empty(r) && !(empty(t))) || (!(empty(r)) && empty(t)))
        return false;
        
    if(empty(r) && empty(t))
        return true;
    
    if((r->data.c != t->data.c) || (r->data.f != t->data.f))
        return false;
    
    if(isEqual(r->left, t->left) && isEqual(r->right, t->right))
        return true;
    else
        return false;
}

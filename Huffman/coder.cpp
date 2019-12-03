#include "coder.h"

void Coder::huffmanTree() {
    Node *t, *l, *r;
    
    while(h.getSize() > 1) {
        t = new Node();
        l = (Node *) malloc(sizeof(Node));
        r = (Node *) malloc(sizeof(Node));
        
        if(!h.empty()) {
            *l = h.extract_min();
            t->setL(l);
        }
        
        if(!h.empty()) {
            *r = h.extract_min();
            t->setR(r);
        }
        
        t->setSumF();
        
        h.insert_key(*t);
    }
    
    t = (Node *) malloc(sizeof(Node));
    *t = h.extract_min();
    
    this->r = t;
}

void Coder::freeHuffmanTree(Tree root) {
    if(root->empty())
        return;
    
    freeHuffmanTree(root->left);
    
    freeHuffmanTree(root->right);
    
    free(root);
}

void Coder::freeTree() {
    freeHuffmanTree(r);
}

Tree Coder::getTree() {
    return r;
}

bool bitCompare(std::bitset<1> bit1, std::bitset<1> bit2) {
    return (~(bit1 ^ bit2) == 0b1);
}

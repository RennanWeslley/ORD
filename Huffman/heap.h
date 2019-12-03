#ifndef HEAP_H
#define HEAP_H

#include "tree.h"
#include <vector>

class Heap {
    private:
        std::vector<Node> data;
        int size;
        int comp;

    public:
        Heap();
        Heap(int);
        Heap(std::vector<Node>, int);
        
        unsigned char getC(int);
        int getF(int);
        int getParent(int);
        int getLeft(int);
        int getRight(int);
        int getSize();
        std::vector<Node> getData();
        
        void setSize(int);
        void setC(int, unsigned char);
        void setF(int, int);
        void setData(std::vector<Node>);
        
        bool empty();
        
        void min_heapify(int);
        void build_min_heap();
        int sizeDec();
        int sizeInc();
        
        Node heap_minimum();
        Node extract_min();
        void decrease_key(int, int);
        void insert_key(Node);
        
        std::string toString();
};

bool isHeap(std::vector<Node>, int, int); /* Is min heap */
bool isEqualH(Heap, Heap);

#endif //HEAP_H

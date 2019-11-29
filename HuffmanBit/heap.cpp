#include "heap.h"

Heap::Heap() {
    size = comp = 0;
}

Heap::Heap(int size) {
    this->size = size;
    comp = size;
}

Heap::Heap(std::vector<Node> data, int size) {
    this->data = data;
    this->size = size;
    comp = size;
}

char Heap::getC(int i) {
    return data[i].data.c;
}

int Heap::getF(int i) {
    return data[i].data.f;
}

int Heap::getParent(int i) {
    return i/2;
}

int Heap::getLeft(int i) {
    return 2*i;
}

int Heap::getRight(int i) {
    return 2*i + 1;
}

int Heap::getSize() {
    return size;
}

std::vector<Node> Heap::getData() {
    return data;
}

bool Heap::empty() {
    return !size;
}

void Heap::setSize(int size) {
    this->size = size;
}

void Heap::setC(int i, char c) {
    data[i].data.c = c;
}

void Heap::setF(int i, int f) {
    data[i].data.f = f;
}

void Heap::setData(std::vector<Node> data) {
    this->data = data;
    size = data.size();
    comp = size;
}

void Heap::min_heapify(int i) {
    if(empty())
        return;
    
    int l = getLeft(i),
        r = getRight(i),
        u;
    
    if(l <= size && data[l-1].data.f < data[i-1].data.f)
        u = l;
    else
        u = i;
    
    if(r <= size && data[r-1].data.f < data[u-1].data.f)
        u = r;
    
    if(u != i) {
        std::swap(data[i-1], data[u-1]);
        
        min_heapify(u);
    }
}

void Heap::build_min_heap() {
    for(int i = size/2; i > 0; i--)
        min_heapify(i);
}

int Heap::sizeDec() {
    return --size;
}

int Heap::sizeInc() {
    return ++size;
}

Node Heap::heap_minimum() {
    return data[0];
}

Node Heap::extract_min() {
    Node aux = data[0];

    data[0] = data[size-1];
    
    data.pop_back();
    
    size--;
        
    min_heapify(1);
    
    return aux;
}

void Heap::decrease_key(int i, int key) {
    i--;
    
    if(data[i].data.f < key)
        return;
    
    data[i].data.f = key;
    
    for(; i && (data[getParent(i)].data.f > data[i].data.f); i = getParent(i))
        std::swap(data[getParent(i)], data[i]);
}

void Heap::insert_key(Node key) {
    data.push_back(key);
    size++;
    comp++;
    
    for(int i = (size-1); i && (data[getParent(i-1)].data.f > data[i].data.f); i = getParent(i))
        std::swap(data[getParent(i-1)], data[i]);
}

std::string Heap::toString() {
    if(empty())
        return "Heap is empty\n";
    
    std::stringstream c, f, s;
    std::string show = "Heap.: {";
    
    for(int i = 0; i < size; i++) {
        c << data[i].data.c;
        f << data[i].data.f;
        
        if((i+1) == size) {
            show += "(" + c.str() + ", " + f.str() + ")" + "}";
            break;
        }
        else
            show += "(" + c.str() + ", " + f.str() + ")" + ", ";
        
        c.str("");
        f.str("");
    }
    
    s << size;
    
    return show + "\nTam: " + s.str();
}

//is min heap
bool isHeap(std::vector<Node> arr, int i, int size) {
    if(i > (size/2))
        return true;
    
    if(!i)
        i++;
    
    int left = 2*i;
    int right = 2*i + 1;
    
    if((left <= size && (arr[i-1].data.f > arr[left-1].data.f || !isHeap(arr, left, size))) ||
      (right <= size && (arr[i-1].data.f > arr[right-1].data.f || !isHeap(arr, right, size))))
        return false;
    
    return true;
}

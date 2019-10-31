#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <sstream>

#define HEAPCOMP 101

class Heap {
    private:
        int *data;
        int size;

    public:
        Heap(int *data, int size) {
            this->data = data;
            this->size = size;
        }
        
        int getParent(int i) {
            return i/2;
        }
        
        int getLeft(int i) {
            return 2*i;
        }

        int getRight(int i) {
            return 2*i + 1;
        }
        
        bool isEmpty() {
            return size == 0;
        }
        
        int getSize() {
            return size;
        }
        
        int *getData() {
            return data;
        }
        
        void sizeDec() {
            size--;
        }
        
        std::string toString() {
            if(this->isEmpty())
                return "Heap is empty\n";
            
            std::stringstream d, s;
            std::string show = "Heap.: {";
            
            for(int i = 1; i <= size; i++) {
                d << data[i];
                
                if(i == size) {
                    show += d.str() + "}";
                    break;
                }
                else
                    show += d.str() + ", ";
                
                d.str("");
            }
            
            s << size;
            
            return show + "\nTam: " + s.str();
        }
};

void print(int *arr, int size) {
    std::cout << "{";
    for(int i = 0 ; i < size; i++)
        if((i+1) != size)
            std::cout << arr[i] << ", ";
        else
            std::cout << arr[i] << "}" << std::endl;
}

void max_heapify(Heap *h, int i) {
    if(h->isEmpty())
        return;
    
    int l = h->getLeft(i),
        r = h->getRight(i),
        u;
    
    if(l <= h->getSize() && h->getData()[l-1] > h->getData()[i-1])
        u = l;
    else
        u = i;
    
    if(r <= h->getSize() && h->getData()[r-1] > h->getData()[u-1])
        u = r;
    
    if(u != i) {
        int aux = h->getData()[i-1];
        h->getData()[i-1] = h->getData()[u-1];
        h->getData()[u-1] = aux;
        
        max_heapify(h, u);
    }
}

Heap build_max_heap(int *arr, int size) {
    Heap h(arr, size);
    
    for(int i = size/2; i > 0; i--)
        max_heapify(&h, i);
    
    print(h.getData(), size);
    
    return h;
}

void heapSort(int *arr, int size) {
    Heap h = build_max_heap(arr, size);
    
    for(int i = size-1, aux; i > 0; i--) {
        aux = arr[0];
        arr[0] = arr[i];
        arr[i] = aux;
        
        h.sizeDec();
        
        max_heapify(&h, 1);
    }
}

bool isHeap(int arr[], int i, int size) {
    if(!i)
        i++;
    
    int left = 2*i;
    int right = 2*i + 1;
    
    if(left >= size || right >= size)
        return true;
    
    if(arr[i-1] < arr[left-1] || arr[i-1] < arr[right-1])
        return false;
    
    if(!isHeap(arr, left, size) || !isHeap(arr, right, size))
        return false;
    
    return true;
}

#endif //HEAP_H

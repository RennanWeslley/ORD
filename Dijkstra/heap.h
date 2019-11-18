#ifndef HEAP_H
#define HEAP_H

#include "list.h"

class Heap {
    private:
        vex_t *data;
        int size;

    public:
        Heap(vex_t *data, int size) {
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
        
        bool empty() {
            return !size;
        }
        
        int getSize() {
            return size;
        }
        
        vex_t *getData() {
            return data;
        }
        
        void min_heapify(int i) {
            if(empty())
                return;
            
            int l = getLeft(i),
                r = getRight(i),
                u;
            
            if(l <= size && data[l-1].w < data[i-1].w)
                u = l;
            else
                u = i;
            
            if(r <= size && data[r-1].w < data[u-1].w)
                u = r;
            
            if(u != i) {
                std::swap(data[i-1], data[u-1]);
                
                min_heapify(u);
            }
        }
        
        void build_min_heap() {
            for(int i = size/2; i > 0; i--)
                min_heapify(i);
        }
        
        void sizeDec() {
            size--;
        }
        
        vex_t heap_minimum() {
            return data[0];
        }
        
        vex_t extract_min() {
            vex_t aux = data[0];
        
            data[0] = data[size-1];
            
            size--;
                
            min_heapify(1);
            
            return aux;
        }
        
        void decrease_key(int i, int key) {
            i--;
            
            if(data[i].w < key)
                return;
            
            data[i].w = key;
            
            for(; i && (data[getParent(i)].w > data[i].w); i = getParent(i))
                std::swap(data[getParent(i)], data[i]);
        }
        
        std::string toString() {
            if(empty())
                return "Heap is empty\n";
            
            std::stringstream v, w, s;
            std::string show = "Heap.: {";
            
            for(int i = 0; i < size; i++) {
                v << data[i].v;
                w << data[i].w;
                
                if((i+1) == size) {
                    show += "(" + v.str() + ", " + w.str() + ")" + "}";
                    break;
                }
                else
                    show += "(" + v.str() + ", " + w.str() + ")" + ", ";
                
                v.str("");
                w.str("");
            }
            
            s << size;
            
            return show + "\nTam: " + s.str();
        }
};

//is min heap
bool isHeap(vex_t arr[], int i, int size) {
    if(i > (size/2))
        return true;
    
    if(!i)
        i++;
    
    int left = 2*i;
    int right = 2*i + 1;
    
    if((left <= size && (arr[i-1].w > arr[left-1].w || !isHeap(arr, left, size))) ||
      (right <= size && (arr[i-1].w > arr[right-1].w || !isHeap(arr, right, size))))
        return false;
    
    return true;
}

#endif //HEAP_H

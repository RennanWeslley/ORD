#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <sstream>

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
        
        void min_heapify(int i) {
            if(this->isEmpty())
                return;
            
            int l = this->getLeft(i),
                r = this->getRight(i),
                u;
            
            if(l <= this->getSize() && this->getData()[l-1] < this->getData()[i-1])
                u = l;
            else
                u = i;
            
            if(r <= this->getSize() && this->getData()[r-1] < this->getData()[u-1])
                u = r;
            
            if(u != i) {
                std::swap(this->getData()[i-1], this->getData()[u-1]);
                
                min_heapify(u);
            }
        }
        
        void build_min_heap() {
            for(int i = size/2; i > 0; i--)
                this->min_heapify(i);
        }
        
        void sizeDec() {
            size--;
        }
        
        int heap_minimum() {
            return data[0];
        }
        
        int extract_min() {
            int aux = data[0];
        
            data[0] = data[size-1];
            
            size--;
                
            min_heapify(1);
            
            return aux;
        }
        
        void decrease_key(int i, int key) {
            i--;
            
            if(data[i] < key)
                return;
            
            data[i] = key;
            
            for(; i && (data[this->getParent(i)] > data[i]); i = this->getParent(i))
                std::swap(data[this->getParent(i)], data[i]);
        }
        
        std::string toString() {
            if(this->isEmpty())
                return "Heap is empty\n";
            
            std::stringstream d, s;
            std::string show = "Heap.: {";
            
            for(int i = 0; i < size; i++) {
                d << data[i];
                
                if((i+1) == size) {
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

void heapSort(int *arr, int size) {
    Heap h(arr, size); 
    
    h.build_min_heap();
    
    for(int i = size-1, aux; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        
        h.sizeDec();
        
        h.min_heapify(1);
    }
}

//is min heap
bool isHeap(int arr[], int i, int size) {
    if(!i)
        i++;
    
    int left = 2*i;
    int right = 2*i + 1;
    
    if(left >= size || right >= size)
        return true;
    
    if(arr[i-1] > arr[left-1] || arr[i-1] > arr[right-1])
        return false;
    
    if(!isHeap(arr, left, size) || !isHeap(arr, right, size))
        return false;
    
    return true;
}

#endif //HEAP_H

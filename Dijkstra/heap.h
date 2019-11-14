#ifndef HEAP_H
#define HEAP_H

#include "list.h"

class Vex {
    public:
        int u;
        int w;
        
        Vex() {}
        
        Vex(int u, int w) {
            this->u = u;
            this->w = w;
        }
            
        void setW(int w) {
            this->w = w;
        }
        
        int getU() {
            return u;
        }
        
        int getW() {
            return w;
        }
};

class Heap {
    private:
        Vex *data;
        int size;

    public:
        Heap(Vex *data, int size) {
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
        
        Vex *getData() {
            return data;
        }
        
        void min_heapify(int i) {
            if(this->isEmpty())
                return;
            
            int l = this->getLeft(i),
                r = this->getRight(i),
                u;
            
            if(l <= this->getSize() && this->getData()[l-1].getW() < this->getData()[i-1].getW())
                u = l;
            else
                u = i;
            
            if(r <= this->getSize() && this->getData()[r-1].getW() < this->getData()[u-1].getW())
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
        
        Vex heap_minimum() {
            return data[0];
        }
        
        Vex extract_min() {
            Vex aux = data[0];
        
            data[0] = data[size-1];
            
            size--;
                
            min_heapify(1);
            
            return aux;
        }
        
        void decrease_key(int i, int key) {
            i--;
            
            if(data[i].getW() < key)
                return;
            
            data[i].setW(key);
            
            for(; i && (data[this->getParent(i)].getW() > data[i].getW()); i = this->getParent(i))
                std::swap(data[this->getParent(i)], data[i]);
        }
        
        std::string toString() {
            if(this->isEmpty())
                return "Heap is empty\n";
            
            std::stringstream u, w, s;
            std::string show = "Heap.: {";
            
            for(int i = 0; i < size; i++) {
                u << data[i].getU();
                w << data[i].getW();
                
                if((i+1) == size) {
                    show += "(" + u.str() + ", " + w.str() + ")" + "}";
                    break;
                }
                else
                    show += "(" + u.str() + ", " + w.str() + ")" + ", ";
                
                u.str("");
                w.str("");
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

//is min heap
bool isHeap(Vex arr[], int i, int size) {
    if(!i)
        i++;
    
    int left = 2*i;
    int right = 2*i + 1;
    
    if(left >= size || right >= size)
        return true;
    
    if(arr[i-1].getW() > arr[left-1].getW() || arr[i-1].getW() > arr[right-1].getW())
        return false;
    
    if(!isHeap(arr, left, size) || !isHeap(arr, right, size))
        return false;
    
    return true;
}

#endif //HEAP_H

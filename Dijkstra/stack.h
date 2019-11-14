#ifndef STACK_H
#define STACK_H

#include "heap.h"

class NodeS {
    public:
        vex_t data;
        NodeS *next;
        
        vex_t getData() {
            return data;
        }
        
        NodeS *getNext() {
            return next;
        }
};

class Stack {
    private:
        NodeS *head;
        int size;
        
    public:
        Stack() {
            this->head = NULL;
            this->size = 0;
        }

        int getSize() {
            return this->size;
        }

        bool empty() {
            return !this->head;
        }
        
        void push(vex_t data) {
            NodeS *node = new NodeS();
            
            node->data = data;
            node->next = this->head;
            this->head = node;
            
            this->size++;
            
            //std::cout << "Inserted: (" << data.v << ", " << data.w << ")" << std::endl;
            
            return;
        }
        
        vex_t pop() {
            NodeS *p = this->head;
            
            vex_t d = p->data;
            
            this->head = p->next;
            
            p->next = NULL;
            delete p;
            
            this->size--;
            
            return d;
        }
        
        std::string toString() {
            if(this->empty())
                return "Empty\n";
            
            std::stringstream v;
            std::stringstream w;
            std::string show = "Stack: {";
            
            NodeS *p = this->head;
            
            for(; p; p = p->next) {
                v << p->data.v;
                w << p->data.w;
                
                if(!p->next)
                    show += "(" + v.str() + ", " + w.str() + ")" + "}";
                else
                    show += "(" + v.str() + ", " + w.str() + ")" + ", ";
                
                v.str("");
                w.str("");
            }
                
            return show + "\n";    
        }
};

#endif //STACK_H

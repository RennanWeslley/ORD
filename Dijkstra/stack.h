#ifndef STACK_H
#define STACK_H

#include "heap.h"

class NodeS {
    public:
        Vex data;
        NodeS *next;
        
        Vex getData() {
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
        
        void push(Vex data) {
            NodeS *node = new NodeS();
            
            node->data = data;
            node->next = this->head;
            this->head = node;
            
            this->size++;
            
            //std::cout << "Inserted: (" << data.v << ", " << data.w << ")" << std::endl;
            
            return;
        }
        
        Vex pop() {
            NodeS *p = this->head;
            
            Vex d = p->data;
            
            this->head = p->next;
            
            p->next = NULL;
            delete p;
            
            this->size--;
            
            return d;
        }
        
        std::string toString() {
            if(this->empty())
                return "Empty\n";
            
            std::stringstream u;
            std::stringstream w;
            std::string show = "Stack: {";
            
            NodeS *p = this->head;
            
            for(; p; p = p->next) {
                u << p->data.getU();
                w << p->data.getW();
                
                if(!p->next)
                    show += "(" + u.str() + ", " + w.str() + ")" + "}";
                else
                    show += "(" + u.str() + ", " + w.str() + ")" + ", ";
                
                u.str("");
                w.str("");
            }
                
            return show + "\n";    
        }
};

#endif // STACK_H

#ifndef STACK_H
#define STACK_H

#include "list.h"

class Stack {
    private:
        node_t *top;
        int size;
        
    public:
        Stack() {
            top = NULL;
            size = 0;
        }

        int getSize() {
            return size;
        }

        bool empty() {
            return !top;
        }
        
        void push(vex_t data) {
            node_t *node = (node_t *) malloc(sizeof(node_t));
            
            node->data = data;
            node->next = top;
            top        = node;
            
            size++;
        }
        
        vex_t pop() {
            node_t *p = top;
            
            vex_t d = p->data;
            
            top = p->next;
            
            p->next = NULL;
            free(p);
            
            size--;
            
            return d;
        }
        
        std::string toString() {
            if(empty())
                return "Empty\n";
            
            std::stringstream v;
            std::stringstream w;
            std::string show = "Stack: {";
            
            node_t *p = top;
            
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

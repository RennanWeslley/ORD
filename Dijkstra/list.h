#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <sstream>

typedef struct {
    int v;
    int w;
} vex_t;

class Node {
    public:
        vex_t data;
        Node *next;
        
        vex_t getData() {
            return data;
        }
        
        int getV() {
            return data.v;
        }
        
        int getW() {
            return data.w;
        }
        
        Node *getNext() {
            return next;
        }
};

class List {
    private:
        Node *head;
        Node *back;
        int size;
        
    public:
        List() {
            this->head = NULL;
            this->size = 0;
        }
        
        Node *getHead() {
            return head;
        }

        int getSize() {
            return this->size;
        }

        bool empty() {
            return !this->head;
        }
        
        int insertHead(vex_t data) {
            Node *node = new Node();
            
            node->data = data;
            node->next = this->head;
            this->head = node;
            
            if(!size)
                this->back = node;
            
            this->size++;
            
            //std::cout << "Inserted: (" << data.v << ", " << data.w << ")" << std::endl;
            
            return 1;
        }
        
        /* Insert Back */
        int insert(vex_t data) {
            if(this->empty())
                return insertHead(data);
            
            Node *p = this->back;
            Node *node = new Node();
            
            node->data = data;
            node->next = NULL;
            p->next    = node;
            this->back = node;
            
            this->size++;
            
            //std::cout << "Inserted: (" << data.v << ", " << data.w << ")" << std::endl;
            
            return 1;
        }
        
        std::string toString() {
            if(this->empty())
                return "Empty\n";
            
            std::stringstream v;
            std::stringstream w;
            std::string show = "List: {";
            
            Node *p = this->head;
            
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

#endif //LIST_H

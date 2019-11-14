#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstdlib>
#include <sstream>

typedef struct {
    int v;
    int w;
} data_t;

class Node {
    public:
        data_t data;
        Node *next;
        
        data_t getData() {
            return data;
        }
        
        Node *getNext() {
            return next;
        }
};

class List {
    private:
        Node *head;
        int size;
        
    public:
        List() {
            this->head = NULL;
            this->size = 0;
        }

        int getSize() {
            return this->size;
        }

        bool empty() {
            return !this->head;
        }
        
        data_t visit(int pos) {
            Node *p = this->head;
            
            for(int i = 0; i < pos; p = p->next, i++);
                
            return p->data;
        }
        
        int insertHead(data_t data) {
            Node *node = new Node();
            
            node->data = data;
            node->next = this->head;
            this->head = node;
            
            this->size++;
            
            //std::cout << "Inserted: (" << data.v << ", " << data.w << ")" << std::endl;
            
            return 1;
        }
        
        int insert(data_t data) {
            if(this->empty())
                return insertHead(data);
            
            Node *p = this->head;
            Node *node = new Node();
            
            for(; p->next; p = p->next);
            
            node->data = data;
            node->next = NULL;
            p->next    = node;
            
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

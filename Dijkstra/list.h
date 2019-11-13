#ifndef LIST_H
#define LIST_H

#include<iostream>
#include<cstdlib>

using namespace std;

typedef struct {
    int pos;
    int value;
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
            if((pos-1) > this->size)
                pos = this->size;
            
            Node *p = this->head;
            
            for(int i = 1; i < pos; p = p->next, i++);
                
            return p->data;
        }
        
        int insertHead(data_t data) {
            Node *node = new Node();
            
            node->data = data;
            node->next = this->head;
            this->head = node;
            
            this->size++;
            
            //std::cout << "Inserted: (" << data.pos << ", " << data.value << ")" << std::endl;
            
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
            
            //std::cout << "Inserted: (" << data.pos << ", " << data.value << ")" << std::endl;
            
            return 1;
        }
        
        std::string toString() {
            if(this->empty())
                return "Empty\n";
            
            stringstream pos;
            stringstream value;
            string show = "List: {";
            
            Node *p = this->head;
            
            for(; p; p = p->next) {
                pos << p->data.pos;
                value << p->data.value;
                
                if(!p->next)
                    show += "(" + pos.str() + ", " + value.str() + ")" + "}";
                else
                    show += "(" + pos.str() + ", " + value.str() + ")" + ", ";
                
                pos.str("");
                value.str("");
            }
                
            return show + "\n";    
        }
};

#endif //LIST_H

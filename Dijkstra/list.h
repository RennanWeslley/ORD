#ifndef LIST_H
#define LIST_H

#include <sstream>

typedef struct {
    int v;
    int w;
} vex_t;

typedef struct node {
    vex_t data;
    struct node *next;
} node_t;

class List {
    private:
        node_t *head;
        node_t *back;
        int size;
        
    public:
        List() {
            head = NULL;
            back = NULL;
            size = 0;
        }
        
        node_t *getHead() {
            return head;
        }

        int getSize() {
            return size;
        }

        bool empty() {
            return !head;
        }
        
        void insertHead(vex_t data) {
            node_t *node = (node_t *) malloc(sizeof(node_t));
            
            node->data = data;
            node->next = head;
            head       = node;
            
            if(!size)
                back = node;
            
            size++;
        }
        
        /* Insert Back */
        void insert(vex_t data) {
            if(empty())
                return insertHead(data);
            
            node_t *p = back;
            node_t *node = (node_t *) malloc(sizeof(node_t));
            
            node->data = data;
            node->next = NULL;
            p->next    = node;
            back       = node;
            
            size++;
        }
        
        std::string toString() {
            if(empty())
                return "Empty\n";
            
            std::stringstream v;
            std::stringstream w;
            std::string show = "List: {";
            
            node_t *p = head;
            
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

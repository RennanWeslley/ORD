#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "heap.h"

#define INF 0x3f3f3f3f

void load_adjacency_list(List *, int, FILE *);
void init(int *, int *, int);
void relax(int, int, int, int *, int *);
void dijkstra(List *, int, int *, int *);
std::string path(int, int *, int *);

void load_adjacency_list(List *list, int size, FILE *f) {
    std::stringstream *d;
    char c[1024];
    vex_t data;

    for(int i = 0; i < size; i++){
        for(int j = 0, pos = i+1; pos < size; c[0] = '\0', pos++, j++) {
            for(int k = 0; ; k++) {
                c[k] = getc(f);
                
                if(c[k] == ' ' || c[k] == '\n') {
                    k--;
                    continue;
                }
                
                if(!isdigit(c[k])) {
                    c[k] = '\0';
                    break;
                }
                
                if(feof(f)) {
                    d = new std::stringstream(c);
                    *d >> data.w;
                    
                    data.v = pos;
                    list[i].insert(data);
                    
                    data.v = i;
                    list[pos].insert(data);
                    
                    return;
                }
            }
                
            d = new std::stringstream(c);
            *d >> data.w;

            data.v = pos;
            list[i].insert(data);

            data.v = i;
            list[pos].insert(data);
        }
    }
}

void init(int *d, int *p, int size) {
    for(int i = 0; i < size; i++) {
        d[i] = INF;
        p[i] = -1;
    }
    
    d[0] = 0;
}

void relax(int u, int v, int w, int *d, int *p) {
    w += d[u];
    
    if(d[v] > w) {
        d[v] = w;
        p[v] = u;
    }
}

void dijkstra(List *list, int size, int *d, int *p) {
    vex_t a;
    vex_t arr[size];
    
    /* Vertex array <- Pairs(u, weight)*/
    for(int i = 0; i < size; i++) {
        arr[i].v = i;
        arr[i].w = d[i];
    }
    
    Heap h(arr, size);
    vex_t node;
    
    h.build_min_heap();
    
    while(!(h.isEmpty())) {
        node = h.extract_min();
        
        for(int i = 0; i < size-1; i++) {
            for(Node *n = list[node.v].getHead(); n; n = n->next)
                relax(node.v, n->getV(), n->getW(), d, p);
        }
    }
}

std::string path(int u, int *d, int *p) {
    std::stringstream toInt;
    int w = d[u];
    std::string path = "Path..: ";
    
    toInt << u;
    path += toInt.str() + " <- ";
    
    toInt.str("");
    
    for(u = p[u]; u > -1; u = p[u]) {
        toInt << u;
        
        path += toInt.str() + " <- ";
        
        toInt.str("");
    }
    
    toInt.str("");
    toInt << w;
    
    return path + "\nWeight: " + toInt.str();
}

#endif //DIJKSTRA_H

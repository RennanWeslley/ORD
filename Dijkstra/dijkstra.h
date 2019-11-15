#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "heap.h"
#include <ctype.h>

#define INF 0x3f3f3f3f

int readInt(FILE *f);
void load_adjacency_list(List *, int, FILE *);
void init(int *, int *, int);
void relax(int, int, int, int *, int *);
void dijkstra(int *, int *, int, FILE *);
std::string path(int, int *, int *);

int readInt(FILE *f) {
    char c[1024];
    char aux;
    bool flag = false;
    int k = 0;
    
    while(1) {
        aux = getc(f);
        
        if(isdigit(aux)) {
            c[k++] = aux;
            flag = true;
        }
        else if(flag) {
            c[k] = '\0';
            break;
        }
    }
        
    std::stringstream d(c);
    d >> k;
    
    return k;
}

void load_adjacency_list(List *list, int size, FILE *f) {
    vex_t data;

    for(int i = 0; i < size; i++)
        for(int pos = i+1; pos < size; pos++) {
            data.w = readInt(f);

            data.v = pos;
            list[i].insert(data);

            data.v = i;
            list[pos].insert(data);
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

void dijkstra(int *d, int *p, int size, FILE *f) {
    /* Load the adjacency list */
    List list[size];
    load_adjacency_list(list, size, f);
    
    /* Vertex array <- Pairs(u, weight)*/
    vex_t arr[size];
    
    for(int i = 0; i < size; i++) {
        arr[i].v = i;
        arr[i].w = d[i];
    }
    
    Heap h(arr, size);
    int u;
    
    h.build_min_heap();
    
    while(!h.isEmpty()) {
        u = h.extract_min().v;
        
        for(node_t *n = list[u].getHead(); n; n = n->next)
            relax(u, n->data.v, n->data.w, d, p);
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

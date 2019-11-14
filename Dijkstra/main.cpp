#include "stack.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define INF 0x3f3f3f3f

void load_adjacency_list(List *, int, FILE *);
void init(int *, int *, int);
void relax(int, int, int, int *, int *);

int main(int argc, char *argv[]) {
    std::cout << std::endl;
    
    if(argc == 1) {
        std::cerr << "\nInvalid argument. Type: make file-number\n" << std::endl;
        return -1;
    }
    
    /* READING FILE */
    char arq[] = "files/dij";
    strcat(arq, argv[1]);
    strcat(arq, ".txt");

    FILE *f = fopen(arq, "r");
    
    if(!f) {
        std::cerr << "Open file error" << std::endl;
        return 0;
    }
    
    char s[1024];
    int size;
    
    /* READING SIZE */
    fgets(s, 1024, f);
    
    if(!s) {
        std::cerr << "Line cannot be read" << std::endl;
        return 0;
    }

    std::stringstream toInt(s);
    toInt >> size;
    /* END OF READING SIZE */
    
    List list[size];
    
    load_adjacency_list(list, size, f);
    
    fclose(f);
    /*END OF READING FILE */
    
    data_t a;
    Vex vex[size];
    
    int d[size];
    int p[size];
    
    init(d, p, size);
    
    for(int i = 0; i < size; i++)
        vex[i] = Vex(i, d[i]);
    
    Heap h(vex, size);
    Vex node;
    
    h.build_min_heap();
    
    while(!(h.isEmpty())) {
        node = h.extract_min();
        
        for(int i = 0; i < size-1; i++) {
            a = list[node.getU()].visit(i);
            relax(node.getU(), a.v, a.w, d, p);
        }
    }
    
    std::string path = "";
    toInt.str("");
    
    toInt << (size-1);
    path += toInt.str() + " <- ";
    
    toInt.str("");
    
    for(int u = p[size-1]; u > -1; u = p[u]) {
        toInt << u;
        
        path += toInt.str() + " <- ";
        
        toInt.str("");
    }
    
    std::cout << "Path..: " << path << std::endl << "Weight: " << d[size-1] << std::endl << std::endl;
    
    /*
    bool flag = false;
    
    for(int i = 0; i < size; i++) {
        std::cout << "[" << i << "] -> " << list[i].toString() << std::endl;
       
        if(list[i].getSize() != (size - 1)) {
            flag = true;
        }
    } 
    
    if(!flag)
        std::cout << "Tudo certo\n" << std::endl;
    else
        std::cout << "Algo errado\n" << std::endl;
    */
    
    return 0;
}

void load_adjacency_list(List *list, int size, FILE *f) {
    std::stringstream *d;
    char c[1024];
    data_t data;

    for(int i = 0; i < size; i++){
        for(int j = 0, pos = i+1; pos < size; pos++, j++) {
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

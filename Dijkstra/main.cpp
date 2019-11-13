#include "heap.h"
#include "list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define HEAPCOMP 256000

void load_adjacency_list(List *, int, FILE *);

int main(int argc, char *argv[]) {
    std::cout << std::endl;
    
    if(argc == 1) {
        std::cout << "\nInvalid argument. Type:\n\nmake file-number\n" << std::endl;
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

    std::stringstream d(s);
    d >> size;
    /* END OF READING SIZE */
    
    List list[size];
    
    load_adjacency_list(list, size, f);
    
    fclose(f);
    /*END OF READING FILE */
    
    for(int i = 0; i < size; i++)
        std::cout << "[" << i << "] -> " << list[i].toString() << std::endl;
    
    bool flag = false;
    
    for(int i = 0; i < size; i++)
        if(list[i].getSize() != (size - 1)) {
            flag = true;
            break;
        }
    
    if(!flag)
        std::cout << "Tudo certo\n" << std::endl;
    else
        std::cout << "Algo errado\n" << std::endl;
    
    return 0;
}

void load_adjacency_list(List *list, int size, FILE *f) {
    std::stringstream *d;
    char aux[1024];
    data_t data;

    for(int i = 0; i < size; i++){
        for(int j = 0, pos = i+1; pos < size; pos++, j++) {
            for(int k = 0; ; k++) {
                aux[k] = getc(f);
                
                if(aux[k] == ' ' || aux[k] == '\n') {
                    k--;
                    continue;
                }
                
                if(!isdigit(aux[k])) {
                    aux[k] = '\0';
                    break;
                }
                
                if(feof(f)) {
                    d = new std::stringstream(aux);
                    *d >> data.value;
                    
                    data.pos = pos;
                    list[i].insert(data);
                    
                    data.pos = i;
                    list[pos].insert(data);
                    
                    return;
                }
            }
                
            d = new std::stringstream(aux);
            *d >> data.value;

            data.pos = pos;
            list[i].insert(data);

            data.pos = i;
            list[pos].insert(data);
        }
    }
}

#include "dijkstra.h"
#include <string.h>
#include <ctype.h>

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

    fgets(s, 1024, f);

    std::stringstream toInt(s);
    toInt >> size;
    
    int d[size];
    int p[size];
    
    /* Init of d and p array */
    init(d, p, size);
    
    /* Do Dijkstra */
    dijkstra(d, p, size, f);
    
    fclose(f);
    /*END OF READING FILE */
    
    std::cout << path((size-1), d, p) << std::endl << std::endl;
    
    return 0;
}

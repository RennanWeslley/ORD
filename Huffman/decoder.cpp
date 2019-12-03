#include "decoder.h"

void Decoder::frequency(FILE *f) {
    fread(arr, sizeof(freq_t), 256, f);
}

void Decoder::makeHeap(FILE *f) {
    std::vector<Node> data;
    
    frequency(f);
    
    for(int i = 0; i < 256; i++)
        if(arr[i]) {
            data.push_back(Node({(unsigned char) i, arr[i]}));
            total += arr[i];
        }
        
    h.setData(data);
    h.build_min_heap();
}

void Decoder::doCode(FILE *f, FILE *newF) {
    makeHeap(f);
    huffmanTree();
    
    unsigned char c;
    std::bitset<8> byte;
    
    Node *auxT = r;
    
    std::cout << std::endl << "Decompressing..." << std::endl;
    
    while(total > 0) {
        fread(&byte, sizeof(char), 1, f);
        
        for(int j = 7; j >= 0; j--) {
            if((auxT->data.c) != '\0') {
                c = auxT->data.c;
                fwrite(&c, sizeof(char), 1, newF);
                
                auxT = r;
                total--;
                
                if(!total)
                    break;
            }
            
            if(bitCompare((std::bitset<1>) byte[j], 0b0))
                auxT = auxT->left;
            else
                auxT = auxT->right;
        }
    }
    
    std::cout << std::endl << "Done." << std::endl << std::endl;
}

void Decoder::code(std::string name) {
    size_t dot = name.find('.');
    
    std::string fn    = name.substr(0, dot) + "(Compressed)" + name.substr(dot);
    std::string newFn = name.substr(0, dot) + "(Decompressed)" + name.substr(dot);
    
    FILE *f    = fopen(("files/" + fn).c_str(), "rb");
    
    if(!f) {
        std::cerr << fn << " -> Open file error" << std::endl;
        return;
    }
    
    FILE *newF = fopen(("files/" + newFn).c_str(), "wb");
    
    if(!newF) {
        std::cerr << newFn << " -> Open file error" << std::endl;
        return;
    }
    
    doCode(f, newF);
    
    fclose(newF);
    fclose(f);
}

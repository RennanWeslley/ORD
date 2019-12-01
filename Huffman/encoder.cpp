#include "encoder.h"

void Encoder::frequency(FILE *f) {
    unsigned char c;
    
    while(!feof(f)) {
        c = fgetc(f);

        if(c != 255)
            arr[c]++;
    }
    
    rewind(f);
}

void Encoder::makeHeap(FILE *f) {
    std::vector<Node> data;
    
    frequency(f);
    
    for(int i = 0; i < 256; i++)
        if(arr[i])
            data.push_back(Node({(unsigned char) i, arr[i]}));
    
    h.setData(data);
    h.build_min_heap();
}

void Encoder::huffmanTraversal() {
    huffmanCoding(r, "", codeArr);
}

void Encoder::doCode(FILE *f, FILE *newF) {
    makeHeap(f);
    huffmanTree();
    huffmanTraversal();
    
    fwrite(arr, sizeof(byte_t), 256, newF);
    
    unsigned char c;
    int j;
    std::bitset<8> byte;
    
    for(j = 0; j < 8; byte[j++] = 0b0);
    j = 7;
    
    std::cout << std::endl << "Compressing..." << std::endl;
    
    while(!feof(f)) {
        c = fgetc(f);
        
        if(c != 255) {
            //std::cout << c << " -> " << codeArr[c] << std::endl;
            for(int i = 0; i < codeArr[c].length(); j--, i++) {
                /* BYTE COMPLETE */
                if(j < 0) {
                    fwrite(&byte, sizeof(char), 1, newF);
                    for(j = 0; j < 8; byte[j++] = 0b0);
                    j = 7;
                }
                
                if(codeArr[c][i] == '1')
                    byte[j] = 0b1;
            }
        }
    }
    
    if(j < 7) 
        fwrite(&byte, sizeof(char), 1, newF);
    
    std::cout << std::endl << "Done." << std::endl << std::endl;
}

void Encoder::code(std::string name) {
    size_t dot = name.find('.');
    
    std::string newFn = name.substr(0, dot) + "(Compressed)" + name.substr(dot);
    
    FILE *f    = fopen(("files/" + name).c_str(), "rb"); /* ORIGINAL FILE */
    
    if(!f) {
        std::cerr << name << " -> Open file error" << std::endl;
        return;
    }
    
    FILE *newF = fopen(("files/" + newFn).c_str(), "wb"); /* COMPRESSED FILE */
    
    if(!newF) {
        std::cerr << newFn << " -> Open file error" << std::endl;
        return;
    }
    
    doCode(f, newF);
    
    fclose(f);
    fclose(newF);
}

std::string Encoder::codeString() {
    std::string s = "";
    
    for(int i = 0; i < 256; i++)
        if(!codeArr[i].empty()) {
            s += (char) i;
            s += " -> " + codeArr[i] + "\n";
        }
        
    return s;        
}

void Encoder::huffmanCoding(Tree root, std::string s, std::string *arr) {    
    if(empty(root))
        return;
    
    if(root->data.c != '\0')
        arr[root->data.c] += s;
    
    huffmanCoding(root->left, (s + '0'), arr);
    
    huffmanCoding(root->right, (s + '1'), arr);
}

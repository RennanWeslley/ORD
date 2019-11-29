#include "huffman.h"

void Huffman::huffmanTree() {
    int size = h.getSize();
    Node *t = new Node();
    Node *l, *r;
    
    for(int i = 0; i < (size-1); i++) {
        l = (Node *) malloc(sizeof(Node));
        r = (Node *) malloc(sizeof(Node));
        
        *l = h.extract_min();
        *r = h.extract_min();
        
        t->setL(l);
        t->setR(r);
        t->setC('\0');
        t->setSumF();
        
        h.insert_key(*t);
    }
    
    t = (Node *) malloc(sizeof(Node));
    *t = h.extract_min();
    
    this->r = t;
}

void Encoder::frequencyHeap(FILE *f) {
    char c;
    
    while(!feof(f)) {
        fread(&c, sizeof(char), 1, f);
        
        if((int) c > 0 && (int) c != 10)
            arr[c]++;
    }
    
    for(int i = 0; i < 256; i++)
        if(arr[i] > 0)
            h.insert_key(Node({(char) i, arr[i]}));
    
    rewind(f);
}

void Encoder::encode(std::string name) {
    size_t dot = name.find('.');
    
    std::string newFname = name.substr(0, dot) + "(Compressed)" + name.substr(dot);
    
    FILE *f    = fopen(("files/" + name).c_str(), "rb");       /* ORIGINAL FILE */
    FILE *newF = fopen(("files/" + newFname).c_str(), "wb"); /* COMPRESSED FILE */
    
    code(f, newF);
    
    fclose(f);
    fclose(newF);
    
    freeHuffmanTree(r);
}

void Encoder::code(FILE *f, FILE *newF) {
    frequencyHeap(f);
    huffmanTree();
    huffmanCoding(r, "", codeArr);
    
    fwrite(arr, sizeof(byte_t), 256, newF);
    
    char c;
    int j;
    std::bitset<8> byte;
    
    for(j = 0; j < 8; byte[j++] = 0b0);
    j = 7;
    
    std::cout << std::endl << "Compressing..." << std::endl;
    
    while(!feof(f)) {
        fread(&c, sizeof(char), 1, f);
        
        if((int) c > 0 && (int) c != 10) {
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

int Decoder::makeHeap() {
    int sum = 0;
    
    for(int i = 0; i < 256; i++)
        if(arr[i]) {
            h.insert_key(Node({(char) i, arr[i]}));
            sum += arr[i];
        }
    
    return sum;
}

void Decoder::decode(std::string name) {
    size_t dot = name.find('.');
    
    std::string fn    = name.substr(0, dot) + "(Compressed)" + name.substr(dot);
    std::string newFn = name.substr(0, dot) + "(Decompressed)" + name.substr(dot);
    
    FILE *f    = fopen(("files/" + fn).c_str(), "rb");
    FILE *newF = fopen(("files/" + newFn).c_str(), "wb");
    
    dcode(f, newF);
    
    fclose(newF);
    fclose(f);
    
    freeHuffmanTree(r);
    
    std::cout << std::endl << "Done." << std::endl << std::endl;
}

void Decoder::dcode(FILE *f, FILE *newF) {
    fread(arr, sizeof(byte_t), 256, f);
    
    int totalF = makeHeap();
    huffmanTree();
    
    char c;
    std::bitset<8> byte;
    
    Node *auxT = r;
    
    std::cout << std::endl << "Decompressing..." << std::endl;
    
    while(totalF > 0) {
        fread(&byte, sizeof(char), 1, f);
        char c;
        
        for(int j = 7; j >= 0; j--) {
            if((auxT->data.c) != '\0') {
                char c = auxT->data.c;
                fwrite(&c, sizeof(char), 1, newF);
                auxT = r;
                totalF--;
            }
            
            if(!totalF)
                break;
            
            if(bitCompare((std::bitset<1>) byte[j], 0b0))
                auxT = auxT->left;
            else
                auxT = auxT->right;
        }
    }
}

void huffmanCoding(Tree root, std::string s, std::string *arr) {    
    if(empty(root))
        return;
    
    if(root->data.c != '\0')
        arr[root->data.c] += s;
    
    huffmanCoding(root->left, (s + '0'), arr);
    
    huffmanCoding(root->right, (s + '1'), arr);
}

void freeHuffmanTree(Tree root) {
    if(empty(root))
        return;
    
    freeHuffmanTree(root->left);
    
    freeHuffmanTree(root->right);
    
    free(root);
}

bool bitCompare(std::bitset<1> bit1, std::bitset<1> bit2) {
    return (~(bit1 ^ bit2) == 0b1);
}


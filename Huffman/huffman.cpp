#include "huffman.h"

void Huffman::huffmanTree() {
    int size = h.getSize();
    Node *t = new Node();
    Node *l, *r;
    
    for(int i = 0; i < (size-1); i++) {
        l = (Node *) malloc(sizeof(Node));
        r = (Node *) malloc(sizeof(Node));
        
        if(!h.empty()) {
            *l = h.extract_min();
            t->setL(l);
        }
        if(!h.empty()) {
            *r = h.extract_min();
            t->setR(r);
        }
        
        t->setC('\0');
        t->setSumF();
        
        h.insert_key(*t);
    }
    
    t = (Node *) malloc(sizeof(Node));
    *t = h.extract_min();
    
    this->r = t;
}

std::string Huffman::codeString() {
    std::string s = "";
    
    for(int i = 0; i < 256; i++)
        if(!codeArr[i].empty()) {
            s += (char) i;
            s += " -> " + codeArr[i] + "\n";
        }
        
    return s;        
}

void Huffman::freeHuffmanTree(Tree root) {
    if(empty(root))
        return;
    
    freeHuffmanTree(root->left);
    
    freeHuffmanTree(root->right);
    
    free(root);
}

void Huffman::freeTree() {
    freeHuffmanTree(r);
}

Heap Huffman::getHeap() {
    return hCopy;
}

Tree Huffman::getTree() {
    return r;
}

void Encoder::makeHeap(FILE *f) {
    std::vector<Node> data;
    unsigned char c;
    
    while(!feof(f)) {
        c = fgetc(f);

        if(c != 255) {
            if(!(arr[c]))
                data.push_back(Node({c, 0}));
            
            arr[c]++;
        }
    }
    
    h.setData(data);
    hCopy.setData(data);
    
    for(int i = 0; i < h.getSize(); i++) {
        h.setF(i, arr[h.getC(i)]);
        hCopy.setF(i, arr[h.getC(i)]);
    }
    
    h.build_min_heap();
    hCopy.build_min_heap();
    
    //std::cout << h.toString() << std::endl;
        
    rewind(f);
}

void Encoder::encode(std::string name) {
    size_t dot = name.find('.');
    
    std::string newFname = name.substr(0, dot) + "(Compressed)" + name.substr(dot);
    
    FILE *f    = fopen(("files/" + name).c_str(), "rb");     /* ORIGINAL FILE */
    FILE *newF = fopen(("files/" + newFname).c_str(), "wb"); /* COMPRESSED FILE */
    
    code(f, newF);
    
    fclose(f);
    fclose(newF);
}

void Encoder::code(FILE *f, FILE *newF) {
    makeHeap(f);
    huffmanTree();
    //preOrder(r);
    huffmanCoding(r, "", codeArr);
    
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

int Decoder::makeHeap() {
    std::vector<Node> data;
    int sum = 0;
    
    for(int i = 0; i < 256; i++)
        if(arr[i]) {
            data.push_back(Node({(unsigned char) i, arr[i]}));
            sum += arr[i];
        }
        
    h.setData(data);
    hCopy.setData(data);
    
    h.build_min_heap();
    hCopy.build_min_heap();
    
    //std::cout << h.toString() << std::endl;
    
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
}

void Decoder::dcode(FILE *f, FILE *newF) {
    fread(arr, sizeof(byte_t), 256, f);
    
    int totalF = makeHeap();
    huffmanTree();
    //preOrder(r);
    unsigned char c;
    std::bitset<8> byte;
    
    Node *auxT = r;
    
    std::cout << std::endl << "Decompressing..." << std::endl;
    
    while(totalF > 0) {
        fread(&byte, sizeof(char), 1, f);
        
        for(int j = 7; j >= 0; j--) {
            if((auxT->data.c) != '\0') {
                c = auxT->data.c;
                fwrite(&c, sizeof(char), 1, newF);
                
                auxT = r;
                totalF--;
                
                if(!totalF)
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

void huffmanCoding(Tree root, std::string s, std::string *arr) {    
    if(empty(root))
        return;
    
    if(root->data.c != '\0')
        arr[root->data.c] += s;
    
    huffmanCoding(root->left, (s + '0'), arr);
    
    huffmanCoding(root->right, (s + '1'), arr);
}

bool bitCompare(std::bitset<1> bit1, std::bitset<1> bit2) {
    return (~(bit1 ^ bit2) == 0b1);
}


#include "huffman.h"

void frequencyHeap(FILE *f, Heap *h, byte_t *arr) {
    char c;
    
    while(!feof(f)) {
        c = getc(f);
        
        if((int) c > 0 && (int) c != 10) {
            if(!(arr[c]))
                h->insert_key(Node({c, 0}));

            arr[c]++;
        }
    }
    
    for(int i = 0; i < h->getSize(); i++)
        h->setF(i, arr[h->getC(i)]);
    
    h->build_min_heap();
    
    rewind(f);
}

Node *huffmanTree(Heap *h, int size) {
    Node *t = new Node();
    Node *l, *r;
    
    for(int i = 0; i < (size-1); i++) {
        l = (Node *) malloc(sizeof(Node));
        r = (Node *) malloc(sizeof(Node));
        
        *l = h->extract_min();
        *r = h->extract_min();
        
        t->setL(l);
        t->setR(r);
        t->setC('\0');
        t->setSumF();
        
        h->insert_key(*t);
    }
    
    t = (Node *) malloc(sizeof(Node));
    *t = h->extract_min();
    
    return t;
}

void huffmanCoding(Tree root, std::string s, std::string *arr) {    
    if(empty(root))
        return;
    
    if(root->data.c != '\0')
        arr[root->data.c] += s;
    
    huffmanCoding(root->left, (s + '0'), arr);
    
    huffmanCoding(root->right, (s + '1'), arr);
}


Tree code(Heap *h, std::string *codeArr, byte_t *arr, FILE *f, FILE *newF, FILE *test) {
    Tree root = huffmanTree(h, h->getSize());
    huffmanCoding(root, "", codeArr);
    
    fwrite(arr, sizeof(byte_t), 256, newF);
    
    char c, aux, space = ' ';
    int j;
    std::bitset<8> byte;
    
    for(j = 0; j < 8; byte[j++] = 0b0);
    j--;
    
    std::cout << std::endl;
    
    while(!feof(f)) {
        c = getc(f);
        
        if((int) c > 0 && (int) c != 10) {
            std::cout << c << " -> " << codeArr[c] << std::endl;
            for(int i = 0; i < codeArr[c].length(); j--, i++) {
                /* BYTE COMPLETE */
                if(j < 0) {
                    fwrite(&space, sizeof(char), 1, test);
                    fwrite(&byte, sizeof(char), 1, newF);
                    
                    for(j = 0; j < 8; byte[j++] = 0b0);
                    j--;
                }
                
                if(codeArr[c][i] == '1') {
                    byte[j] = 0b1;
                    aux = '1';
                }
                else
                    aux = '0';
                
                fwrite(&aux, sizeof(char), 1, test);
            }
        }   
    }
    
    if(j < 7) 
        fwrite(&byte, sizeof(char), 1, newF);
    
    return root;
}

bool bitCompare(std::bitset<1> bit1, std::bitset<1> bit2) {
    return (~(bit1 ^ bit2) == 0b1);
}

void testing(FILE *f, FILE *newF) {
    byte_t arr[256];
    char c;
    
    fread(arr, sizeof(byte_t), 256, newF);
    
    std::cout << std::endl;
    
    while(!feof(f)) {
        c = getc(f);
        
        if((int) c > 0 && (int) c != 10)
            std::cout << c << " - " << (int) arr[c] <<  std::endl;
    }
}

void huffman(FILE *f, FILE *newF, FILE *test) {
    Heap h;
    byte_t arr[256] = {0};
    std::string codeArr[256] = {""};
    
    frequencyHeap(f, &h, arr);
    
    Tree root = code(&h, codeArr, arr, f, newF, test);
    
    rewind(f);
    rewind(newF);
    rewind(test);
    
    testing(f, newF);
    
    freeHuffmanTree(root);
}

void freeHuffmanTree(Tree root) {
    if(empty(root))
        return;
    
    freeHuffmanTree(root->left);
    
    freeHuffmanTree(root->right);
    
    free(root);
}

#include "heap.h"
#include <stdlib.h>
#include <stdio.h>
#include <bitset>

Node *huffmanTree(Heap *, int);
void huffmanCoding(Tree, std::string, std::string *);
bool bitCompare(std::bitset<1>, std::bitset<1>);
void freeHuffmanTree(Tree);
void test(Heap *);

int main(int argc, char *argv[]) {
    int arr[256] = {0};
    char c;
    Heap h;
    
    FILE *f = fopen("files/laptop.txt", "r");
    
    while(!feof(f)) {
        c = getc(f);
        
        if((int) c > 0 && (int) c != 10) {
            if(!(arr[c]))
                h.insert_key(Node({c, 0}));

            arr[c]++;
        }
    }
    
    rewind(f);
    
    for(int i = 0; i < h.getSize(); i++)
        h.setF(i, arr[h.getC(i)]);
    
    h.build_min_heap();
    
    /* HUFFMAN */
    Tree root = huffmanTree(&h, h.getSize());
    
    std::string codeArr[256] = {""};
    huffmanCoding(root, "", codeArr);
    
    std::bitset<1> altByte1;
    std::bitset<2> altByte2;
    std::bitset<3> altByte3;
    std::bitset<4> altByte4;
    std::bitset<5> altByte5;
    std::bitset<6> altByte6;
    std::bitset<7> altByte7;
    
    std::bitset<8> byte;
    std::bitset<1> bit;
    int j = 7;
    char aux;
    char space = ' ';
    
    FILE *newF = fopen("files/laptopCoded.txt", "wb");
    FILE *test = fopen("files/laptopCodedTest.txt", "wb");
    
    while(!feof(f)) {
        c = getc(f);
        
        if((int) c > 0 && (int) c != 10) {
            std::cout << c << " -> " << codeArr[c] << std::endl;
            for(int i = 0; i < codeArr[c].length(); i++) {
                switch(codeArr[c][i]) {
                    case '0':
                        bit = 0b0;
                        aux = '0';
                        break;
                    case '1':
                        bit = 0b1;
                        aux = '1';
                        break;
                }
                
                byte[j--] = bit[0];
                fwrite(&aux, sizeof(char), 1, test);
                
                if(!j) {
                    fwrite(&space, sizeof(char), 1, newF);
                    fwrite(&byte, sizeof(char), 1, newF);
                    j = 7;
                }
            }
            
            if(j < 7) {
                switch((j+1)) {
                    case 7:
                        altByte1[0] = byte[7];
                        fwrite(&altByte1, sizeof(char)/8, 1, newF);
                        break;
                    case 6:
                        for(int i = 1, k = 7; i >= 0; altByte2[i--] = byte[7]);
                        fwrite(&altByte2, sizeof(char)/7, 1, newF);
                        break;
                    case 5:
                        for(int i = 2, k = 7; i >= 0; altByte2[i--] = byte[7]);
                        fwrite(&altByte3, sizeof(char)/6, 1, newF);
                        break;
                    case 4:
                        for(int i = 3, k = 7; i >= 0; altByte2[i--] = byte[7]);
                        fwrite(&altByte4, sizeof(char)/5, 1, newF);
                        break;
                    case 3:
                        for(int i = 4, k = 7; i >= 0; altByte2[i--] = byte[7]);
                        fwrite(&altByte5, sizeof(char)/4, 1, newF);
                        break;
                    case 2:
                        for(int i = 5, k = 7; i >= 0; altByte2[i--] = byte[7]);
                        fwrite(&altByte6, sizeof(char)/3, 1, newF);
                        break;
                    case 1:
                        for(int i = 6, k = 7; i >= 0; altByte2[i--] = byte[7]);
                        fwrite(&altByte7, sizeof(char)/2, 1, newF);
                        break;
                }

            }
        }   
    }
    
    fclose(test);
    fclose(newF);
    fclose(f);
    
    freeHuffmanTree(root);
    
    return 0;
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

/*
void code(std::string *codeArr, FILE *old, FILE *newF) {

    
}
*/
bool bitCompare(std::bitset<1> bit1, std::bitset<1> bit2) {
    return (~(bit1 ^ bit2) == 0b1);
}

void freeHuffmanTree(Tree root) {
    if(empty(root))
        return;
    
    freeHuffmanTree(root->left);
    
    freeHuffmanTree(root->right);
    
    free(root);
}

void test(Heap *h) {
    std::cout << h->toString() << std::endl;
    isHeap(h->getData(), 0, h->getSize())? std::cout << "True" : std::cout << "False";
    std::cout << std::endl << std::endl;
    
    h->build_min_heap();
    std::cout << h->toString() << std::endl;
    isHeap(h->getData(), 0, h->getSize())? std::cout << "True" : std::cout << "False";
    std::cout << std::endl << std::endl;
}

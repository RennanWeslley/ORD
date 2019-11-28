#include "heap.h"
#include <stdlib.h>
#include <stdio.h>

Node *huffmanTree(Heap *, int);
void huffmanCoding(Tree, std::string, std::string *);
void freeHuffmanTree(Tree);
//void test(Heap *);

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
    
    char aux;
    
    FILE *test = fopen("files/laptopCodedTest.txt", "wb");
    
    while(!feof(f)) {
        c = getc(f);
        
        if((int) c > 0 && (int) c != 10) {
            std::cout << c << " -> " << codeArr[c] << std::endl;
            for(int i = 0; i < codeArr[c].length(); i++) {
                switch(codeArr[c][i]) {
                    case '0':
                        aux = '0';
                        break;
                    case '1':
                        aux = '1';
                        break;
                }
                
                fwrite(&aux, sizeof(char), 1, test);  
            }
            
        }
    }
    
    fclose(test);
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

void freeHuffmanTree(Tree root) {
    if(empty(root))
        return;
    
    freeHuffmanTree(root->left);
    
    freeHuffmanTree(root->right);
    
    free(root);
}

/*
void test(Heap *h) {
    std::cout << h->toString() << std::endl;
    isHeap(h->getData(), 0, h->getSize())? std::cout << "True" : std::cout << "False";
    std::cout << std::endl << std::endl;
    
    h->build_min_heap();
    std::cout << h->toString() << std::endl;
    isHeap(h->getData(), 0, h->getSize())? std::cout << "True" : std::cout << "False";
    std::cout << std::endl << std::endl;
}
*/

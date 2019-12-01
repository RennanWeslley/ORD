#ifndef ENCODER_H
#define ENCODER_H

#include "coder.h"

class Encoder : public Coder {
    private:
        std::string codeArr[256] = {""};
        void huffmanCoding(Tree, std::string, std::string *);
        
    public:
        void frequency(FILE *);
        void makeHeap(FILE *);
        void huffmanTraversal();
        void code(std::string);
        void doCode(FILE *, FILE *);
        std::string codeString();
};

#endif //DECODER_H

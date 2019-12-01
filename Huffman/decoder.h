#ifndef DECODER_H
#define DECODER_H

#include "coder.h"

class Decoder : public Coder {
    private:
        int total = 0;
        
    public:
        void frequency(FILE *);
        void makeHeap(FILE *);
        void code(std::string);
        void doCode(FILE *, FILE *);
};

#endif //DECODER_H

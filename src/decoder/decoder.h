//
// Created by WolfPlay on 01/12/2023.
//

#ifndef KASJER_DECODER_H
#define KASJER_DECODER_H

#include "bin_generator.h"

class decoder {
public:
    static bin_generator::header headerFromBytes(char* headerByteData);
    static bin_generator::customer customerFromBytes(char* customerByteData);
    static bool verifyByteData(char* headerByteData, char* customerByteData);
    static bool verifyRawData(bin_generator::header headerRawData, bin_generator::customer* customersRawData);
    static unsigned int calculateBreaks(bin_generator::header headerRawData, bin_generator::customer* customersRawData);
};


#endif //KASJER_DECODER_H

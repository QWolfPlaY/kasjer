//
// Created by WolfPlay on 01/12/2023.
//

#ifndef KASJER_DECODER_H
#define KASJER_DECODER_H

#include "bin_generator.h"
#include "cpp-core/core.h"

class decoder
{
public:
    static bin_generator::header headerFromBytes(char *headerByteData);
    static bin_generator::customer customerFromBytes(char* customersByteData, size_t offset, const bool BYTE_OFFSET);
    static bool verifyByteFile(char *headerByteData, size_t fileSize);
    static bool verifyRawData(bin_generator::header headerRawData, std::vector<bin_generator::customer> customers);
    static unsigned int calculateBreaks(bin_generator::header headerRawData, bin_generator::customer *customersRawData);
};


#endif //KASJER_DECODER_H

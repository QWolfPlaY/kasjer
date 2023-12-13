//
// Created by WolfPlay on 01/12/2023.
//

#include "decoder.h"
#include "bin_generator.h"
#include "cpp-core/core.h"

bin_generator::header decoder::headerFromBytes(char *headerByteData)
{
    bin_generator::header header;

    header.workTime =

    return bin_generator::header();
}

bin_generator::customer decoder::customerFromBytes(char *customerByteData)
{
    return bin_generator::customer();
}

bool decoder::verifyByteData(char *headerByteData, char *customerByteData, size_t fileSize)
{
    bin_generator::header header =
    return false;
}

bool decoder::verifyRawData(bin_generator::header headerRawData, bin_generator::customer *customersRawData)
{
    return false;
}

unsigned int decoder::calculateBreaks(bin_generator::header headerRawData, bin_generator::customer *customersRawData)
{
    return 0;
}

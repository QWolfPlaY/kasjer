#include <random>
#include <vector>

#include "bin_generator.h"
#include "cpp-core/core.h"

bin_generator::header bin_generator::generateHeader() {
    std::random_device rd;
    std::mt19937 gen(rd());

    bin_generator::header headerRawData = {};

    headerRawData.customerCount = std::uniform_int_distribution<unsigned int>(1, 100000)(gen);
    headerRawData.workTime = std::uniform_int_distribution<unsigned int>(1, 1000000000)(gen);
    headerRawData.cigaretteBreakLen = std::uniform_int_distribution<unsigned int>(1, headerRawData.workTime)(gen);

    return headerRawData;
}

bin_generator::customer bin_generator::generateCustomer(bin_generator::header headerRawData) {
    std::random_device rd;
    std::mt19937 gen(rd());

    unsigned int workTime = headerRawData.workTime;

    bin_generator::customer customerRawData = {};

    customerRawData.entryTime = std::uniform_int_distribution<unsigned int>(1, --workTime)(rd);
    customerRawData.timeUsage = std::uniform_int_distribution<unsigned int>(1, workTime)(rd);


    return customerRawData;
}

char *bin_generator::generateByteData(bin_generator::header headerRawData) {
    char *headerBytes = core::toBytes(&headerRawData, sizeof(bin_generator::header));
    size_t headerSize = sizeof(bin_generator::header);

    size_t dataSize = headerSize + (headerRawData.customerCount * sizeof(bin_generator::customer));
    char *byteData = new char[dataSize]; // ! DON'T FORGET TO FREE THE MEMORY

    memcpy(byteData, headerBytes, headerSize);

    delete[] headerBytes;

    size_t index = headerSize;

    for (int i = 0; i < headerRawData.customerCount; i++) {
        bin_generator::customer customerData = generateCustomer(headerRawData);
        char* customerBytes = core::toBytes(&customerData, sizeof(bin_generator::customer));
        size_t customerSize = sizeof(bin_generator::customer);

        memcpy(byteData + index, customerBytes, customerSize);

        delete[] customerBytes;
        index += customerSize;
    }

    return byteData;
}

size_t bin_generator::calculateSize(bin_generator::header headerRawData) {
    size_t size = sizeof(bin_generator::header) + (headerRawData.customerCount * sizeof(bin_generator::customer));
    return size;
}
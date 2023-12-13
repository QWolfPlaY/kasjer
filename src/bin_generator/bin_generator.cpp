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
    char *headerBytes = core::toBytes(&headerRawData, bin_generator::HEADER_SIZE);

    size_t dataSize = bin_generator::HEADER_SIZE + (headerRawData.customerCount * bin_generator::CUSTOMER_SIZE);
    char *byteData = new char[dataSize]; // ! DON'T FORGET TO FREE THE MEMORY

    memcpy(byteData, headerBytes, bin_generator::HEADER_SIZE);

    delete[] headerBytes;

    size_t index = bin_generator::HEADER_SIZE;

    for (int i = 0; i < headerRawData.customerCount; i++) {
        bin_generator::customer customerData = generateCustomer(headerRawData);
        char* customerBytes = core::toBytes(&customerData, bin_generator::CUSTOMER_SIZE);

        memcpy(byteData + index, customerBytes, bin_generator::CUSTOMER_SIZE);

        delete[] customerBytes;
        index += bin_generator::CUSTOMER_SIZE;
    }

    return byteData;
}

size_t bin_generator::calculateSize(bin_generator::header headerRawData) {
    size_t size = bin_generator::HEADER_SIZE + (headerRawData.customerCount * bin_generator::CUSTOMER_SIZE);
    return size;
}
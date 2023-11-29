#include <random>
#include <vector>

#include "bin_generator.h"
#include "cpp-core/core.h"

bin_generator::header bin_generator::generateHeader() {
    std::random_device rd;
    std::mt19937 gen(rd());

    bin_generator::header headerRawData = {};

    headerRawData.customerCount = std::uniform_int_distribution<unsigned int>(1, 100000)(rd);
    headerRawData.workTime = std::uniform_int_distribution<unsigned int>(1, 1000000000)(rd);
    headerRawData.cigaretteBreakLen = std::uniform_int_distribution<unsigned int>(1, headerRawData.workTime)(rd);

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
    char *headerBytes = core::toBytes(headerRawData);

    size_t dataSize = sizeof(headerBytes) + (headerRawData.customerCount * sizeof(bin_generator::customer));
    char *byteData = new char[dataSize]; // ! DON'T FORGET TO FREE THE MEMORY

    std::vector<bin_generator::customer> customers;

    size_t index;

    for (index = 0; index < sizeof(headerBytes); index++) {
        byteData[index] = headerBytes[index];
    }

    customers.reserve(headerRawData.customerCount * sizeof(bin_generator::customer));
    for (int i = 0; i < headerRawData.customerCount; i++) {
        customers.push_back(generateCustomer(headerRawData));
    }

    std::vector<char> customersBytesVec;
    customersBytesVec.reserve(customers.size() * sizeof(customer));
    for (const auto &element: customers) {
        char *customerBytes = core::toBytes(element);
        for (size_t i = 0; i < sizeof(*customerBytes); i++) {
            customersBytesVec.push_back(customerBytes[i]);
        }
        delete[] customerBytes;
    }

    for (char byte: customersBytesVec) {
        byteData[index] = byte;
        index++;
    }

    delete[] headerBytes;

    return byteData;
}

size_t bin_generator::calculateSize(bin_generator::header headerRawData) {
    size_t size = sizeof(bin_generator::header) + (headerRawData.customerCount * sizeof(bin_generator::customer));
    return size;
}
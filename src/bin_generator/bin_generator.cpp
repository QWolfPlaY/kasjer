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
    std::vector<bin_generator::customer> customers;
    std::vector<char> byteData;

    char *headerBytes = core::toBytes(headerRawData);
    byteData.reserve(sizeof(&headerBytes));
    
    for (int i = 0; i < sizeof(&headerBytes); i++) {
        byteData.push_back(headerBytes[i]);
    }

    for (int i = 0; i < headerRawData.customerCount; i++) {
        customers.push_back(generateCustomer(headerRawData));
    }


    return 0;
}


int main(int argc, char *argv[]) {


    return 0;
}
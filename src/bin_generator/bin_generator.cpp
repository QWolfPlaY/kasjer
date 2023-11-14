#include <random>

#include "bin_generator.h"
#include "cpp-core/core.h"

bin_generator::header bin_generator::generateHeader() {
    std::random_device rd;
    std::mt19937 gen(rd());

    bin_generator::header headerRawData = {};

    headerRawData.customerCount     = std::uniform_int_distribution<unsigned int> (1, 100000)(rd);
    headerRawData.workTime          = std::uniform_int_distribution<unsigned int> (1, 1000000000)(rd);
    headerRawData.cigaretteBreakLen = std::uniform_int_distribution<unsigned int> (1, 999999999)(rd);

    return headerRawData;
}

bin_generator::customer bin_generator::generateCustomer() {
    return bin_generator::customer();
}

char *bin_generator::data() {
    return nullptr;
}


int main(int argc, char *argv[]) {


    return 0;
}
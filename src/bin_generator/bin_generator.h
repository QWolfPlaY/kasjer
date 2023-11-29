//
// Created by WolfPlay on 11/14/2023.
//

#ifndef KASJER_BIN_GENERATOR_H
#define KASJER_BIN_GENERATOR_H

class bin_generator {
public:
    typedef struct {
        unsigned int customerCount;
        unsigned int workTime;
        unsigned int cigaretteBreakLen;
    } header;
    typedef struct {
        unsigned int entryTime;
        unsigned int timeUsage;
    } customer;

    static header generateHeader();
    static customer generateCustomer(header headerRawData);
    static size_t calculateSize(header headerRawData);
    static char* generateByteData(header headerRawData);
};


#endif //KASJER_BIN_GENERATOR_H

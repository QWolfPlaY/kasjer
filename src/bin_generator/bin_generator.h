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
        unsigned char byteData[12] = {};
    } header;
    typedef struct {
        unsigned int entryTime;
        unsigned int timeUsage;
    } customer;

    static header generateHeader();
    static customer generateCustomer();

    static char* data();
};


#endif //KASJER_BIN_GENERATOR_H

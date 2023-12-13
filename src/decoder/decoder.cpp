//
// Created by WolfPlay on 01/12/2023.
//

#include "decoder.h"
#include "bin_generator.h"
#include "cpp-core/core.h"

bin_generator::header decoder::headerFromBytes(char* headerByteData)
{
    bin_generator::header header;

    memcpy(&header.customerCount, headerByteData, sizeof(bin_generator::header().customerCount));
    memcpy(&header.workTime,
           headerByteData + sizeof(bin_generator::header().customerCount),
           sizeof(bin_generator::header().workTime)
           );
    memcpy(&header.workTime,
           headerByteData + sizeof(bin_generator::header().customerCount) + sizeof(bin_generator::header().workTime),
           sizeof(bin_generator::header().cigaretteBreakLen)
           );

    return header;
}

bin_generator::customer decoder::customerFromBytes(char* customersByteData, size_t offset, const bool BYTE_OFFSET = true)
{
    bin_generator::customer customer;

    if (!BYTE_OFFSET) {
        offset *= bin_generator::CUSTOMER_SIZE;
    }

    memcpy(&customer.entryTime, customersByteData + offset, sizeof(bin_generator::customer().entryTime));
    memcpy(&customer.entryTime,
           customersByteData + offset + sizeof(bin_generator::customer().entryTime),
           sizeof(bin_generator::customer().timeUsage)
           );

    return customer;

}

bool decoder::verifyByteFile(char* headerByteData, size_t fileSize)
{
    bin_generator::header header = headerFromBytes(headerByteData);

    size_t totalCustomerByteSize = header.customerCount * bin_generator::CUSTOMER_SIZE;

    if ((fileSize - bin_generator::HEADER_SIZE) < totalCustomerByteSize) { return false; }
    else { return true; }
}

bool decoder::verifyRawData(bin_generator::header header, std::vector<bin_generator::customer> customers)
{
    unsigned int customersTimeSum = 0;

    for (bin_generator::customer customer : customers) {
        customersTimeSum += customer.entryTime;
        customersTimeSum += customer.timeUsage;
    }

    bool isTotalTimeCorrect = true;
    bool isCustomerCountCorrect = true;
    bool isCigaretteBreakLenCorrect = true;

    if (customersTimeSum > header.workTime) { isTotalTimeCorrect = false; }
    else if (customers.size() != header.customerCount) { isCustomerCountCorrect = false; }
    else if (header.cigaretteBreakLen > header.workTime) { isCigaretteBreakLenCorrect = false; }

    if (isTotalTimeCorrect && isCustomerCountCorrect && isCigaretteBreakLenCorrect) { return true; }
    else { return false; }
}

unsigned int decoder::calculateBreaks(bin_generator::header headerRawData, bin_generator::customer* customersRawData)
{
    
    return 0;
}

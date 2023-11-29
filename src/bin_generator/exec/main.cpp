#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <mutex>
#include <filesystem>

#include "spdlog/spdlog.h"
#include "bin_generator.h"

int main(int argc, char *argv[]) {
#ifdef LOGGING_LEVEL
    spdlog::set_level(LOGGING_LEVEL);
#else
    spdlog::set_level(spdlog::level::info);
#endif

    bin_generator::header header = bin_generator::generateHeader();
    spdlog::info("Generated header:");
    spdlog::info("Customer count: " + std::to_string(header.customerCount));
    spdlog::info("Work time: " + std::to_string(header.workTime));
    spdlog::info("Cigarette break length: " + std::to_string(header.cigaretteBreakLen));

    spdlog::info("Generating binary data...");
    auto start = std::chrono::high_resolution_clock::now();
    char* binaryData = bin_generator::generateByteData(header);
    auto end = std::chrono::high_resolution_clock::now();
    auto execTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    spdlog::debug("Took " + std::to_string(execTime.count()) + "ns");
    spdlog::debug("Average: " + std::to_string(execTime.count() / header.customerCount) + " ns/customer");

    std::filesystem::path dirPath = "./data/";

    spdlog::info("Writing results to file...");
    if (!std::filesystem::exists(dirPath)) {
        spdlog::debug("Creating folder...");
        try {
            std::filesystem::create_directory(dirPath);
            spdlog::debug("Folder created successfully");
        } catch (const std::exception &exception) {
            spdlog::error("Error creating folder: " + std::string(exception.what()));
            return -1;
        }
    } else {
        spdlog::debug("Folder already exists");
    }


    spdlog::debug("Finding free filename...");
    unsigned short fileNum = 0;
    std::filesystem::path filePath;
    do {
        filePath = "./data/data" + std::to_string(fileNum) + ".bin";
        fileNum++;
    } while(std::filesystem::exists(filePath));

    spdlog::debug("Found free filename: data" + std::to_string(fileNum) + ".bin");
    spdlog::debug("Opening file for writing");
    std::ofstream outFile(filePath, std::ios::binary);
    if (!outFile) {
        spdlog::error("Error opening file for writing!");
        return -2;
    } else {
        spdlog::debug("Opened file for writing");
    }

    spdlog::debug("Creating file mutex");
    std::mutex fileMutex;

    spdlog::debug("Locking file mutex");
    std::unique_lock<std::mutex> lock(fileMutex);

    spdlog::debug("Writing binary data to file...");
    auto writeStart = std::chrono::high_resolution_clock::now();
    outFile.write(binaryData, sizeof(binaryData));
    auto writeEnd = std::chrono::high_resolution_clock::now();
    spdlog::debug("Done writing to file");
    auto writeTime = std::chrono::duration_cast<std::chrono::microseconds>(writeEnd - writeStart);
    spdlog::debug("Took: " + std::to_string(writeTime.count()) + "µs");

    outFile.close();
    spdlog::debug("Closed file");
    spdlog::info("Done :)");

    return 0;
}
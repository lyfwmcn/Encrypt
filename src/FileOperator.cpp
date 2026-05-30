#include "FileOperator.hpp"
#include <fstream>
#include <iostream>
#include <functional>
#include <stdexcept>
#include "Config.hpp"

void Hsr::FileOperator::read(const std::string& filePath, bool isLockedFile) {
    std::ifstream is(filePath, std::ios::in | std::ios::binary);
    if (!is.is_open()) {
        throw std::runtime_error(filePath + " can't open");
    }
    is.seekg(0, std::ios::end);
    size_t fileSize = is.tellg();
    is.seekg(0, std::ios::beg);
    if (isLockedFile) {
        if (fileSize < Hsr::lockedFileHeader.size()) {
            is.close();
            throw std::runtime_error(filePath + " is not a locked file");
        }
        char temp;
        size_t size = Hsr::lockedFileHeader.size();
        for (size_t i = 0; i < size; ++i) {
            is.read(&temp, 1);
            if (temp != Hsr::lockedFileHeader[i]) {
                is.close();
                throw std::runtime_error(filePath + " is not a locked file");
            }
        }
        fileSize -= size;
    }
    data.resize(fileSize);
    is.read(data.data(), fileSize);
    is.close();
}

void Hsr::FileOperator::write(const std::string& filePath, bool isLockedFile) const {
    std::ofstream os(filePath, std::ios::out | std::ios::binary);
    if (!os.is_open()) {
        throw std::runtime_error(filePath + " can't open");
    }
    if (isLockedFile) {
        os.write(Hsr::lockedFileHeader.data(), Hsr::lockedFileHeader.size());
    }
    os.write(data.data(), data.size());
    os.close();
}

void Hsr::FileOperator::encrypt(const std::string& key) {
    size_t len {key.size()};
    size_t size {data.size()};
    for (size_t i = 0; i < size; ++i) {
        data[i] ^= key[i % len];
    }
}

void Hsr::FileOperator::decrypt(const std::string& key) {
    encrypt(key);
}

void Hsr::FileOperator::hexPrint() const {
    hexPrint(data.size());
}

void Hsr::FileOperator::hexPrint(size_t maxBytes) const {
    std::function<unsigned int(char)> helperFunc1 {
        [](char c) -> unsigned int {
            int x {static_cast<int>(c)};
            return x >= 0 ? static_cast<unsigned int>(x) : static_cast<unsigned int>(256 + x);
        }
    };
    std::function<char(unsigned int)> helperFunc2 {
        [](unsigned int v) -> char {
            return v < 10 ? v + 48 : v + 55;
        }
    };
    size_t size {data.size() <= maxBytes ? data.size() : maxBytes};
    for (size_t i = 0; i < size; ++i) {
        unsigned int c {helperFunc1(data[i])};
        unsigned int highValue {c / 16};
        unsigned int lowValue {c % 16};
        std::cout << helperFunc2(highValue) << helperFunc2(lowValue);
        if (i + 1 < size) {
            std::cout << " ";
        }
    }
    std::cout << std::endl;
}

bool Hsr::FileOperator::hasSuffix(const std::string& fileName, const std::string& suffix) {
    if (fileName.size() < suffix.size()) {
        return false;
    }
    size_t temp = fileName.size() - suffix.size();
    size_t size = suffix.size();
    for (size_t i = 0; i < size; ++i) {
        if (fileName[temp + i] != suffix[i]) {
            return false;
        }
    }
    return true;
}

// FileReader.cpp

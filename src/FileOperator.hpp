#pragma once

#include <string>
#include <vector>

namespace Hsr {
    class FileOperator {
        std::vector<char> data;

    public:
        FileOperator() = default;
        FileOperator(const FileOperator&) = delete;
        FileOperator& operator=(const FileOperator&) = delete;
        ~FileOperator() = default;

        void read(const std::string& filePath, bool isLockedFile);

        void write(const std::string& filePath, bool isLockedFile) const;

        void encrypt(const std::string& key);

        void decrypt(const std::string& key);

        static bool hasSuffix(const std::string& fileName, const std::string& suffix);
    };
}

// FileReader.hpp

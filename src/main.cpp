#include <iostream>
#include <cstring>
#include "FileOperator.hpp"
#include "ToolFunction.hpp"
#include "Config.hpp"
#include <stdexcept>

int main(int argc, char* argv[]) {
    if (argc > 1) {
        if (Hsr::strcmp(argv[1], "-en") && argc == 4) {
            Hsr::FileOperator oper;
            try {
                oper.read(argv[2], false);
            }
            catch(const std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
                return EXIT_FAILURE;
            }
            oper.encrypt(argv[3]);
            std::string newFilePath {argv[2]};
            newFilePath.append(Hsr::lockedFileSuffix);
            try {
                oper.write(newFilePath, true);
            }
            catch(const std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
                return EXIT_FAILURE;
            }
        }
        else if (Hsr::strcmp(argv[1], "-de") && argc == 4) {
            if (!Hsr::FileOperator::hasSuffix(argv[2], Hsr::lockedFileSuffix)) {
                std::cerr << argv[2] << " is not a locked file" << std::endl;
                return EXIT_FAILURE;
            }
            Hsr::FileOperator oper;
            try {
                oper.read(argv[2], true);
            }
            catch(const std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
                return EXIT_FAILURE;
            }
            oper.decrypt(argv[3]);
            std::string newFilePath {argv[2]};
            try {
                oper.write(newFilePath.substr(0, newFilePath.size() - Hsr::lockedFileSuffix.size()), false);
            }
            catch(const std::runtime_error& e) {
                std::cerr << e.what() << std::endl;
                return EXIT_FAILURE;
            }
        }
        else if (Hsr::strcmp(argv[1], "--help") && argc == 2) {
            std::cout << "--help: get help" << std::endl;
            std::cout << "-en [filePath] [key]: encrypt filePath by key" << std::endl;
            std::cout << "-de [filePath] [key]: decrypt filePath by key" << std::endl;
        }
        else {
            std::cerr << "Command Fault" << std::endl;
            return 2;
        }
    }
    else {
        std::cout << "Enter \"[exePath] --help\" to Get Help" << std::endl;
        return 2;
    }
    return 0;
}

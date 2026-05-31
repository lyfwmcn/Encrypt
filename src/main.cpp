#include <iostream>
#include "FileOperator.hpp"
#include "ToolFunction.hpp"
#include "Config.hpp"

int main(int argc, char* argv[]) {
    if (argc == 2 && Hsr::strcmp(argv[1], "--help")) {
        std::cout << "--help: get help" << std::endl;
        std::cout << "-en [filePath] [key]: encrypt filePath by key" << std::endl;
        std::cout << "-de [filePath] [key]: decrypt filePath by key" << std::endl;
        return EXIT_SUCCESS;
    }
    if (argc == 4 && Hsr::strcmp(argv[1], "-en")) {
        Hsr::FileOperator oper;
        try {
            oper.read(argv[2], false);
        }
        catch(const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        }
        try {
            oper.encrypt(argv[3]);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        }
        std::string newFilePath {argv[2]};
        newFilePath.append(Hsr::lockedFileSuffix);
        try {
            oper.write(newFilePath, true);
        }
        catch(const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
    if (argc == 4 && Hsr::strcmp(argv[1], "-de")) {
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
        try {
            oper.decrypt(argv[3]);
        }
        catch(const std::invalid_argument& e) {
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        }
        std::string newFilePath {argv[2]};
        newFilePath.erase(newFilePath.size() - Hsr::lockedFileSuffix.size(), Hsr::lockedFileSuffix.size());
        try {
            oper.write(newFilePath, false);
        }
        catch(const std::runtime_error& e) {
            std::cerr << e.what() << std::endl;
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
    std::cerr << "command fault" << std::endl;
    std::cerr << "enter \"[exePath] --help\" to get help" << std::endl;
    return 2;
}

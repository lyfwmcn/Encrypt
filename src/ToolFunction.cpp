#include "ToolFunction.hpp"

bool Hsr::strcmp(const char* str0, const char* str1) {
    while (*str0 != '\0' && *str1 != '\0') {
        if (*str0 != *str1) {
            return false;
        }
        ++str0;
        ++str1;
    }
    return *str0 == '\0' && *str1 == '\0';
}

// ToolFunction.cpp

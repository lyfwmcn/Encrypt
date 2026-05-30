#pragma once

#include <string>
#include <vector>

namespace Hsr {
    inline const std::string lockedFileSuffix(".hlock");
    inline const std::vector<char> lockedFileHeader {'h', 's', 'r', 't'};
}

// Config.hpp

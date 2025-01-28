#include <iostream>
#include <string>
#include <map>
#include "Buffer.h"

#pragma once

typedef std::map<std::string, FunctionPointer> CommandMap;

namespace Commands {
    inline std::string current = "";

    inline CommandMap* Map = new CommandMap();

    extern std::tuple<bool, bool> execute(std::string executing);
    extern void init();
}

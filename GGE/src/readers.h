#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include "stage.h"

namespace Reader {
    std::tuple<Stage*, std::string> readLine(std::string line);

    Stage_Text* read_Text(std::string file);
}

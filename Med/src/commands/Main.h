#include "../Functions.h"
#include "../Commands.h"

#pragma once

#define cM(X, Y) Commands::Map->insert({#X, Functions::Y})

namespace CommandMapping {
    extern void mainInit();
    extern void commandInit();
    extern void init();
}

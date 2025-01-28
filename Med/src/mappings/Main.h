#include "../Buffer.h"
#include "../Functions.h"
#include "../Settings.h"

#pragma once

#define cK(X, Y, Z) Modes::X->map.insert({Keys::construct Y, Z});

namespace Mappings {
    extern void init();
    extern void mainInit();
    extern void commandInit();
}

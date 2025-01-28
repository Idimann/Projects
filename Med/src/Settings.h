#include "Buffer.h"
#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>

#pragma once

typedef std::tuple<short, short, short, short> Color_S;

typedef struct {
    short number;
    short fg;
    short bg;
} Color;

namespace Settings {
    namespace Colors {
        namespace Singulars {
#define makeColor(N, X, Y, Z) std::make_tuple(N, X, Y, Z);
            extern void update();
            inline Color_S statusBar = makeColor(1, 100, 100, 100);
            inline Color_S highlighting = makeColor(2, 200, 200, 200);
            inline Color_S cursorFG = makeColor(3, 0, 0, 0);
            inline Color_S cursorBG = makeColor(4, 255, 255, 255);
        }

#define getSingular(X) std::get<0>(Singulars::X)

        inline Color statusBar = {
            .number = 1,
            .fg = -1,
            .bg = getSingular(statusBar),
        };

        inline Color highlighting = {
            .number = 2,
            .fg = -1,
            .bg = getSingular(highlighting),
        };

        inline Color cursor = {
            .number = 3,
            .fg = getSingular(cursorFG),
            .bg = getSingular(cursorBG),
        };

        extern void updateThese();
        extern void update();
    }
    
    inline unsigned char boundShifting = 4;
    inline unsigned char tabSize = 4;
    inline bool no_CTRL_C = true;
}

#include <ncurses.h>
#include "Settings.h"

#define in_cl(X) \
if(std::get<0>(Settings::Colors::Singulars::X) != -1) { \
    init_color(std::get<0>(Settings::Colors::Singulars::X),\
        std::get<1>(Settings::Colors::Singulars::X),\
        std::get<2>(Settings::Colors::Singulars::X),\
        std::get<3>(Settings::Colors::Singulars::X));\
}

extern void Settings::Colors::Singulars::update() {
    in_cl(statusBar);
    in_cl(highlighting);
    in_cl(cursorBG);
    in_cl(cursorFG);
}

#define in_pr(X) init_pair(Settings::Colors::X.number, \
        Settings::Colors::X.fg, \
        Settings::Colors::X.bg)

extern void Settings::Colors::updateThese() {
    in_pr(statusBar);
    in_pr(highlighting);
    in_pr(cursor);
}

extern void Settings::Colors::update() {
    Singulars::update();
    updateThese();
}

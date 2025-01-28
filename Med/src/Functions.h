#include <iostream>
#include <string>
#include "Buffer.h"

#pragma once

#define newMapFunction(X) \
    std::tuple<bool, bool> \
X(struct Buffer& buffer, struct WindowInformation &wInfo, std::vector<std::string> args)

namespace Functions {
    extern newMapFunction(TransitionCursors);

    extern newMapFunction(MoveUp);
    extern newMapFunction(MoveDown);
    extern newMapFunction(MoveLeft);
    extern newMapFunction(MoveRight);
    extern newMapFunction(MoveRightWord);
    extern newMapFunction(MoveLeftWord);
    extern newMapFunction(MoveWordBeginning);
    extern newMapFunction(MoveWordEnd);
    extern newMapFunction(MoveStart);
    extern newMapFunction(MoveEndRaw);
    extern newMapFunction(MoveStartRaw);
    extern newMapFunction(MoveEnd);
    extern newMapFunction(InsertChar);
    extern newMapFunction(PopChar);

    extern newMapFunction(SplitWindowRight);
    extern newMapFunction(SplitWindowLeft);
    extern newMapFunction(SplitWindowTop);
    extern newMapFunction(SplitWindowBottom);

    extern newMapFunction(ExitEditor);
    extern newMapFunction(SaveFile);

    extern newMapFunction(SwitchToCommandMode);
    extern newMapFunction(RemoveCommandChar);
    extern newMapFunction(InsertCommandChar);
    extern newMapFunction(ExecuteCommand);
    extern newMapFunction(ExitCommand);
}

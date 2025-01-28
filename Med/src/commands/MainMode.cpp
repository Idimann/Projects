#include "Main.h"

extern void CommandMapping::mainInit() {
    cM(transition-cursors, TransitionCursors);
    cM(exit, ExitEditor);
    cM(cursor-up, MoveUp);
    cM(cursor-down, MoveDown);
    cM(cursor-left, MoveLeft);
    cM(cursor-right, MoveRight);
    cM(cursor-right-word, MoveRightWord);
    cM(cursor-left-word, MoveLeftWord);
    cM(cursor-word-end, MoveWordEnd);
    cM(cursor-word-beginning, MoveWordBeginning);
    cM(line-start, MoveStart);
    cM(line-end, MoveEnd);
    cM(line-start-raw, MoveStartRaw);
    cM(line-end-raw, MoveEndRaw);
    cM(insert-char, InsertChar);
    cM(pop-char, PopChar);
    cM(save-file, SaveFile);
    cM(window-split-right, SplitWindowRight);
    cM(window-split-left, SplitWindowLeft);
    cM(window-split-top, SplitWindowTop);
    cM(window-split-bottom, SplitWindowBottom);
}

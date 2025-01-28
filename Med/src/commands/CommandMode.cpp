#include "Main.h"

extern void CommandMapping::commandInit() {
    cM(command-mode, SwitchToCommandMode);
    cM(command-insert-char, InsertCommandChar);
    cM(command-pop-char, RemoveCommandChar);
    cM(command-execute, ExecuteCommand);
    cM(command-exit, ExitCommand);
}

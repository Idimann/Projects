#pragma once

#include <iostream>
#include <string>

typedef struct {
    unsigned int key;
    std::string mode;
} KeyMapping;

class Window;
typedef void (*FunctionPointer) (Window& window);

extern void addModeMapping(const KeyMapping key, FunctionPointer);
extern void getModeMapping(const KeyMapping key);

#include <map>
#include "Mappings.h"
#include "Mode.h"

std::map<KeyMapping, FunctionPointer> Function_mappings = std::map<KeyMapping, FunctionPointer>();

extern void createDefaultMappings() {
    addModeMapping({
            .key = 'i
}

extern void addModeMapping(const KeyMapping key, FunctionPointer mapping) {
    Function_mappings[key] = mapping;
}

extern void doModeMapping(const KeyMapping key) {
    (*Function_mappings[key])();
}

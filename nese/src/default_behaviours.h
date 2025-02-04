#pragma once

#include "window.h"

#define CTRL(x) ((x) & 0x1f)

void default_behaviours_init();

void default_behaviours_behaviour_toggles();
void default_behaviours_movement();
void default_behaviours_type();

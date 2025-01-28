#pragma once

#include <iostream>
#include <string>

extern void init();

extern int clampInt(const int value, const int min, const int max);
extern int minInt(const int first, const int second);
extern std::string replaceAll(std::string str, const std::string from, const std::string to);
extern std::string createMultiChar(const char character, const int number);

//Quitting/switchting back to normal mode
#define CODE_DONE 1
#define CODE_EXIT 2

//Windows
#define CODE_SPLIT_VR 3
#define CODE_SPLIT_HT 4
#define CODE_SPLIT_VL 5
#define CODE_SPLIT_HB 6
#define CODE_MOVE_U 7
#define CODE_MOVE_D 8
#define CODE_MOVE_L 9
#define CODE_MOVE_R 10

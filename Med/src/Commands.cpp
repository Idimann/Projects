#include "Commands.h"
#include "Functions.h"
#include "commands/Main.h"
#include "Window.h"

namespace Commands {
    extern void init() {
        CommandMapping::init();
    }

    extern std::tuple<bool, bool> execute(std::string executing) {
        std::tuple<bool, bool> returning = std::make_tuple(false, true);
        std::vector<std::string> args = std::vector<std::string>();
        executing += ' ';

        size_t pos = 0;
        std::string token = "";
        while ((pos = executing.find(" ")) != std::string::npos) {
            token = executing.substr(0, pos);
            args.push_back(token);
            executing.erase(0, pos + 1);
        }

        token = args[0];
        args.erase(args.begin());

        if(Commands::Map->count(token)) {
            unsigned int currentWindow = Windows::getCurrent();
            struct WindowInformation winInfo = WindowInformation(Windows::get()->x, 
                    Windows::get()->y, 
                    Windows::get()->xSize, 
                    Windows::get()->ySize);
            returning = Commands::Map->find(token)->second(*Windows::get()->buffer, winInfo, args);

            bool changed = (Windows::get(currentWindow)->x != winInfo.x) || 
                (Windows::get(currentWindow)->y != winInfo.y) ||
                (Windows::get(currentWindow)->xSize != winInfo.xSize) ||
                (Windows::get(currentWindow)->ySize != winInfo.ySize);

            Windows::get(currentWindow)->x = winInfo.x;
            Windows::get(currentWindow)->y = winInfo.y;
            Windows::get(currentWindow)->xSize = winInfo.xSize;
            Windows::get(currentWindow)->ySize = winInfo.ySize;

            if(changed)
                Windows::get()->resize();
        }

        return returning;
    }
}

#include <fstream>
#include <tuple>
#include "Functions.h"
#include "Buffer.h"
#include "Utility.h"
#include "Window.h"
#include "curses/curses.h"
#include "Commands.h"
#include "Settings.h"

namespace Functions {
#define mT(X, Y) std::make_tuple(X, Y)

    extern newMapFunction(TransitionCursors) {
        for(int i = 0; i < buffer.position.size(); i++)
            buffer.position[i].moving = !buffer.position[i].moving;

        return mT(true, true);
    }

    extern newMapFunction(MoveUp) {
        if(Buffers::getY(buffer, wInfo.xSize, 0) == 0)
            return mT(false, false);

        for(int i = 0; i < buffer.position.size(); i++) {
            buffer.position[i].swapPrevious();

            buffer.position[i].addPosition(-Buffers::getBackToNewLine(buffer, i) - 1);
            buffer.position[i].addPosition(-Buffers::getBackToNewLine(buffer, i));
            buffer.position[i].addPosition(std::min(Buffers::getUntilNewLine(buffer, i) - 1, 
                        buffer.position[i].getX()));
        }


        if(buffer.bound != 0 && Buffers::getY(buffer, wInfo.xSize, 0) < Settings::boundShifting)
            buffer.bound -= Buffers::getLineSizeBackwards(buffer) - 1;

        return mT(true, false);
    }

    extern newMapFunction(MoveDown) {
        if(!Buffers::isNewLine(buffer, buffer.position.size() - 1))
            return mT(false, false);

        for(int i = 0; i < buffer.position.size(); i++) {
            buffer.position[i].swapPrevious();

            buffer.position[i].addPosition(Buffers::getUntilNewLine(buffer, i));
            buffer.position[i].addPosition(std::min(Buffers::getUntilNewLine(buffer, i) - 1, 
                        buffer.position[i].getX()));
        }


        if(Buffers::isNewLineTimes(buffer, Settings::boundShifting, buffer.position.size() - 1) &&
                Buffers::getY(buffer, wInfo.xSize, buffer.position.size() - 1) >=
                wInfo.ySize - Settings::boundShifting - 1)
            buffer.bound += Buffers::getLineSize(buffer);

        return mT(true, false);
    }

    extern newMapFunction(MoveLeft) {
        if(buffer.position[0].getPosition() == 0)
            return mT(false, false);

        for(int i = 0; i < buffer.position.size(); i++) {
            buffer.position[i].addPosition(-1);
            buffer.position[i].setX(Buffers::getBackToNewLine(buffer, i));

            buffer.position[i].setXOp(buffer.position[i].getX());
            buffer.position[i].setPositionOp(buffer.position[i].getPosition());
        }

        if(buffer.bound != 0 && Buffers::getY(buffer, wInfo.xSize, 0) < Settings::boundShifting)
            buffer.bound -= Buffers::getLineSizeBackwards(buffer) - 1;

        return mT(true, false);
    }

    extern newMapFunction(MoveRight) {
        if(buffer.position[buffer.position.size() - 1].getPosition() >= buffer.text.length() - 1)
            return mT(false, false);

        for(int i = 0; i < buffer.position.size(); i++) {
            buffer.position[i].addPosition(1);
            buffer.position[i].setX(Buffers::getBackToNewLine(buffer, i));

            buffer.position[i].setXOp(buffer.position[i].getX());
            buffer.position[i].setPositionOp(buffer.position[i].getPosition());
        }

        if(Buffers::isNewLineTimes(buffer, Settings::boundShifting, buffer.position.size() - 1) &&
                Buffers::getY(buffer, wInfo.xSize, buffer.position.size() - 1) 
                >= wInfo.ySize - Settings::boundShifting - 1)
            buffer.bound += Buffers::getLineSize(buffer);

        return mT(true, false);
    }

    extern newMapFunction(MoveLeftWord) {
        if(buffer.position[0].getPosition() == 0)
            return mT(false, false);

        buffer.position[0].swapPrevious();

        const int subtracting = Buffers::getUntilWordBackwards(buffer, 0);
        if(subtracting == -1) {
            buffer.position[0].setPosition(0);
            buffer.position[0].setX(0);

            for(int i = 1; i < buffer.position.size(); i++) {
                buffer.position[i].swapPrevious();

                buffer.position[i].addPosition(-Buffers::getUntilWordBackwards(buffer, i));
                buffer.position[i].setX(Buffers::getBackToNewLine(buffer, i));
            }

            return mT(false, false);
        }

        for(int i = 0; i < buffer.position.size(); i++) {
            buffer.position[i].swapPrevious();

            buffer.position[i].addPosition(-Buffers::getUntilWordBackwards(buffer, i));
            buffer.position[i].setX(Buffers::getBackToNewLine(buffer, i));
        }

        if(buffer.bound != 0 && Buffers::getY(buffer, wInfo.xSize, 0) < Settings::boundShifting)
            buffer.bound -= Buffers::getLineSizeBackwards(buffer) - 1;

        return mT(true, false);
    }

    extern newMapFunction(MoveRightWord) {
        if(buffer.position[buffer.position.size() - 1].getPosition() >= buffer.text.length() - 1)
            return mT(false, false);

        for(int i = 0; i < buffer.position.size(); i++) {
            buffer.position[i].swapPrevious();

            buffer.position[i].addPosition(Buffers::getUntilWord(buffer, i));
            buffer.position[i].setX(Buffers::getBackToNewLine(buffer, i));
        }

        if(Buffers::isNewLineTimes(buffer, Settings::boundShifting, buffer.position.size() - 1) &&
                Buffers::getY(buffer, wInfo.xSize, buffer.position.size() - 1) >=
                wInfo.ySize - Settings::boundShifting - 1)
            buffer.bound += Buffers::getLineSize(buffer);

        return mT(true, false);
    }

    extern newMapFunction(MoveWordBeginning) {
        for(int i = 0; i < buffer.position.size(); i++) {
            buffer.position[i].swapPrevious();

            unsigned int x = buffer.position[i].getX();
            if(std::get<0>(Commands::execute("cursor-left-word"))) {
                Commands::execute("cursor-right-word");

                if(buffer.position[i].getX() == x) {
                    Commands::execute("cursor-left-word");
                    return Commands::execute("cursor-word-beginning");
                }
            }
        }

        return mT(true, false);
    }

    extern newMapFunction(MoveWordEnd) {
        for(int i = 0; i < buffer.position.size(); i++) {
            buffer.position[i].swapPrevious();

            unsigned int x = buffer.position[i].getX();
            if(std::get<0>(Commands::execute("cursor-right-word"))) {
                Commands::execute("cursor-left-word");

                if(buffer.position[i].getX() == x) {
                    Commands::execute("cursor-right-word");
                    return Commands::execute("cursor-word-end");
                }
            }
        }

        return mT(true, false);
    }

    extern newMapFunction(MoveStart) {
        for(int i = 0; i < buffer.position.size(); i++) {
            buffer.position[i].swapPrevious();

            unsigned int x = buffer.position[i].getX();

            buffer.position[i].addPosition(-buffer.position[i].getX());
            buffer.position[i].setX(0);
            Buffers::moveTillNoWhitespace(buffer, i);

            if(x == buffer.position[i].getX()) {
                Commands::execute("cursor-up");
                return Commands::execute("line-start-raw");
            }
        }

        return mT(true, false);
    }

    extern newMapFunction(MoveEnd) {
        if(buffer.position[buffer.position.size() - 1].getPosition() >= buffer.text.length() - 1)
            return mT(false, true);

        for(int i = 0; i < buffer.position.size(); i++) {
            buffer.position[i].swapPrevious();

            const unsigned int moving = Buffers::getUntilNewLine(buffer, i) - 1;

            if(moving == 0) {
                Commands::execute("cursor-down");
                return Commands::execute("line-end-raw");
            }

            buffer.position[i].addX(moving);
            buffer.position[i].addPosition(moving);
        }

        return mT(true, false);
    }

    extern newMapFunction(MoveEndRaw) {
        for(int i = 0; i < buffer.position.size(); i++) {
            if(buffer.text[buffer.position[i].getPosition()] == '\n')
                continue;

            buffer.position[i].swapPrevious();

            const unsigned int moving = Buffers::getUntilNewLine(buffer, i) - 1;

            buffer.position[i].addX(moving);
            buffer.position[i].addPosition(moving);
        }

        return mT(true, false);
    }

    extern newMapFunction(MoveStartRaw) {
        for(int i = 0; i < buffer.position.size(); i++) {
            buffer.position[i].swapPrevious();

            unsigned int x = buffer.position[i].getX();

            buffer.position[i].addPosition(-buffer.position[i].getX());
            buffer.position[i].setX(0);
            Buffers::moveTillNoWhitespace(buffer, i);
        }

        return mT(true, false);
    }

    extern newMapFunction(InsertChar) {
        const std::string inserting = Utils::parseDesc(args[0]);
        for(int i = 0; i < buffer.position.size(); i++) {
            buffer.text.insert(buffer.position[i].getPosition(), inserting);
            buffer.colors.insert(buffer.colors.begin() + buffer.position[i].getPosition(), inserting.size(),
                    buffer.colors[buffer.position[i].getPosition()]);
            buffer.position[i].addPosition(1);
            buffer.position[i].setX(Buffers::getBackToNewLine(buffer, i));
        }

        return mT(true, true);
    }

    extern newMapFunction(PopChar) {
        if(buffer.text.empty() || buffer.position[0].getPosition() == 0)
            return mT(false, true);

        for(int i = 0; i < buffer.position.size(); i++) {
            buffer.text.erase(buffer.position[i].getPosition() - 1, 1);
            buffer.colors.erase(buffer.colors.begin() + buffer.position[i].getPosition() - 1);
            buffer.position[i].addPosition(-1);
            buffer.position[i].setX(Buffers::getBackToNewLine(buffer, i));
        }

        return mT(true, true);
    }

    extern newMapFunction(SplitWindowRight) {
        const unsigned int xSize = wInfo.xSize;
        wInfo.xSize /= 2;

        Buffers::add(new Buffer("--new--"));
        Windows::add(new Window(Buffers::getLast(), wInfo.x + wInfo.xSize,
                    wInfo.y, xSize - wInfo.xSize, wInfo.ySize));
        Windows::setCurrent(Windows::getSize() - 1);
        
        return mT(true, true);
    }

    extern newMapFunction(SplitWindowLeft) {
        const unsigned int xSize = wInfo.xSize;
        wInfo.xSize /= 2;
        wInfo.x += wInfo.xSize;

        Buffers::add(new Buffer("--new--"));
        Windows::add(new Window(Buffers::getLast(), wInfo.x - wInfo.xSize,
                    wInfo.y, xSize - wInfo.xSize, wInfo.ySize));
        Windows::setCurrent(Windows::getSize() - 1);
        
        return mT(true, true);
    }

    extern newMapFunction(SplitWindowTop) {
        return mT(false, true);
    }

    extern newMapFunction(SplitWindowBottom) {
        return mT(false, true);
    }

    extern newMapFunction(SwitchToCommandMode) {
        buffer.mode = &Modes::Command;

        return mT(true, true);
    }

    extern newMapFunction(ExitEditor) {
        quitNcurses();

        return mT(false, true);
    }

    extern newMapFunction(InsertCommandChar) {
        Commands::current += Utils::parseDesc(args[0]);

        return mT(true, false);
    }

    extern newMapFunction(RemoveCommandChar) {
        if(Commands::current.empty())
            return mT(false, false);

        Commands::current.pop_back();

        return mT(true, false);
    }

    extern newMapFunction(ExecuteCommand) {
        bool returning = std::get<0>(Commands::execute(Commands::current));
        Commands::current = "";

        buffer.mode = &Modes::Main;

        return mT(returning, true);
    }

    extern newMapFunction(ExitCommand) {
        Commands::current = "";

        return mT(false, true);
    }

    extern newMapFunction(SaveFile) {
        if(!buffer.isFile)
            return mT(false, true);

        if(buffer.fileName == "") {
            unsigned int number = 1;
            while(std::ifstream(buffer.fileName).good()) {
                buffer.fileName = "untitled-" + std::to_string(number);
                ++number;
            }
            buffer.name = buffer.fileName;
        }

        std::ofstream writing(buffer.fileName.c_str());
        const std::string multiChar = Utils::constructNumber(Settings::tabSize, ' ');
        std::string text = buffer.text;
        Utils::replaceAll(text, multiChar, "\t");
        writing << text.c_str();
        writing.close();

        return mT(true, true);
    }
}

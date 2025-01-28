#include <curses.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "Buffer.h"
#include "Settings.h"
#include "curses/curses.h"
#include "Functions.h"
#include "Utility.h"
#include "mappings/Main.h"

namespace Keys {
    extern KeyMapping construct(const std::vector<unsigned short> input) {
        KeyMapping returning = 0;
        returning |= (KeyMapping) input[0];

        for(int i = 1; i < input.size(); i++)
            returning |= (((KeyMapping) input[i]) << (i * 10));

        return returning;
    }
}

namespace Modes {
    extern void init() {
        Mappings::init();
    }
}

std::vector<Buffer*> bufferList = std::vector<Buffer*>();

namespace Buffers {
    extern std::string loadFile(const char* fileName) {
        std::ifstream f(fileName);
        if(f.fail())
            return "\n";

        std::stringstream stringstream;
        stringstream << f.rdbuf();

        std::string returning = stringstream.str();
        Utils::replaceAll(returning, "\t", Utils::constructNumber(Settings::tabSize, ' '));

        return returning;
    }

    extern unsigned int getUntilNewLine(Buffer &buffer, const unsigned int index) {
        unsigned int returning = 0;
        
        for(int i = buffer.position[index].getPosition(); i < buffer.text.size(); i++) {
            ++returning;

            if(buffer.text[i] == '\n')
                break;
        }

        return returning;
    }

    extern int getUntilWord(Buffer &buffer, const unsigned int index) {
        unsigned int returning = 0;
        bool hit = false;
        bool everNotWhitespace = false;
        int backWord = -1;
        for(int i = buffer.position[index].getPosition(); i < buffer.text.size(); i++) {
            if(everNotWhitespace && Utils::isWhiteSpace(buffer.text[i])) {
                if(backWord == -1) {
                    backWord = returning;
                    everNotWhitespace = false;
                }
                else
                    return backWord + 1;
            }
            else if(!Utils::isWhiteSpace(buffer.text[i]))
                everNotWhitespace = true;

            if(Utils::isNonWordSpace(buffer.text[i]))
                hit = true;
            else if(hit)
                break;
            
            ++returning;
        }

        return returning;
    }

    extern int getUntilWordBackwards(Buffer &buffer, const unsigned int index) {
        unsigned int returning = 0;
        bool hit = false;
        bool everNotWhitespace = false;
        int backWord = -1;
        bool broken = false;
        for(int i = buffer.position[index].getPosition(); i > 0; i--) {
            if(everNotWhitespace && Utils::isWhiteSpace(buffer.text[i])) {
                if(backWord == -1) {
                    backWord = returning;
                    everNotWhitespace = false;
                }
                else
                    return backWord + 1;
            }
            else if(!Utils::isWhiteSpace(buffer.text[i]))
                everNotWhitespace = true;

            if(Utils::isNonWordSpace(buffer.text[i]))
                hit = true;
            else if(hit) {
                broken = true;
                break;
            }
            
            ++returning;
        }

        return broken ? returning : -1;
    }

    extern bool isNewLine(Buffer &buffer, const unsigned int index) {
        unsigned char returning = 0;
        for(int i = buffer.position[index].getPosition(); i < buffer.text.size(); i++) {
            if(buffer.text[i] == '\n')
                ++returning;

            if(returning == 2)
                return true;
        }

        return false;
    }

    extern unsigned int getLineSize(Buffer &buffer) {
        unsigned int returning = 0;
        
        for(int i = buffer.bound; i < buffer.text.size(); i++) {
            ++returning;

            if(buffer.text[i] == '\n')
                break;
        }

        return returning;
    }

    extern unsigned int getLineSizeBackwards(Buffer &buffer) {
        unsigned int returning = 0;
        bool foundNewLine = false;
        
        for(int i = buffer.bound; i >= 0; i--) {
            if(buffer.text[i] == '\n') {
                if(foundNewLine)
                    break;
                else
                    foundNewLine = true;
            }

            ++returning;
        }

        return returning;
    }

    extern bool isNewLineTimes(Buffer &buffer, unsigned int times, const unsigned int index) {
        unsigned int counting = 0;
        
        for(int i = buffer.position[index].getPosition(); i < buffer.text.size(); i++) {
            if(buffer.text[i] == '\n') {
                if(counting == times)
                    return true;
                else
                    ++counting;
            }
        }

        return false;
    }


    extern unsigned int getBackToNewLine(Buffer &buffer, const unsigned int index) {
        unsigned int returning = 0;
        
        for(int i = buffer.position[index].getPosition();
                i >= 0 && (returning == 0 || buffer.text[i] != '\n'); i--)
            ++returning;

        return returning - 1;
    }

    extern int getY(Buffer &buffer, const unsigned int size, const unsigned int index) {
        int returning = 0;
        unsigned int counting = 0;

        for(int i = std::min(buffer.bound, buffer.position[index].getPosition()); 
                i < std::max(buffer.bound, buffer.position[index].getPosition()); i++) {
            ++counting;

            if(buffer.text[i] == '\n' || counting > size) {
                counting = 0;
                ++returning;
            }
        }

        return std::min(buffer.bound, 
                buffer.position[index].getPosition()) == buffer.bound ? returning : (-returning);
    }

    extern void moveTillNoWhitespace(Buffer &buffer, const unsigned int index) {
        if(buffer.text[buffer.position[index].getPosition()] == '\n' && buffer.position[index].getPosition() != 0 &&
                buffer.text[buffer.position[index].getPosition() - 1] == '\n')
            return;

        for(int i = buffer.position[index].getPosition(); i < buffer.text.size() &&
                Utils::isWhiteSpace(buffer.text[i]); i++) {

            if(buffer.position[index].moving) {
                ++buffer.position[index].position2;
                ++buffer.position[index].x2;
            }
            else {
                ++buffer.position[index].position1;
                ++buffer.position[index].x1;
            }
        }
    }

    extern unsigned int getUntilNewLineWithStartPos(Buffer &buffer, const unsigned int startPos) {
        unsigned int returning = 0;

        for(int i = startPos; i < buffer.text.size(); i++) {
            ++returning;

            if(buffer.text[i] == '\n')
                break;
        }

        return returning;
    }

    extern void add(Buffer* buffer) {
        bufferList.push_back(buffer);
    }

    extern Buffer* get(const unsigned int number) {
        return bufferList[number];
    }

    extern Buffer* getLast() {
        return bufferList[bufferList.size() - 1];
    }
}

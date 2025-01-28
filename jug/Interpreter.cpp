#include <iostream>
#include <string>
#include <map>
#include <vector>

std::string stringifyVector(const std::vector<float>& input) {
    std::string returning = "";
    returning += '{';

    for(const float f : input) {
	returning += f;
	returning += ", ";
    }

    returning += "}\n";

    return returning;
}

typedef std::vector<float> (*Function) (std::vector<float>);

std::map<std::string, Function> functions{};

std::vector<float> process(std::string input) {
    std::string documenting;
    int bracketLevel;
    bool found;

    while(found) {
	documenting = "";
	bracketLevel = 0;
	found = false;
	for(char& c : input) {
	    if(bracketLevel)
		documenting += c;

	    if(c == '(') {
		if(!bracketLevel)
		    documenting = "";
		++bracketLevel;
	    }
	    else if(c == ')') {
		--bracketLevel;

		if(!bracketLevel) {
		    found = true;
		    break;
		}
	    }
	}
    }

    documenting.pop_back();
    std::cout << documenting << '\n';
}

void run() {
    bool running = true;
    std::string input = "";

    while(running) {
	std::cout << ">> ";
	std::cin >> input;

	if(input == ":q")
	    break;

	std::cout << stringifyVector(process(input));
    }
}

int main(int argc, char* argv[]) {
    std::cout << "Das ist die Sprache fuer die coolent Leute!\n";

    run();
    return 0;
}

#include <iostream>
#include <time.h>
#include <random>
#include <vector>
#include <algorithm>
#include "database.h"

int main(int argc, char* argv[]) {
    char familyFriendly;
    std::cout << "Familienfreundlich (y/n)?\n";
    std::cin >> familyFriendly;

    std::vector<int> already = {};

    while(true) {
        std::cout << "Wie viele Woerter?\n";
        int input;
        std::cin >> input;

        std::string output = "";

        srand(time(NULL));

        for(int i = input - 1; i > -1; i--) {
            if(familyFriendly != 'n') {
                int choice = random() % 45;

                while(std::find(already.begin(), already.end(), choice) != already.end())
                    choice = random() % 45;

                already.push_back(choice);

                output += i == 0 ? NORM_WORDS2[choice] : NORM_WORDS1[choice];
            } else {
                const int choice = random() % 52;

                already.push_back(choice);

                output += i == 0 ? ABTNORM_WORDS2[choice] : ABTNORM_WORDS1[choice];
            }
        }

        std::cout << output << '\n';
    }

    return 0;
}

#include <iostream>
#include "campaign.h"
#include "strings.h"
#include "reader.h"

int main(int argc, char** argv) {
    Campaign campaign = Reader::read("Test");
    campaign.play();

    return 0;
}

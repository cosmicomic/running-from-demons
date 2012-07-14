#include "location.h"
#include "exit.h"
#include <vector>
#include <string>
#include <cstring>
using namespace std;

Exit::Exit(int newDirection, Location *newLeadsTo) {
    direction = newDirection;
    leadsTo = newLeadsTo;
}

string Exit::getDirectionName() {
    return directionName;
}

void Exit::setDirectionName(string newDirectionName) {
    directionName = newDirectionName;
}

void Exit::setShortDirectionName(string newShortName) {
    shortDirectionName = newShortName;
}

string Exit::getShortDirectionName() {
    return shortDirectionName;
}

void Exit::setLeadsTo(Location *newLeadsTo) {
    leadsTo = newLeadsTo;
}

Location* Exit::getLeadsTo() {
    return leadsTo;
}

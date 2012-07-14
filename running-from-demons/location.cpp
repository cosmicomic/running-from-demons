#include "location.h"
#include "exit.h"
#include <vector>
#include <string>
#include <cstring>
using namespace std;

Location::Location(string newName, string newDescription) {
    name = newName;
    description = newDescription;
}

void Location::addExit(Exit *newExit) {
    exits.push_back(newExit);
}

string Location::getName() {
    return name;
}

string Location::getDescription() {
    return description;
}

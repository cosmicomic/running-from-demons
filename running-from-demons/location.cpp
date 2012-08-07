#include "location.h"
#include <vector>
#include <string>
#include <cstring>
using namespace std;

Location::Location(string newName, string newDescription) {
    name = newName;
    description = newDescription;
}

string Location::getName() {
    return name;
}

string Location::getDescription() {
    return description;
}

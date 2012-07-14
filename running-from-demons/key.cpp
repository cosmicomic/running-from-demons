#include "key.h"
using namespace std;

Key::Key (string newName, string newDescription, Location *newLocation) : Item(newName, newDescription, newLocation)
{
    name = newName;
    description = newDescription;
    location = newLocation;
}

bool Key::isFound() {
    return found;
}

bool Key::isValid() {
    return valid;
}

void Key::setFound(bool state) {
    found = state;
}

void Key::setValid(bool state) {
    valid = state;
}

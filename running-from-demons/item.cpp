#include "item.h"
using namespace std;

Item::Item (string newName, string newDescription, Location *newLocation) {
    name = newName;
    description = newDescription;
    location = newLocation;
}

string Item::getName() {
    return name;
}

string Item::getDescription() {
    return description;
}

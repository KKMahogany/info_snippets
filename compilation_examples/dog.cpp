#include "pet.h"
#include <iostream>

using namespace std;

string getPetType() {
    return "dog";
}

int PAT_COUNT = 0;
bool patPet(int times) {
    PAT_COUNT += times;
    cout << "You have pat the dog " << PAT_COUNT << " times.\n";
    return true;
}

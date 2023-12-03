#include "pet.h"
#include <iostream>

using namespace std;

string getPetType() {
    return "cat";
}

int PAT_COUNT = 0;
bool patPet(int times) {
    if(PAT_COUNT < 3) {
        PAT_COUNT += times;
        cout << "You pet the cat!\n";
        return true;
    } else {
        cout << "The cat runs under the couch and you cannot pet it.\n";
        return false;
    }
}

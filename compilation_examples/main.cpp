#include "pet.h"
#include <iostream>

using namespace std;

int main() {
    cout << "I have a pet! It is a: " << getPetType() << "\n";;
    string s;
    while(getline(std::cin, s)) {
        if(s == "pat") {
            bool success = patPet(1);
            if(!success) {
                cerr << "Failed to pat!\n";
            }
        } else {
            cout << "Sorry you can only pat\n";
        }
    }
}

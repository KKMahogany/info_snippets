// Cyclic dependency example
//
// 1. Preprocessing
// 2. Compilation (per-file)
// 3. Linking (multi-files)
#include <iostream>

// Forward declare function b
void b(int);

void a(int iteration) {
    std::cerr << "It's me, A\n";
    if(iteration == 10) {
        std::cerr << "Killing the program\n";
        exit(0);
    }
    b(iteration+1);
}

//void b(int iteration) {
//    std::cerr << "It's me, B\n";
//    a(iteration+1);
//}


int main() {
    a(0);
}

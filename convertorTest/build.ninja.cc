#include <iostream>
#include <cstdlib>
using namespace std;
int main() {
    cout << "Running: g++ -O3 -c hello.cc  -o hello.o" << endl;
    system("g++ -O3 -c hello.cc  -o hello.o");
    cout << "Running: g++ hello.o  -o hello" << endl;
    system("g++ hello.o  -o hello");
    return 0;
}

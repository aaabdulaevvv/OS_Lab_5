#include <unistd.h>
#include <iostream>

using namespace std;

int main() {
    std::cout << "Process ID: " << getpid() << std::endl;
    int x = 42;
    cout << "Address of x: " << &x << endl;
    cout << "Now x is equal to " << x << endl;
    sleep(30);
    x = 10;
    cout << "Now x is equal to " << x << endl;
    sleep(15);
    return 0;
}

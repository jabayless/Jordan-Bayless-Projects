#include <iostream>

using namespace std;

int main(int argc, char *argv){
    string myName = "jordan";
    reinterpret_cast<int>(myName);

    cout << myName;
    reinterpret_cast<string>(myName);
    cout << myName;

return 0;
}


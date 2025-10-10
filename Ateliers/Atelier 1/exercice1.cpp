#include <iostream>
using namespace std;

int main()
{
    char c = '\x01'; // It's a character how containe a hexadecimal number
    // char a = '\x0B';
    short int p = 10;

    cout << (int)c << endl;
    cout << p << endl;

    cout << "p+3= " << p + 3 << endl;             // type: short int
    cout << "c+1= " << c + 1 << endl;             // type: integer
    cout << "p+c = " << p + c << endl;            // type: integer
    cout << "3*p+5*c= " << 3 * p + 5 * c << endl; // type: integer
}
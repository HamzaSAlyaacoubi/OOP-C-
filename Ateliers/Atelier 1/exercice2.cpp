#include <iostream>
using namespace std;

int main()
{
    char c = '\x05';
    int n = 5;
    long p = 1000;
    float x = 1.25;
    double z = 5.5;

    cout << "n+c+p= " << n + c + p << endl;                             // type: Long; result:1010;
    cout << "2*x+c= " << 2 * x + c << endl;                             // type: Float; result:7.5;
    cout << "(char)n+c= " << (char)n + c << endl;                       // type: int; result:10;
    cout << "(float)z+n/2= " << (float)z + n / 2 << endl;               // type: Float; result:7.5 because n is an integer,so: n/2=2 (int);
    cout << "(float)z+(float)n/2= " << (float)z + (float)n / 2 << endl; // type: Float; result:8 because we convert n to float,so: n/2=2.5 (float);
}
#include <iostream>
using namespace std;

int main()
{
    int n = 5, p = 9;
    int q;
    float x;

    q = n < p; // n is less than p so q would be true which is 1
    cout << "q = n < p  --> " << q << endl;
    q = n == p; // n is not equal to p so q would be false which is 0
    cout << "q = n == p  --> " << q << endl;
    q = p % n + p > n; // q = 1
    cout << "q = p % n + p > n  --> " << q << endl;
    x = p / n; // x = 9 / 5 = 1 because p and n are integers
    cout << "x = p / n  --> " << x << endl;
    x = (float)p / n; // x = 9 / 5 = 1.8 because p would be float before the division
    cout << "x = (float)p / n  --> " << x << endl;
    x = (p + 0.5) / n; // x = 9.5 / 5 = 1.9 because p would be float after adding 0.5
    cout << "x = (p + 0.5) / n  --> " << x << endl;
    x = (int)(p + 0.5) / n; // x = 1 because of (int)x that transform 1.9 to 1
    cout << "x = (int)(p + 0.5) / n  --> " << x << endl;
    q = n * (p > n ? n : p); // q = 25 because p is greater than n,so it return n then n*n
    cout << "q = n * (p > n ? n : p)  --> " << q << endl;
    q = n * (p < n ? n : p); // q = 45 because p is greater than n,so it return p then n*p
    cout << "q = n * (p < n ? n : p)  --> " << q << endl;
}

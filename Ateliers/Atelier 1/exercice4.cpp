#include <iostream>
using namespace std;

int main()
{
    int i, j, n;

    i = 0;
    n = i++; // n = 0 & i = 1
    cout << "A : i = " << i << " n = " << n << "\n";

    i = 10;
    n = ++i; // n = 11 & i = 11
    cout << "B : i = " << i << " n = " << n << "\n";

    i = 20;
    j = 5;
    n = i++ * ++j; // n = 20 * 6 = 120 & i = 21 & j = 6
    cout << "C : i = " << i << " j = " << j << " n = " << n << "\n";

    i = 15;
    n = i += 3; // i = 15 + 3 = 18 then n = 18
    cout << "D : i = " << i << " n = " << n << "\n";

    i = 3;
    j = 5;
    n = i *= --j; // j = 4  then  i = 3 * 4 = 12  then  n = i = 12
    cout << "E : i = " << i << " j = " << j << " n = " << n << "\n";

    /*
    Note:
    In the incrementation we have before the operation --> ++i or --i
    and after the operation --> i++ or i--
    But others like *=, +=, -=, /= are always before the operation
    */

    // My other tests with /= operator:
    i = 6;
    j = 3;
    n = i /= j; // j = 3 then i = 6 / 3 = 2 then n = 2
    cout << "F : i = " << i << " j = " << j << " n = " << n << "\n";

    i = 6;
    j = 2;
    n = i /= ++j; // j = 3 then i = 6 / 3 = 2 then n = 2
    cout << "F : i = " << i << " j = " << j << " n = " << n << "\n";

    i = 6;
    j = 2;
    n = i /= j++; // j = 2 then i = 6 / 2 = 3 then n = 3 then j = 3
    cout << "F : i = " << i << " j = " << j << " n = " << n << "\n";
}
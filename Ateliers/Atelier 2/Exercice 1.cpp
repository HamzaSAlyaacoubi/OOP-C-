#include <iostream>
using namespace std;

/* || Methode 1 */
int x = 1;
void nombreDapelle()
{
    cout << "appel numero " << x << endl;
    x++;
}

/* || Methode 2 */
void nombreDapelle2()
{
    static int i = 1;
    cout << "appel numero " << i << endl;
    i++;
}



int main()
{

    nombreDapelle();
    nombreDapelle();
    nombreDapelle();
    nombreDapelle();
    cout << "___________________________" << endl;
    nombreDapelle2();
    nombreDapelle2();
    nombreDapelle2();
    nombreDapelle2();
}

/* 
Ecrire un programme C++ qui :
1. déclare un entier a;
2. déclare une référence vers cet entier ref_a;
3. déclare un pointeur vers cet entier p_a;
4. affiche les variables, leurs adresses, la valeur pointée 
*/

#include <iostream>
using namespace std;


int main() {

    int a = 100;

    int &ref_a = a;

    int *p_a = &a;

    cout << "Valeur de a : " << a << endl;
    cout << "Adresse de a : " << &a << endl;

    cout << "Valeur de ref_a : " << ref_a << endl; // même valeur de a 
    cout << "Adresse de ref_a : " << &ref_a << endl; // va etre identique à celle de a

    cout << "Valeur de p_a : " << p_a << endl; // adresse de a
    cout << "Valeur pointee *p_a: " << *p_a << endl; // valeur de a
    cout << "Adresse de p_a : " << &p_a << endl; // adresse du pointeur lui-même
}
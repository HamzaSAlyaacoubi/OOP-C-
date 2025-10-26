/*
Écrire une fonction nommée incrementer() permettant d’incrémenter la valeur d’une variable passée en paramètre et une fonction nommée permuter() permettant d’échanger les contenus de 2 variables de type int fournies en argument :
1. en transmettant l’adresse des variables concernées (seule méthode utilisable en C) ;
2. en utilisant la transmission par référence.
Dans les deux cas, écrire un programme (main) qui teste les deux fonctions
*/

#include <iostream>
using namespace std;


void incrementer(int *num){
    (*num)++;
}

void permuter(int *num1, int *num2){
    int cache = *num1;

    *num1 = *num2;
    *num2 = cache;

}

void incrementer2(int &num){
    num++;
}

void permuter2(int &num1, int &num2){
    int cache = num1;

    num1 = num2;
    num2 = cache;

}


int main() {


    int nombre1 = 10;
    int nombre2 = 20;

    cout << "Avant incrementer: nombre1 = " << nombre1 << endl;
    incrementer(&nombre1);
    cout << "Apres incrementer: nombre1 = " << nombre1 << endl;

    permuter(&nombre1, &nombre2);
    cout << "Le nombre 1 est : " << nombre1 << endl;
    cout << "Le nombre 2 est : " << nombre2 << endl;

    int x = 10;
    int y = 20;

    cout << "Avant incrementer: x = " << x << endl;
    incrementer2(x);
    cout << "Apres incrementer: x = " << x << endl;

    cout << "Avant permutation: x = " << x << ", y = " << y << endl;
    permuter2(x, y); 
    cout << "Apres permutation: x = " << x << ", y = " << y << endl;

    return 0;
}
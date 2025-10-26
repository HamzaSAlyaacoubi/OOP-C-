/*
Écrire une fonction récursive en C++ qui affiche toutes les permutations possibles d’une chaîne de
caractères donnée. Aucune bibliothèque spéciale ne doit être utilisée !!
*/

#include <iostream>
using namespace std;

void permuter(char &a, char &b) {
    char temp = a;
    a = b;
    b = temp;
}

void permutations(string &chaine, int debut, int fin) {
    if (debut == fin) {
        cout << chaine << endl; // cas de base : une permutation complète
    } else {
        for (int i = debut; i <= fin; i++) {
            // échanger le caractère courant avec celui du début
            permuter(chaine[debut], chaine[i]);

            // appel récursif sur le reste de la chaîne
            permutations(chaine, debut + 1, fin);

            // remettre la chaîne dans l’état initial (backtracking)
            permuter(chaine[debut], chaine[i]);
        }
    }
}

int main(){

    string mot;
    cout << "Entrez une chaine : ";
    cin >> mot;

    cout << "\nLes permutations sont :\n";
    permutations(mot, 0, mot.length() - 1);

    return 0;

}


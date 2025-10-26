/*
Écrire un programme allouant dynamiquement un emplacement pour un tableau d’entiers, dont la
taille est fournie en donnée.
1. Utiliser ce tableau pour y placer des nombres entiers lus également en donnée.
2. Créer ensuite dynamiquement un nouveau tableau destiné à recevoir les carrés des nombres
contenus dans le premier.
3. Supprimer le premier tableau, afficher les valeurs du second et supprimer le tout.
*/

#include <iostream>
using namespace std;


int main(){
    

    int n;
    cout << "Entrer la taille du tableau: ";
    cin >> n;

    int *tab = new int[n];
    int *p = tab;

    cout << "Entrer des nombres entiers dans le tableau:" << endl;
    for (p = tab; p < tab + n; p++){
        cin >> *p;
    }

    int *carreTab = new int[n];
    int *ptr = carreTab;
    
    p = tab;
    for(ptr = carreTab; ptr < carreTab + n; ptr++){
        *ptr = (*p)*(*p);
        p++;
    }

    delete[] tab;
    tab = nullptr;
    p = nullptr;


    int i = 1;
    cout << "Les carres sont : ";
    for (ptr = carreTab; ptr < carreTab + n; ptr++){
        cout << "Nombre " << i << " : " << *ptr << endl;
        i++;
    }

    delete[] carreTab;
    carreTab = nullptr;
    ptr = nullptr;

    return 0;



}
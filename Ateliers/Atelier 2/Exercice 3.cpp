/*
Écrire, de deux façons différentes, un programme qui lit 10 nombres entiers dans un tableau avant d’en rechercher le plus grand et le plus petit :
a. en utilisant uniquement le « formalisme tableau » ;
b. en utilisant le « formalisme pointeur », à chaque fois que cela est possible.
*/

#include <iostream>
using namespace std;

void trouverLePetit(int tab[]){
    int min = tab[0];
    for(int i=0; i<10; i++){
        if(tab[i] < min) min = tab[i];
    }
    cout << "Le plus petit nombre est :" << min << endl;
}

void trouverLeGrand(int tab[]){
    int max = tab[0];
    for(int i=0; i<10; i++){
        if(tab[i] > max) max = tab[i];
    }
    cout << "Le plus grand nombre est :" << max << endl;
}


int main(){
    /* || Programme 1*/
     int tab[10];

    for(int i=0; i<10; i++){
        cout << "Entrez le nombre "<< i+1 <<": ";
        cin >> tab[i];
    }

    /*
    
    trouverLePetit(tab);
    trouverLeGrand(tab); 

    */
    
    // ou //

    int min = tab[0];
    int max = tab[0];

    for (int i = 1; i < 10; i++) {
        if (tab[i] < min)
            min = tab[i];
        if (tab[i] > max)
            max = tab[i];
    }

    cout << "Le plus petit = " << min << endl;
    cout << "Le plus grand = " << max << endl;
    
    

    /* || Pragramme 2*/
    int arr[10];
    int *p = arr;
    
    
    for(int i=0; i<10; i++){
        cout << "Entrez le nombre "<< i +1 <<": ";
        cin >> *p;
        p++;
    }

    int *pmin = arr;
    int *pmax = arr;

    for (p = arr + 1; p < arr + 10; p++) {
        if (*p < *pmin)
            pmin = p;
        if (*p > *pmax)
            pmax = p;
    }

    cout << "Le plus petit = " << *pmin << endl;
    cout << "Le plus grand = " << *pmax << endl;


    return 0;

}

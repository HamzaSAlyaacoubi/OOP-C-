/*
Une pile est un ensemble dynamique d’éléments où le retrait se fait d’une façon particulière.
En effet, lorsque l’on désire enlever un élément de l’ensemble, ce sera toujours le dernier inséré
qui sera retiré. Un objet pile doit répondre aux fonctions suivantes :
• Initialiser une pile (constructeur(s))
• Empiler un élément sur la pile (push)
• Dépiler un élément de la pile (pop)
Pour simplifier, nous allons supposer que les éléments à empiler sont de type int.
Le programme principale main comprend la définition d'une classe pile et un programme de
test qui crée deux piles p1 et p2, empile dessus des valeurs entières et les dépiler pour vérifier
les opérations push et pop.
*/

#include <iostream>
using namespace std;

class Pile
{
private:
    int *elements; // Tableau dynamique pour stocker les éléments
    int tailleMax; // Taille maximale de la pile
    int sommet;    // Indice du sommet de la pile

public:
    // Constructeur avec taille maximale
    Pile(int taille = 10)
    {
        tailleMax = taille;
        elements = new int[tailleMax];
        sommet = -1;
        cout << "Pile initialisée avec une taille de " << tailleMax << endl;
    }

    // Destructeur pour libérer la mémoire
    ~Pile()
    {
        delete[] elements;
    }

    // Empiler un élément (push)
    void push(int valeur)
    {
        if (sommet == tailleMax - 1)
        {
            cout << "Erreur : pile pleine, impossible d'empiler " << valeur << endl;
            return;
        }
        elements[++sommet] = valeur;
        cout << valeur << " empilé dans la pile." << endl;
    }

    // Dépiler un élément (pop)
    int pop()
    {
        if (sommet == -1)
        {
            cout << "Erreur : pile vide, rien à dépiler." << endl;
            return -1; // ou une autre valeur spéciale
        }
        int val = elements[sommet--];
        cout << val << " dépilé de la pile." << endl;
        return val;
    }

    // Afficher la pile (pour test)
    void afficher() const
    {
        if (sommet == -1)
        {
            cout << "Pile vide." << endl;
            return;
        }
        cout << "Contenu de la pile : ";
        for (int i = 0; i <= sommet; i++)
        {
            cout << elements[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    // Création de deux piles
    Pile p1(5);
    Pile p2(3);

    // Empilement sur p1
    p1.push(10);
    p1.push(20);
    p1.push(30);
    p1.afficher();

    // Dépilement sur p1
    p1.pop();
    p1.afficher();

    // Empilement sur p2
    p2.push(100);
    p2.push(200);
    p2.afficher();

    // Dépilement sur p2
    p2.pop();
    p2.pop();
    p2.pop(); // test pile vide

    return 0;
}

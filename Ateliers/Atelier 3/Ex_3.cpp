#include <iostream>
using namespace std;

// Structure représentant un élément de la liste
struct Element
{
    int valeur;       // donnée contenue dans le nœud
    Element *suivant; // pointeur vers l’élément suivant
};

// Classe Liste simplement chaînée
class Liste
{
private:
    Element *premier; // pointeur sur le premier élément de la liste

public:
    // Constructeur
    Liste()
    {
        premier = nullptr;
        cout << "Liste créée (vide)." << endl;
    }

    // Destructeur — libère toute la mémoire
    ~Liste()
    {
        Element *courant = premier;
        while (courant != nullptr)
        {
            Element *temp = courant;
            courant = courant->suivant;
            delete temp;
        }
        cout << "Liste détruite et mémoire libérée." << endl;
    }

    // Ajouter un élément au début de la liste
    void ajouterDebut(int val)
    {
        Element *nouveau = new Element;
        nouveau->valeur = val;
        nouveau->suivant = premier; // l'ancien premier devient le suivant
        premier = nouveau;          // le nouveau devient le premier
        cout << val << " ajouté au début de la liste." << endl;
    }

    // Supprimer un élément au début de la liste
    void supprimerDebut()
    {
        if (premier == nullptr)
        {
            cout << "La liste est vide, rien à supprimer." << endl;
            return;
        }
        Element *temp = premier;
        premier = premier->suivant; // avancer le pointeur
        cout << "Élément " << temp->valeur << " supprimé du début." << endl;
        delete temp; // libération mémoire
    }

    // Afficher tout le contenu de la liste
    void afficher() const
    {
        if (premier == nullptr)
        {
            cout << "La liste est vide." << endl;
            return;
        }

        cout << "Contenu de la liste : ";
        Element *courant = premier;
        while (courant != nullptr)
        {
            cout << courant->valeur << " ";
            courant = courant->suivant;
        }
        cout << endl;
    }
};

// === Programme principal ===
int main()
{
    Liste maListe;

    maListe.ajouterDebut(10);
    maListe.ajouterDebut(20);
    maListe.ajouterDebut(30);

    maListe.afficher();

    maListe.supprimerDebut();
    maListe.afficher();

    maListe.supprimerDebut();
    maListe.supprimerDebut();
    maListe.supprimerDebut(); // test de suppression sur liste vide

    return 0;
}

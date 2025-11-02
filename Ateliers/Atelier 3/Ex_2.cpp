#include <iostream>
#include <cstring> // pour memcpy, memset
using namespace std;

class Fichier
{
private:
    char *P;      // pointeur vers la zone mémoire (fichier en mémoire)
    int longueur; // longueur du fichier en octets

public:
    // Constructeur
    Fichier()
    {
        P = nullptr;
        longueur = 0;
        cout << "Constructeur : objet Fichier créé." << endl;
    }

    // Destructeur
    ~Fichier()
    {
        if (P != nullptr)
        {
            delete[] P; // libération mémoire
            cout << "Destructeur : mémoire libérée." << endl;
        }
        else
        {
            cout << "Destructeur : aucune mémoire à libérer." << endl;
        }
    }

    // Méthode Creation : allouer une zone mémoire
    void Creation(int taille)
    {
        if (P != nullptr)
        {
            cout << "Mémoire déjà allouée, on la libère d'abord..." << endl;
            delete[] P;
        }

        P = new char[taille]; // allocation dynamique
        longueur = taille;

        if (P)
            cout << "Espace mémoire de " << taille << " octets alloué." << endl;
        else
            cout << "Erreur d'allocation mémoire !" << endl;
    }

    // Méthode Remplit : remplir arbitrairement la zone mémoire
    void Remplit()
    {
        if (P == nullptr)
        {
            cout << "Erreur : aucune zone mémoire allouée !" << endl;
            return;
        }

        // On remplit avec des lettres (A, B, C, ...)
        for (int i = 0; i < longueur; ++i)
            P[i] = 'A' + (i % 26);

        cout << "Zone mémoire remplie arbitrairement." << endl;
    }

    // Méthode Affiche : afficher le contenu mémoire
    void Affiche() const
    {
        if (P == nullptr)
        {
            cout << "Erreur : aucune donnée à afficher !" << endl;
            return;
        }

        cout << "Contenu du fichier (" << longueur << " octets) : ";
        for (int i = 0; i < longueur; ++i)
            cout << P[i];
        cout << endl;
    }
};

// Programme principal
int main()
{
    cout << "=== Début du programme ===" << endl;

    // Instanciation dynamique d’un objet Fichier
    Fichier *f = new Fichier();

    // Appel des méthodes
    f->Creation(20);
    f->Remplit();
    f->Affiche();

    // Suppression de l’objet et appel du destructeur
    delete f;

    cout << "=== Fin du programme ===" << endl;
    return 0;
}

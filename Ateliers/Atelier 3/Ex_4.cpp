#include <iostream>
#include <string>
using namespace std;

//
// === CLASSE CLIENT ===
//
class Client
{
private:
    int id;
    string nom;
    string prenom;

public:
    // Constructeur par défaut (client vide)
    Client() : id(0), nom(""), prenom("")
    {
        cout << "Client vide créé." << endl;
    }

    // Constructeur avec paramètres
    Client(int id, string nom, string prenom) : id(id), nom(nom), prenom(prenom)
    {
        cout << "Client créé : " << prenom << " " << nom << endl;
    }

    // Constructeur de copie
    Client(const Client &autre)
    {
        id = autre.id;
        nom = autre.nom;
        prenom = autre.prenom;
        cout << "Client copié : " << prenom << " " << nom << endl;
    }

    // Destructeur
    ~Client()
    {
        cout << "Client " << prenom << " " << nom << " détruit." << endl;
    }

    // Méthode d’affichage
    void afficher() const
    {
        cout << "Client [ID=" << id << ", Nom=" << nom << ", Prénom=" << prenom << "]" << endl;
    }
};

//
// === CLASSE COMPTE ===
//
class Compte
{
private:
    int numero;
    float solde;
    Client *client;          // pointeur vers un client
    static int totalComptes; // variable statique commune à tous les comptes

public:
    // Constructeur par défaut
    Compte() : numero(0), solde(0.0), client(nullptr)
    {
        totalComptes++;
        cout << "Compte vide créé." << endl;
    }

    // Constructeur avec paramètres
    Compte(int num, float s, const Client &c) : numero(num), solde(s)
    {
        client = new Client(c); // copie du client (copie profonde)
        totalComptes++;
        cout << "Compte créé pour : ";
        client->afficher();
    }

    // Constructeur de copie
    Compte(const Compte &autre)
    {
        numero = autre.numero;
        solde = autre.solde;
        // copie profonde du client
        if (autre.client != nullptr)
            client = new Client(*autre.client);
        else
            client = nullptr;
        totalComptes++;
        cout << "Compte copié (numéro " << numero << ")." << endl;
    }

    // Destructeur
    ~Compte()
    {
        if (client != nullptr)
        {
            delete client;
            client = nullptr;
        }
        totalComptes--;
        cout << "Compte numéro " << numero << " détruit." << endl;
    }

    // Méthode d'affichage
    void afficher() const
    {
        cout << "Compte [Numéro=" << numero << ", Solde=" << solde << "]" << endl;
        if (client)
            client->afficher();
        else
            cout << "Aucun client associé." << endl;
    }

    // Méthode statique : affiche le nombre total de comptes
    static void afficherTotalComptes()
    {
        cout << "Nombre total de comptes : " << totalComptes << endl;
    }

    // Accesseur pour modifier le solde
    void setSolde(float nouveauSolde) { solde = nouveauSolde; }
    float getSolde() const { return solde; }
};

// Initialisation du membre statique
int Compte::totalComptes = 0;

//
// === FONCTION UTILITAIRE ===
//

// On la déclare inline pour optimiser les petits calculs très fréquents
inline float calculInteret(float solde, float taux)
{
    return solde + solde * taux / 100.0;
}

//
// === PROGRAMME PRINCIPAL ===
//
int main()
{
    cout << "=== DÉBUT DU PROGRAMME ===" << endl;

    // Création de clients
    Client c1(1, "Dupont", "Jean");
    Client c2(2, "Durand", "Marie");

    // Création de comptes
    Compte compte1(1001, 2500.0, c1);
    Compte compte2(1002, 4000.0, c2);

    Compte::afficherTotalComptes();

    // Copie d’un compte
    Compte compte3 = compte1;
    Compte::afficherTotalComptes();

    // Affichage des comptes
    cout << "\n--- Informations comptes ---" << endl;
    compte1.afficher();
    compte2.afficher();
    compte3.afficher();

    // Application d’intérêts
    float nouveauSolde = calculInteret(compte1.getSolde(), 5.0);
    compte1.setSolde(nouveauSolde);
    cout << "\nAprès application des intérêts : " << endl;
    compte1.afficher();

    // Suppression d’un compte (test du destructeur)
    cout << "\nSuppression de compte2..." << endl;
    {
        Compte temp(2001, 1000, c1);
        Compte::afficherTotalComptes();
    } // temp sort du scope, son destructeur est appelé ici

    Compte::afficherTotalComptes();

    cout << "\n=== FIN DU PROGRAMME ===" << endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Client
{
private:
    string nom;
    string CIN;
    string idClient;

public:
    Client(string n, string c, string id)
        : nom(n), CIN(c), idClient(id) {}

    string getNom() const { return nom; }
    string getCIN() const { return CIN; }
    string getIdClient() const { return idClient; }

    void afficherInfos() const
    {
        cout << "Client : " << nom << " | CIN : " << CIN
             << " | Identifiant : " << idClient << endl;
    }
};

class AgentBancaire;
class Banque;

class CompteBancaire
{
private:
    string numeroCompte;
    double solde;
    string codeSecret;
    const Client *proprietaire;

public:
    CompteBancaire(string num, double s, string code, const Client *c)
        : numeroCompte(num), solde(s), codeSecret(code), proprietaire(c) {}

    void deposer(double montant)
    {
        solde += montant;
        cout << "Depot de " << montant << " DH effectué sur le compte " << numeroCompte << endl;
    }

    void retirer(double montant)
    {
        if (montant <= solde)
        {
            solde -= montant;
            cout << "Retrait de " << montant << " DH effectué du compte " << numeroCompte << endl;
        }
        else
        {
            cout << "Solde insuffisant sur le compte " << numeroCompte << endl;
        }
    }

    void afficherInfosPubliques() const
    {
        cout << "Compte N°" << numeroCompte
             << " | Proprietaire : " << proprietaire->getNom()
             << " | Solde : " << solde << " DH" << endl;
    }

private:
    // Accès confidentiel uniquement pour certaines classes
    string getCodeSecret() const { return codeSecret; }

    // Seules ces classes peuvent accéder aux données privées
    friend class AgentBancaire;
    friend class Banque;
};

class AgentBancaire
{
private:
    string nom;
    string idAgent;

public:
    AgentBancaire(string n, string id)
        : nom(n), idAgent(id) {}

    void consulterCodeSecret(const CompteBancaire &compte) const
    {
        cout << "Agent " << nom << " consulte le code secret du compte "
             << compte.numeroCompte << ": " << compte.codeSecret << endl;
    }

    void transfert(CompteBancaire &source, CompteBancaire &destination, double montant) const
    {
        if (montant <= source.solde)
        {
            source.solde -= montant;
            destination.solde += montant;
            cout << "Agent " << nom << " a effectue un transfert de "
                 << montant << " DH du compte " << source.numeroCompte
                 << " vers " << destination.numeroCompte << endl;
        }
        else
        {
            cout << "Transfert impossible : solde insuffisant sur le compte source." << endl;
        }
    }
};

class Banque
{
private:
    string nom;
    vector<Client> clients;
    vector<CompteBancaire *> comptes;

public:
    Banque(string n) : nom(n) {}

    void ajouterClient(const Client &c)
    {
        clients.push_back(c);
    }

    void ajouterCompte(CompteBancaire *c)
    {
        comptes.push_back(c);
    }

    // Audit interne (accès complet)
    void rapportAudit() const
    {
        cout << "\n========== RAPPORT D’AUDIT (" << nom << ") ==========" << endl;
        for (auto c : comptes)
        {
            cout << "Compte : " << c->numeroCompte
                 << " | Client : " << c->proprietaire->getNom()
                 << " | Solde : " << c->solde
                 << " | Code secret : " << c->codeSecret << endl;
        }
        cout << "======================================================" << endl;
    }

    void afficherTousLesComptes() const
    {
        cout << "\n--- Liste des comptes ---" << endl;
        for (auto c : comptes)
            c->afficherInfosPubliques();
    }
};

int main()
{
    Client c1("Ahmed Karim", "AA12345", "C001");
    Client c2("Sara Benali", "BB67890", "C002");

    // Création de comptes
    CompteBancaire compte1("1001", 5000.0, "1234", &c1);
    CompteBancaire compte2("1002", 3000.0, "5678", &c2);

    // Création de la banque
    Banque banque("Banque Centrale");
    banque.ajouterClient(c1);
    banque.ajouterClient(c2);
    banque.ajouterCompte(&compte1);
    banque.ajouterCompte(&compte2);

    // Création d’un agent
    AgentBancaire agent("Youssef", "A001");

    // Opérations
    compte1.deposer(1000);
    compte2.retirer(500);
    agent.transfert(compte1, compte2, 1500);

    // L’agent consulte un code secret (autorisé)
    agent.consulterCodeSecret(compte2);

    // Audit interne
    banque.afficherTousLesComptes();
    banque.rapportAudit();

    return 0;
}
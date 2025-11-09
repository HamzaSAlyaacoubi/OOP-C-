#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Ressource
{
protected:
    string id;
    string titre;
    string auteur;
    int annee;
    bool disp;

public:
    Ressource(string i, string t, string a, int an, bool d = true) : id(i), titre(t), auteur(a), annee(an), disp(d) {}

    string getID() { return id; }
    string getTitre() { return titre; }
    string getAuteur() { return auteur; }
    int getAnnee() { return annee; }

    virtual void afficherInfo()
    {
        cout << "--------------infos----------------" << endl;
        cout << "ID : " << id << endl;
        cout << "LE TITRE : " << titre << endl;
        cout << "L'AUTEUR : " << auteur << endl;
        cout << "ANNEE : " << annee << endl;
    }

    virtual void telecharger()
    {
        cout << "Disponible à telecharger !!" << endl;
    }

    virtual ~Ressource() {}
};
class Telechargeable
{
private:
    bool telechargeable;

public:
    Telechargeable() : telechargeable(true) {}

    virtual void telecharger()
    {
        cout << "Telechargement en cours..." << endl;
    }

    void afficherMessage()
    {
        cout << "Ressource disponible pour le telechargement !" << endl;
    }
};

class Livre : public Ressource, public Telechargeable
{
private:
    string ISBN;

public:
    Livre(string i, string t, string a, int an, string IS, bool d = true) : Ressource(i, t, a, an, d)
    {
        ISBN = IS;
    }

    void afficherInfo() override
    {
        cout << "--------------infos----------------" << endl;
        cout << "ID : " << id << endl;
        cout << "LE TITRE : " << titre << endl;
        cout << "L'AUTEUR : " << auteur << endl;
        cout << "ANNEE : " << annee << endl;
        cout << "ISBN : " << ISBN << endl;
    }

    void telecharger() override
    {
        cout << "Telechargement du livre \"" << titre << "\"..." << endl;
    }
};

class Magazine : public Ressource, public Telechargeable
{
private:
    string sujet;

public:
    Magazine(string i, string t, string a, int an, string s, bool d = true) : Ressource(i, t, a, an, d)
    {
        sujet = s;
    }

    void afficherInfo() override
    {
        cout << "--------------infos----------------" << endl;
        cout << "ID : " << id << endl;
        cout << "LE TITRE : " << titre << endl;
        cout << "L'AUTEUR : " << auteur << endl;
        cout << "ANNEE : " << annee << endl;
        cout << "SUJET : " << sujet << endl;
    }

    void telecharger() override
    {
        cout << "Telechargement du magazine \"" << titre << "\"..." << endl;
    }
};

class Video : public Ressource, public Telechargeable
{
private:
    int duree;

public:
    Video(string i, string t, string a, int an, int s, bool d = true) : Ressource(i, t, a, an, d)
    {
        duree = s;
    }

    void afficherInfo() override
    {
        cout << "--------------infos----------------" << endl;
        cout << "ID : " << id << endl;
        cout << "LE TITRE : " << titre << endl;
        cout << "L'AUTEUR : " << auteur << endl;
        cout << "ANNEE : " << annee << endl;
        cout << "DUREE : " << duree << endl;
    }

    void telecharger() override
    {
        cout << "Telechargement du video \"" << titre << "\"..." << endl;
    }
};

class Mediatheque
{
private:
    string nom;
    vector<Ressource *> ressource;

public:
    Mediatheque(string n) : nom(n) {}

    void ajouter(Ressource *r)
    {
        ressource.push_back(r);
    }

    void afficherToutes()
    {
        for (auto r : ressource)
            r->afficherInfo();
    }
    void rechercher(string titre)
    {
        for (Ressource *&a : ressource)
        {
            if (titre == a->getTitre())
            {
                a->afficherInfo();
            }
        }
    }
    // void AfficherID(string ID){
    //     for(Ressource* &a : ressource){
    //         if(ID == a->getID()){
    //             a->afficherInfo();
    //         }
    //     }
    // }

    void rechercher(int annee)
    {
        for (Ressource *&a : ressource)
        {
            if (annee == a->getAnnee())
            {
                a->afficherInfo();
            }
        }
    }

    void rechercher(int annee, string auteur)
    {
        for (Ressource *&a : ressource)
        {
            if (annee == a->getAnnee())
            {
                if (auteur == a->getAuteur())
                {
                    a->afficherInfo();
                }
            }
        }
    }
};

int main()
{
    Mediatheque m("Mediatheque Centrale");

    Livre l1("1", "Les Misérables", "Victor Hugo", 1862, "ISBN1234");
    Magazine m1("2", "Science & Vie", "Rédaction S&V", 2023, "Science");
    Video v1("3", "C++ Tutorial", "John Doe", 2024, 120);

    m.ajouter(&l1);
    m.ajouter(&m1);
    m.ajouter(&v1);

    cout << "=== Affichage complet ===" << endl;
    m.afficherToutes();

    cout << "\n=== Recherche par titre ===" << endl;
    m.rechercher("Science & Vie");

    cout << "\n=== Test telechargement ===" << endl;
    l1.telecharger();
    v1.telecharger();

    return 0;
}
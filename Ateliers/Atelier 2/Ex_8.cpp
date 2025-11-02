#include <iostream>
#include <string>
using namespace std;

class Voiture
{
private:
    string marque;
    string modele;
    int annee;
    float kilometrage;
    float vitesse;

public:
    Voiture()
    {
        marque = "Inconnue";
        modele = "Inconnu";
        annee = 0;
        kilometrage = 0.0;
        vitesse = 0.0;
        cout << "Constructeur par defaut appele." << endl;
    }

    /* Voiture(string marque, string modele, int annee, float kilometrage, float vitesse){
        this->marque = marque;
        this->modele = modele;
        this->annee = annee;
        this->kilometrage = kilometrage;
        this->vitesse = vitesse;
        cout << "Constructeur avec parametres appele." << endl;

    }; */

    /* Voiture(string marque, string modele, int annee, float kilometrage, float vitesse)
        :marque(marque), modele(modele), annee(annee), kilometrage(kilometrage), vitesse(vitesse){
        cout << "Constructeur avec parametres appele." << endl;

    }; */

    Voiture(string mar, string mod, int ann, float kil, float vit)
    {
        marque = mar;
        modele = mod;
        annee = ann;
        kilometrage = kil;
        vitesse = vit;
        cout << "Constructeur avec parametres appele." << endl;
    };

    void accelerer(float valeur)
    {
        vitesse += valeur;
    }

    void freiner(float valeur)
    {
        if (vitesse - valeur >= 0)
            vitesse -= valeur;
        else if (vitesse - valeur < 0)
            vitesse = 0;
    }

    void afficherInfo()
    {
        cout << "La marque : " << marque << endl;
        cout << "Le modele : " << modele << endl;
        cout << "L'annee : " << annee << endl;
        cout << "Le kilometrage : " << kilometrage << endl;
        cout << "La vitesse : " << vitesse << endl;
    }

    void avancer(float distance)
    {
        // check if distance is positive
        if (distance > 0)
            kilometrage += distance;
        else
            cout << "La distance doit etre superieur a 0" << endl;
    }

    ~Voiture()
    {
        cout << "La voiture est detruite avec succes";
    }
};

int main()
{

    Voiture maVoiture = Voiture("skoda", "A7", 2019, 30000, 120);

    maVoiture.afficherInfo();
    maVoiture.accelerer(30.0);

    maVoiture.afficherInfo();
    maVoiture.freiner(20);
    maVoiture.afficherInfo();
    maVoiture.freiner(160);
    maVoiture.afficherInfo();
    maVoiture.avancer(2000);
    maVoiture.afficherInfo();

    Voiture saVoiture;
    cout << "--------------------------------------" << endl;

    saVoiture.afficherInfo();

    return 0;
}
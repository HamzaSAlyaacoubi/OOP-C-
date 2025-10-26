#include <iostream>
#include <string>
using namespace std;

class Voiture {
private:
    // 🔹 Attributs
    string marque;
    string modele;
    int annee;
    float kilometrage;
    float vitesse;

public:
    // 🔹 Constructeur par défaut
    Voiture() {
        marque = "Inconnue";
        modele = "Inconnu";
        annee = 0;
        kilometrage = 0.0;
        vitesse = 0.0;
        cout << "Constructeur par defaut appele." << endl;
    }

    // 🔹 Constructeur avec paramètres
    Voiture(string m, string mod, int a, float km, float v) {
        marque = m;
        modele = mod;
        annee = a;
        kilometrage = km;
        vitesse = v;
        cout << "Constructeur avec parametres appele." << endl;
    }

    // 🔹 Méthode pour accélérer
    void accelerer(float valeur) {
        vitesse += valeur;
        cout << "La voiture accelere de " << valeur << " km/h. Vitesse actuelle : " << vitesse << " km/h" << endl;
    }

    // 🔹 Méthode pour freiner
    void freiner(float valeur) {
        vitesse -= valeur;
        if (vitesse < 0)
            vitesse = 0;
        cout << "La voiture freine de " << valeur << " km/h. Vitesse actuelle : " << vitesse << " km/h" << endl;
    }

    // 🔹 Méthode pour avancer
    void avancer(float distance) {
        if (distance > 0) {
            kilometrage += distance;
            cout << "La voiture avance de " << distance << " km. Kilometrage total : " << kilometrage << " km" << endl;
        } else {
            cout << "Distance invalide !" << endl;
        }
    }

    // 🔹 Méthode pour afficher les infos
    void afficherInfo() {
        cout << "\n===== Informations sur la voiture =====" << endl;
        cout << "Marque : " << marque << endl;
        cout << "Modele : " << modele << endl;
        cout << "Annee : " << annee << endl;
        cout << "Kilometrage : " << kilometrage << " km" << endl;
        cout << "Vitesse : " << vitesse << " km/h" << endl;
        cout << "=======================================" << endl;
    }

    // 🔹 Destructeur
    ~Voiture() {
        cout << "La voiture " << marque << " " << modele << " est detruite." << endl;
    }
};

// 🔹 Programme principal pour tester la classe
int main() {
    // Création d’une voiture avec le constructeur par défaut
    Voiture v1;
    v1.afficherInfo();

    // Création d’une voiture avec le constructeur paramétré
    Voiture v2("Toyota", "Corolla", 2020, 35000.5, 80);
    v2.afficherInfo();

    // Tester les méthodes
    v2.accelerer(20);
    v2.avancer(150.75);
    v2.freiner(50);
    v2.afficherInfo();

    return 0;
}

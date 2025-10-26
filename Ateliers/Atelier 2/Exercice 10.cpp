#include <iostream>
using namespace std;

class Complexe {
private:
    float reel;
    float imag;

public:
    // 🔹 Constructeur avec valeurs par défaut
    Complexe(float r = 0, float i = 0) {
        reel = r;
        imag = i;
    }

    // 🔹 Lecture des valeurs
    void saisir() {
        cout << "Entrez la partie reelle : ";
        cin >> reel;
        cout << "Entrez la partie imaginaire : ";
        cin >> imag;
    }

    // 🔹 Affichage
    void afficher() const {
        if (imag >= 0)
            cout << reel << " + " << imag << "i";
        else
            cout << reel << " - " << -imag << "i";
    }

    // 🔹 Addition
    Complexe addition(const Complexe &c) const {
        return Complexe(reel + c.reel, imag + c.imag);
    }

    // 🔹 Soustraction
    Complexe soustraction(const Complexe &c) const {
        return Complexe(reel - c.reel, imag - c.imag);
    }

    // 🔹 Multiplication
    Complexe multiplication(const Complexe &c) const {
        float r = reel * c.reel - imag * c.imag;
        float i = reel * c.imag + imag * c.reel;
        return Complexe(r, i);
    }

    // 🔹 Division
    Complexe division(const Complexe &c) const {
        float denominateur = c.reel * c.reel + c.imag * c.imag;
        if (denominateur == 0) {
            cout << "Erreur : division par zero !" << endl;
            return Complexe(0, 0);
        }
        float r = (reel * c.reel + imag * c.imag) / denominateur;
        float i = (imag * c.reel - reel * c.imag) / denominateur;
        return Complexe(r, i);
    }

    // 🔹 Egalité
    bool egal(const Complexe &c) const {
        return (reel == c.reel && imag == c.imag);
    }
};

int main() {
    Complexe c1, c2, resultat;
    int choix;

    cout << "=== Programme sur les nombres complexes ===" << endl;

    cout << "\nSaisir le premier nombre complexe :" << endl;
    c1.saisir();

    cout << "\nSaisir le deuxieme nombre complexe :" << endl;
    c2.saisir();

    do {
        cout << "\n========== MENU ==========" << endl;
        cout << "1. Addition" << endl;
        cout << "2. Soustraction" << endl;
        cout << "3. Multiplication" << endl;
        cout << "4. Division" << endl;
        cout << "5. Test d'egalite" << endl;
        cout << "0. Quitter" << endl;
        cout << "==========================" << endl;
        cout << "Votre choix : ";
        cin >> choix;

        switch (choix) {
        case 1:
            resultat = c1.addition(c2);
            cout << "\nResultat de l'addition : ";
            resultat.afficher();
            cout << endl;
            break;

        case 2:
            resultat = c1.soustraction(c2);
            cout << "\nResultat de la soustraction : ";
            resultat.afficher();
            cout << endl;
            break;

        case 3:
            resultat = c1.multiplication(c2);
            cout << "\nResultat de la multiplication : ";
            resultat.afficher();
            cout << endl;
            break;

        case 4:
            resultat = c1.division(c2);
            cout << "\nResultat de la division : ";
            resultat.afficher();
            cout << endl;
            break;

        case 5:
            if (c1.egal(c2))
                cout << "\nLes deux nombres complexes sont egaux." << endl;
            else
                cout << "\nLes deux nombres complexes sont differents." << endl;
            break;

        case 0:
            cout << "\nFin du programme." << endl;
            break;

        default:
            cout << "Choix invalide !" << endl;
        }
    } while (choix != 0);

    return 0;
}

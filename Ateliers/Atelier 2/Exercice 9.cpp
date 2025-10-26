#include <iostream>
#include <cmath> // pour sqrt()
using namespace std;

class Vecteur3D {
private:
    float x, y, z;

public:
    // 🔹 Constructeur avec valeurs par défaut
    Vecteur3D(float x_ = 0, float y_ = 0, float z_ = 0)
        : x(x_), y(y_), z(z_) {}

    // 🔹 Affichage du vecteur
    void afficher() const {
        cout << "(" << x << ", " << y << ", " << z << ")";
    }

    // 🔹 Somme de deux vecteurs — résultat renvoyé par valeur
    Vecteur3D somme(const Vecteur3D &v) const {
        return Vecteur3D(x + v.x, y + v.y, z + v.z);
    }

    // 🔹 Produit scalaire
    float produitScalaire(const Vecteur3D &v) const {
        return (x * v.x + y * v.y + z * v.z);
    }

    // 🔹 Vérifie si deux vecteurs coïncident
    bool coincide(const Vecteur3D &v) const {
        return (x == v.x && y == v.y && z == v.z);
    }

    // 🔹 Norme du vecteur
    float norme() const {
        return sqrt(x * x + y * y + z * z);
    }

    // =============================================
    // === PARTIE DEMANDÉE : normax sous 3 formes ===
    // =============================================

    // 1️⃣ Résultat renvoyé par valeur
    Vecteur3D normax_valeur(const Vecteur3D &v) const {
        if (this->norme() >= v.norme())
            return *this; // retourne une copie
        else
            return v;
    }

    // 2️⃣ Résultat renvoyé par adresse
    const Vecteur3D* normax_adresse(const Vecteur3D* v) const {
        if (this->norme() >= v->norme())
            return this; // retourne l’adresse du vecteur courant
        else
            return v;
    }

    // 3️⃣ Résultat renvoyé par référence
    const Vecteur3D& normax_reference(const Vecteur3D &v) const {
        if (this->norme() >= v.norme())
            return *this; // retourne une référence sur l’objet courant
        else
            return v;
    }
};

int main() {
    // Création de quelques vecteurs
    Vecteur3D v1(3, 4, 0); // norme = 5
    Vecteur3D v2(1, 2, 2); // norme ≈ 3

    cout << "v1 = "; v1.afficher(); cout << endl;
    cout << "v2 = "; v2.afficher(); cout << endl;

    // 🔹 Somme
    cout << "\nSomme : ";
    Vecteur3D s = v1.somme(v2);
    s.afficher(); cout << endl;

    // 🔹 Produit scalaire
    cout << "Produit scalaire : " << v1.produitScalaire(v2) << endl;

    // 🔹 Vérifie coïncidence
    cout << "Les deux vecteurs coincident ? "
         << (v1.coincide(v2) ? "Oui" : "Non") << endl;

    // 🔹 Normes
    cout << "Norme v1 = " << v1.norme() << endl;
    cout << "Norme v2 = " << v2.norme() << endl;

    // 🔹 normax par valeur
    cout << "\nNormax (valeur) : ";
    Vecteur3D max1 = v1.normax_valeur(v2);
    max1.afficher(); cout << endl;

    // 🔹 normax par adresse
    cout << "Normax (adresse) : ";
    const Vecteur3D* max2 = v1.normax_adresse(&v2);
    max2->afficher(); cout << endl;

    // 🔹 normax par référence
    cout << "Normax (référence) : ";
    const Vecteur3D& max3 = v1.normax_reference(v2);
    max3.afficher(); cout << endl;

    return 0;
}

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Vecteur3d
{
private:
    float x, y, z;

public:
    Vecteur3d(float x = 0, float y = 0, float z = 0)
        : x(x), y(y), z(z)
    {
    }

    void afficher()
    {
        cout << "(" << x << ", " << y << ", " << z << ")" << endl;
    }

    Vecteur3d somme(const Vecteur3d &vect2)
    {
        Vecteur3d vectSom(x + vect2.x, y + vect2.y, z + vect2.z);
        cout << "La somme du vecteur " << "(" << x << ", " << y << ", " << z << ")" << " et du vecteur " << "(" << vect2.x << ", " << vect2.y << ", " << vect2.z << ")" << "egale " << "(" << x + vect2.x << ", " << y + vect2.y << ", " << z + vect2.z << ")" << endl;

        return (vectSom);
    }

    float produit(const Vecteur3d &vect2)
    {
        float vectProd(x * vect2.x + y * vect2.y + z * vect2.z);
        cout << "Le produit du vecteur " << "(" << x << ", " << y << ", " << z << ")" << " et du vecteur " << "(" << vect2.x << ", " << vect2.y << ", " << vect2.z << ")" << "egale : " << vectProd << endl;

        return (vectProd);
    }

    bool coincide(const Vecteur3d &vect2)
    {
        if (x == vect2.x && y == vect2.y && z == vect2.z)
        {
            cout << "Les deux vecteurs coincident !!!!" << endl;
            return true;
        }
        else
        {
            cout << "Les deux vecteurs ne coincident pas !!!!" << endl;
            return false;
        }
    }

    float norme() const
    {
        /* float norme = sqrt(x * x + y * y + z * z);
        cout << "La nome du vecteur " << "(" << x << ", " << y << ", " << z << ")" << " eg al a " << norme << endl;*/
        return sqrt(x * x + y * y + z * z);
    }

    Vecteur3d normax(const Vecteur3d &vect)
    {
        if (this->norme() >= vect.norme())
            return *this;
        else
            return vect;

        /* float norme1 = sqrt(x * x + y * y + z * z);
        float norme2 = sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z);

        if (norme1 < norme2)
            return norme2;
        else if (norme1 > norme2)
            return norme1;
        else
        {
            cout << "Les normes des deux vecteurs sont egaux !" << endl;
            return 0;
        } */
    }

    const Vecteur3d *normax_address(const Vecteur3d *vect)
    {
        if (this->norme() >= vect->norme())
            return this;
        else
            return vect;
    }

    const Vecteur3d &normax_refference(const Vecteur3d &vect)
    {
        if (this->norme() >= vect.norme())
            return *this;
        else
            return vect;
    }
};

int main()
{

    Vecteur3d vecteur1(0, 0, 4);
    Vecteur3d vecteur2(4, 5, 6);

    vecteur1.afficher();
    vecteur1.somme(vecteur2);
    vecteur1.produit(vecteur2);
    vecteur1.coincide(vecteur2);
    vecteur1.norme();
    vecteur2.norme();
}
#include <iostream>
using namespace std;

void remplir(int *arr, int n)
{

    for (int i = 0; i < n; i++)
    {
        cout << "Nombre " << i + 1 << " : ";
        cin >> *arr;
        arr++;
    }
}

void afficher(const int *arr, int n)
{

    for (int i = 0; i < n; i++)
    {
        cout << "Nombre " << i + 1 << " : " << *arr << endl;
        arr++;
        //_sleep(500);
    }
}

int &trouverMax(int *arr, int n)
{
    int *max = arr;

    for (int i = 0; i < n; i++)
    {
        if (*arr > *max)
            max = arr;
        arr++;
    }
    return *max;
}

int &trouverMaxChatGPT(int *arr, int n)
{
    int *pmax = arr; // pointeur vers le max actuel

    for (int i = 1; i < n; i++)
    {
        if (*(arr + i) > *pmax)
            pmax = arr + i; // pmax pointe vers le nouvel élément max
    }

    return *pmax; // on retourne une référence vers cet élément
}

void inverser(const int *arr, int n)
{
    int arrInverse[n];
    for (int i = 1; i <= n; i++)
    {
        arrInverse[n - i] = *arr;
        arr++;
    }
    cout << "Le tableau inverser: " << endl;
    afficher(arrInverse, n);
}

int main()
{
    int n;
    cout << "Entrer la taille du tableau: ";
    cin >> n;

    int arr[n];
    cout << "Entrer des nombres entiers dans le tableau:" << endl;
    //_sleep(500);

    remplir(arr, n);

    cout << "Apres 1s le tableau va etre afficher!" << endl;
    //_sleep(1000);
    afficher(arr, n);

    int &maximum = trouverMax(arr, n);
    cout << "Le max est: " << maximum << endl;

    cout << "Entrez une nouvelle valeur pour remplacer le maximum : ";
    cin >> maximum;

    inverser(arr, n);

    /* // Remplir
    for (int i = 0; i < n; i++)
    {
        cout << "Nombre " << i + 1 << " : ";
        cin >> arr[i];
    }

    // Afficher
    cout << "Je vais afficher le tableau:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "Nombre " << i + 1 << " = " << arr[i];
        cout << endl;
    } */

    return 0;
}

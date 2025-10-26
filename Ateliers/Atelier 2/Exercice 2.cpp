#include <iostream>
using namespace std;

int multipleDeDeux(int num) {
    /* || Methode simple*/
        /* if( num%2 == 0){
            return 1;
        }
        else {
            return 0;
        } */

    /* || Methode 2*/
        /* return (num%2 == 0) ?  1 :  0; */

    /* || Methode 3*/
        return (num%2 == 0);
}

int multipleDeTrois(int num) {
    /* || Methode simple*/
    /* if( num%3 == 0){
        return 1;
    }
    else {
        return 0;
    } */

    /* || Methode 2*/
    /* return (num%3 == 0) ?  1 :  0; */

    /* || Methode 3*/
    return (num%3 == 0);
}

int main(){
    int num;

    for(int i=0; i<4; i++){

    cout << "donner un entier : " ;
    cin >> num;

    int checkPair = multipleDeDeux(num);
    int checkMlutTrois = multipleDeTrois(num);

        /* || With Ternary Operator */
    checkPair 
    ? cout << "Le nombre " << num << " est pair" << endl 
    : cout << "Le nombre " << num << " est impair" << endl;

    checkMlutTrois 
    ? cout << "Le nombre " << num << " est multiple de 3" << endl 
    : cout << "Le nombre " << num << " n'est pas multiple de 3" << endl;

    num%6 == 0 
    ? cout << "Le nombre " << num << " est divisible par 6" << endl 
    : cout << "Le nombre " << num << " n'est pas divisible par 6" << endl;


        /* || Simple way */
    /* if(checkPair){
        cout << "Le nombre " << num << " est pair" << endl;
    }
    else {
        cout << "Le nombre " << num << " est impair" << endl;
    } */

    /* if(checkMlutTrois){
        cout << "Le nombre " << num << " est multiple de 3" << endl;
    }
    else {
        cout << "Le nombre " << num << " n'est pas multiple de 3" << endl;
    } */

    /* if(num%6 == 0){
        cout << "Le nombre " << num << " est divisible par 6" << endl;
    }
    else {
        cout << "Le nombre " << num << " n'est pas divisible par 6" << endl;
    } */

    cout << "-----------------------" << endl;

    }

    
}


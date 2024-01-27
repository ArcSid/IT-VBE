#include <iostream>
#include <fstream>
using namespace std;

void skaitymas(int& num, int lytis[], int rankosPuse[], int dydis[]){
    ifstream data("U1.txt");
    data >> num;
    for(int i = 0; i<num; i++){
        data >> lytis[i] >> rankosPuse[i] >> dydis[i];
    }
    data.close();
}

void poruAtrinkimas(int& num, int lytis[], int rankosPuse[], int dydis[]){
    
}

int main(){
    int num;
    int lytis[100];
    int rankosPuse[100];
    int dydis[100];

    skaitymas(num, lytis, rankosPuse, dydis);
    poruAtrinkimas(num, lytis, rankosPuse, dydis);
}
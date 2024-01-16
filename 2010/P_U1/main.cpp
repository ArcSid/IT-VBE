#include <iostream>
#include <fstream>
using namespace std;

void skaitymas(int turimos_figureles[]){
    ifstream data("U1.txt");
    int n;
    data >> n;
    for(int i = 0; i<n; i++){
        int n;
        data >> n;
        turimos_figureles[0] += 8-n;
        data >> n;
        turimos_figureles[1] += 2-n;
        data >> n;
        turimos_figureles[2] += 2-n;
        data >> n;
        turimos_figureles[3] += 2-n;
        data >> n;
        turimos_figureles[4] += 1-n;
        data >> n;
        turimos_figureles[5] += 1-n;
    }
}

int kiekRinkiniu(int turimos_figureles[]){
    turimos_figureles[0] = turimos_figureles[0]/8;
    turimos_figureles[1] = turimos_figureles[1]/2;
    turimos_figureles[2] = turimos_figureles[2]/2;
    turimos_figureles[3] = turimos_figureles[3]/2;
    int n = turimos_figureles[0];
    for(int i = 0; i<6; i++){
        if(n > turimos_figureles[i]){
            n = turimos_figureles[i];
        }
    }
    return n;
}

void rez(int n){
    ofstream rez("U1rez.txt");
    rez << n << endl;
}

int main(){
    int turimos_figureles[6] = {0};
    skaitymas(turimos_figureles);
    rez(kiekRinkiniu(turimos_figureles));
    return 0;
}
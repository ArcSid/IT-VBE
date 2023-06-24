#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

struct Varza{
    double varza[50];
    int count;
    double bendra_varza(){
        double sum = 0;
        for(int i = 0; i<count; i++){
            sum+=1/varza[i];
        }
        return sum;
    }
};
void rez(double sistemos_varza){
  ofstream rez("U1rez.txt");
  rez << fixed << setprecision(2) << sistemos_varza << endl;
}

double bendra_sistemos_varza(int varzu_kiekis, Varza varzos[]){
    double sum = 0;
    for(int i = 0; i<varzu_kiekis; i++){
        sum += 1/varzos[i].bendra_varza();
    }
    return sum;
}

void skaitymas(int& varzu_kiekis, Varza varzos[]){
    ifstream data("U1.txt");
    data >> varzu_kiekis;
    for(int i = 0; i<varzu_kiekis; i++){
        data >> varzos[i].count;
        for(int a = 0; a<varzos[i].count; a++){
            data >> varzos[i].varza[a];
        }
    }
}
int main(){
    Varza varzos[100];
    int varzu_kiekis;
    skaitymas(varzu_kiekis,varzos);
    rez(bendra_sistemos_varza(varzu_kiekis,varzos));
}
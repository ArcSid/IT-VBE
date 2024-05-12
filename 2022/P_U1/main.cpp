#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

struct Parduotuve{
    string pavadinimas;
    vector<float> kainos;
    vector<string> prekes;
};

void skaitytiIsFailo(vector<Parduotuve>& parduotuves, int& piniguKiekis, vector<string>& prekes){
    ifstream data("U1.txt");
    int prekiuKiekis;
    float kaina;

    data >> prekiuKiekis;
    data >> piniguKiekis;

    string preke;
    for(int i = 0; i<prekiuKiekis; i++){
        data >> preke;
        prekes.push_back(preke);
    }

    for(int i = 0; i<5; i++){
        char ch[11];
        data.ignore();
        data.get(ch, 10);
        Parduotuve tempParduotuve;
        tempParduotuve.pavadinimas = ch;
        for(int j = 0; j<prekiuKiekis; j++){
            data >> kaina;
            tempParduotuve.kainos.push_back(kaina);
        }
        parduotuves.push_back(tempParduotuve);
    }
    data.close();
}

float rastiPigiausiuKainuSuma(vector<Parduotuve> parduotuves, float minimumai[]){
    float suma = 0;
    int prekiuKiekis = parduotuves[0].kainos.size();
    for(int i = 0; i<prekiuKiekis; i++){
        int min_j = 0;
        for(int j = 0; j<parduotuves.size(); j++){
            if(parduotuves[j].kainos[i] > 0){
                min_j = j;
                break;
            }
        }
        for(int j = 0; j<parduotuves.size(); j++){
            if(parduotuves[j].kainos[i] < parduotuves[min_j].kainos[i] && parduotuves[j].kainos[i] > 0){
                min_j = j;
            }
        }
        suma += parduotuves[min_j].kainos[i];
        minimumai[i] = parduotuves[min_j].kainos[i];
    }
    return suma;
}

void priskirtiPrekesParduotuvems(vector<Parduotuve>& parduotuves, float minimumai[], vector<string> prekes){
    for(int i = 0; i<parduotuves.size(); i++){
        for(int j = 0; j<prekes.size(); j++){
            if(parduotuves[i].kainos[j] == minimumai[j]){
                parduotuves[i].prekes.push_back(prekes[j]);
            }
        }
    }
}

void rikiuotiParduotuves(vector<Parduotuve>& parduotuves){
    for(int i = 0; i<parduotuves.size(); i++){
        for(int j = 0; j<parduotuves.size()-1-i; j++){
            if(parduotuves[j].prekes.size() < parduotuves[j+1].prekes.size()){
                swap(parduotuves[j], parduotuves[j+1]);
            }
        }
    }
}

void rez(int piniguKiekis, float maziausiaKaina, vector<Parduotuve> parduotuves){
    ofstream rez("U1rez.txt");
    if((float) maziausiaKaina > piniguKiekis){
        rez << "Nepavyks nusipirkti" << endl;
        rez.close();
        return;
    }
    rez << maziausiaKaina << endl;
    for(int i = 0; i<parduotuves.size(); i++){
        if(parduotuves[i].prekes.size() > 0){
            rez << parduotuves[i].pavadinimas << " ";
            for(int j = 0; j<parduotuves[i].prekes.size(); j++){
                rez << setw(10) << parduotuves[i].prekes[j] << " ";
            }
            rez << endl; 
        }
    }
    rez.close();
}

int main(){
    vector<Parduotuve> parduotuves;
    int piniguKiekis;
    vector<string> prekes;
    skaitytiIsFailo(parduotuves, piniguKiekis, prekes);
    float minimumai[10] = {0};
    float maziausiaKaina =  rastiPigiausiuKainuSuma(parduotuves, minimumai);
    priskirtiPrekesParduotuvems(parduotuves,minimumai,prekes);
    rikiuotiParduotuves(parduotuves);
    rez(piniguKiekis, maziausiaKaina, parduotuves);
    return 0;
}
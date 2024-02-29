#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Seka{
    vector<int> seka;
    vector<int> ivykdytosKomandos;
    int xf, yf;
    string resultatas;
};

// xc ir yc - current x ir y, xf ir yf - final x ir y

void komanduVykdymas(int x0, int y0, Seka& seka){
    int xc = x0, yc = y0;
    for(int i = 0; i<seka.seka.size(); i++){
        if(i != 0 && xc == x0 && yc == y0){
            seka.resultatas = "pasiektas tikslas";
            break;
        }
        if(seka.seka[i] == 1){
            xc ++;
            yc ++;
            seka.ivykdytosKomandos.push_back(seka.seka[i]);
            continue;
        }
        if(seka.seka[i] == 2){
            xc ++;
            yc --;
            seka.ivykdytosKomandos.push_back(seka.seka[i]);
            continue;
        }
        if(seka.seka[i] == 3){
            xc --;
            yc --;
            seka.ivykdytosKomandos.push_back(seka.seka[i]);
            continue;
        }
        if(seka.seka[i] == 4){
            xc --;
            yc ++;
            seka.ivykdytosKomandos.push_back(seka.seka[i]);
            continue;
        }
    }


    if(xc != x0 && yc != x0){
        seka.resultatas = "sekos pabaiga";
    }
    seka.xf = xc;
    seka.yf = yc;

}

void skaitymas(int& x0, int& y0, int& sekuKiekis, Seka sekos[10]){
    int sekosIlgis;
    int sekosKomanda;
    ifstream data("U2.txt");
    data >> x0 >> y0 >> sekuKiekis;
    for(int i = 0; i<sekuKiekis; i++){
        data >> sekosIlgis;
        for(int j = 0; j<sekosIlgis; j++){
            data >> sekosKomanda;
            sekos[i].seka.push_back(sekosKomanda);
        }
    }
    data.close();
}

void rez(int sekuKiekis, Seka sekos[]){
    ofstream rez("U2rez.txt");
    for(int i = 0; i<sekuKiekis; i++){
        rez << sekos[i].resultatas << " ";
        if(sekos[i].resultatas == "sekos pabaiga"){
            rez << sekos[i].seka.size() << " ";
        }
        for(int j = 0; j<sekos[i].ivykdytosKomandos.size(); j++){
            rez << sekos[i].ivykdytosKomandos[j] << " ";
        }
        if(sekos[i].resultatas == "pasiektas tikslas"){
            rez << sekos[i].ivykdytosKomandos.size() << endl;
        }
        if(sekos[i].resultatas == "sekos pabaiga"){
            rez << sekos[i].xf << " " << sekos[i].yf << endl;
        }
    }
    rez.close();
}

int main(){
    int x0, y0;
    int sekuKiekis;
    Seka sekos[10];
    skaitymas(x0, y0, sekuKiekis, sekos);
    for(int i = 0; i<sekuKiekis; i++){
        komanduVykdymas(x0, y0, sekos[i]);
    }
    rez(sekuKiekis, sekos);
    return 0;
}
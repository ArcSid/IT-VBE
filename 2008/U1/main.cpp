#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct Asmuo{
    int gimimo_metai;
    int gimimo_menesis;
    int gimimo_diena;

    int mirties_metai;
    int mirties_menesis;
    int mirties_diena;

    string vardas;
    // metai turi 365d
    int kiekDienuGyveno(){
        int metuDienos[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
        int menesiuDienos = 0;
        for(int i = 0; i<gimimo_menesis; i++){
            menesiuDienos += metuDienos[i];
        }
        int gimimasDienomis = gimimo_metai*365+menesiuDienos+gimimo_diena;
        menesiuDienos = 0;
        for(int i = 0; i<mirties_menesis; i++){
            menesiuDienos+=metuDienos[i];
        }
        int mirtisDienomis = mirties_metai*365+menesiuDienos+mirties_diena;

        return mirtisDienomis-gimimasDienomis;
    }

};

void skaitymas(vector<Asmuo>& asmenys){
    int asmenu_kiekis;
    ifstream data("U2.txt");
    data >> asmenu_kiekis;
    ofstream test("test.txt");
    for(int i = 0; i<asmenu_kiekis; i++){
        char vardas[21];
        char tempchars[2];
        data.read(tempchars,1);
        data.read(vardas,20);
        vardas[20] = '\0';
        Asmuo temp;
        temp.vardas = vardas;
        data >> temp.gimimo_metai >> temp.gimimo_menesis >> temp.gimimo_diena;
        data >> temp.mirties_metai >> temp.mirties_menesis >> temp.mirties_diena;
        asmenys.push_back(temp);
    }
    data.close();
}

void rez(vector<Asmuo> asmenys){
    ofstream data("U2rez.txt");
    for(int i = 0; i<asmenys.size(); i++){
        //cout << asmenys[i].vardas.length() << " " << asmenys[i].vardas<< endl;
        data << asmenys[i].vardas << " " << asmenys[i].gimimo_metai << " " << asmenys[i].gimimo_menesis << " " << asmenys[i].gimimo_diena << 
        " " << asmenys[i].mirties_metai << " " << asmenys[i].mirties_menesis << " " << asmenys[i].mirties_diena 
        << " " << asmenys[i].kiekDienuGyveno() << endl;
    }
    res.close();
}

int main(){
    vector<Asmuo> asmenys;
    skaitymas(asmenys);
    rez(asmenys);
    return 0;
}

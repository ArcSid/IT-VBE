#include <iostream>
#include <fstream>
using namespace std;

void skaitymas(int& nominaluSk, int& gilijuKiekis, int nominalai[]){
    ifstream data("U1.txt");
    int mokiniuSk;
    data >> mokiniuSk;
    int gilijos;
    for(int i = 0; i<mokiniuSk; i++){
        data >> gilijos;
        gilijuKiekis+=gilijos;
    }
    data >> nominaluSk;
    for(int i = 0; i<nominaluSk; i++){
        data >> nominalai[i];
    }
    data.close();
}

void monetuSkaiciavimas(int nominaluSk, int gilijuKiekis, int nominalai[], int nominaluoseGautuMonetuSk[], int& liko){
    for(int i = 0; i<nominaluSk; i++){
        nominaluoseGautuMonetuSk[i] = gilijuKiekis/nominalai[i];
        gilijuKiekis =  gilijuKiekis % nominalai[i];
    }
    liko = gilijuKiekis;
}

void rez(int nominaluSk, int nominaluoseGautuMonetuSk[], int nominalai[], int gilijuKiekis, int liko){
    ofstream rez("U1rez.txt");
    rez << gilijuKiekis << endl;
    for(int i = 0; i<nominaluSk; i++){
        rez << nominalai[i] << " " << nominaluoseGautuMonetuSk[i] << endl;
    }
    rez << liko << endl;
    rez.close();
}

int main(){
    int nominaluSk;
    int nominalai[15];
    int gilijuKiekis = 0;
    int nominaluoseGautuMonetuSk[15] = {0};
    int liko = 0;
    skaitymas(nominaluSk, gilijuKiekis, nominalai);
    monetuSkaiciavimas(nominaluSk, gilijuKiekis, nominalai, nominaluoseGautuMonetuSk, liko);
    rez(nominaluSk, nominaluoseGautuMonetuSk, nominalai, gilijuKiekis, liko);
    return 0;   
}
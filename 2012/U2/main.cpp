#include <iostream>
#include <fstream>

using namespace std;

struct Dievas {
  string vardas;
  int kauliukai[10] = {0};
  int kauliuku_kiekis;

  int tasku_suma() {
    int suma = 0;
    for(int i = 0; i<kauliuku_kiekis; i++) {
      if(kauliukai[i] %2 != 0) {
        suma -= kauliukai[i];
      } else {
        suma += kauliukai[i];
        
      }
    }
    return suma;
  }

  int lyginiu_sk(){
    int lyg_sk = 0;
    for(int i = 0; i<kauliuku_kiekis; i++){
      if(kauliukai[i] %2 == 0){
        lyg_sk++;
      }
    }
    return lyg_sk;
  }
};

void resultatas(Dievas dievas){
  ofstream rez("U2rez.txt");
  rez << dievas.vardas << dievas.tasku_suma();
  rez.close();
}

int isrinktas_dievas(int dievu_kiekis, Dievas dievai[]) {
  int max_taskai = dievai[0].tasku_suma();
  int dievo_indikatorius = 0;
  
  for(int i = 0; i < dievu_kiekis; i++){
    if(dievai[i].tasku_suma() > max_taskai) {
      max_taskai = dievai[i].tasku_suma();
      dievo_indikatorius = i;
      continue;
    }
    
    if(max_taskai == dievai[i].tasku_suma()) {
      if(dievai[i].lyginiu_sk() > dievai[dievo_indikatorius].lyginiu_sk()) {
        dievo_indikatorius = i;
        
      }
    }
  }
  return dievo_indikatorius;
}

void skaitymas(int& kauliuku_kiekis,int& dievu_kiekis, Dievas dievai[]) {
  
  ifstream data("U2.txt");
  data >> dievu_kiekis >> kauliuku_kiekis;
  
  for(int i = 0; i < dievu_kiekis; i++) {
    char ch[11];
    data.read(ch, 1); // read ENDLINE
    data.read(ch, 10);
    dievai[i].vardas = ch;
    for(int a = 0; a < kauliuku_kiekis; a++){
      data >> dievai[i].kauliukai[a];
    }
  }
  data.close();
}

int main() {
  Dievas dievai[50];
  int kauliuku_kiekis;
  int dievu_kiekis;
  
  skaitymas(kauliuku_kiekis, dievu_kiekis, dievai);
  for(int i = 0; i< dievu_kiekis; i++) {
    dievai[i].kauliuku_kiekis = kauliuku_kiekis;
  }
  
  int indicator = isrinktas_dievas(dievu_kiekis, dievai);
  resultatas(dievai[indicator]);
  
  return 0;
}

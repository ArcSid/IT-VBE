#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int pradiniaiDuomenys = 5;
const int piratuKiekis = 10;

void skaitymas(int piratai[]){
  ifstream data("U1.txt");
  for(int i = 0; i<pradiniaiDuomenys; i++){
    data >> piratai[i];
  }
  for(int i = pradiniaiDuomenys; i<piratuKiekis-pradiniaiDuomenys; i++){
    piratai[i] = 0;
  }
  data.close();
}

void pasidalinimas(int piratai[], int pasidaline[]){
  for(int i = 0; i<pradiniaiDuomenys; i++){
      for(int j = i+1; j<piratuKiekis; j++){
        if(piratai[i] - 1 >= 0){
          pasidaline[j]++;
          piratai[i]--;
        }
        if(j == piratuKiekis-1){
          pasidaline[i] += piratai[i];
        }
    }
  }
}

void rez(int pasidaline[]){
  ofstream rez("U1rez.txt");
  for(int i = 0; i<piratuKiekis; i++){
    rez << pasidaline[i] << " ";
  }
  rez << endl;
  rez.close();
}

int main() {
  int piratai[10];
  skaitymas(piratai);
  int pasidaline[10] = {0};
  pasidalinimas(piratai, pasidaline);
  rez(pasidaline);
  return 0;
}
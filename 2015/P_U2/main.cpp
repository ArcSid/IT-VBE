#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Mokinys{
  string vardas;
  string atsakymai;
  int taskuKiekis = 0;
  bool mokytojas = false;
};

void skaitymas(vector<Mokinys>& mokiniai){
  int mokiniuKiekis;
  int klausimuKiekis;
  int mokytojoIndikatorius;
  ifstream data("U2.txt");
  data >> mokiniuKiekis;
  data >> klausimuKiekis;
  data >> mokytojoIndikatorius;
  for(int i = 0; i<mokiniuKiekis; i++){
    Mokinys tempMokinys;
    data.ignore();
    char vardas[11];
    data.read(vardas, 10);
    vardas[10] = '\0';
    tempMokinys.vardas = vardas;
    data >> tempMokinys.atsakymai;
    if(i == mokytojoIndikatorius-1){
      tempMokinys.mokytojas = true;
    }
    mokiniai.push_back(tempMokinys);
  }
  data.close();
}

void taskuSkaiciavimas(vector<Mokinys>& mokiniai){
  Mokinys mokytojas;
  for(int i = 0; i<mokiniai.size(); i++){
    if(mokiniai[i].mokytojas == true){
      mokytojas = mokiniai[i];
      break;
    }
  }

  for(int i = 0; i<mokiniai.size(); i++){
    if(mokiniai[i].mokytojas == true){
      continue;
    }
    for(int j = 0; j<mokiniai[i].atsakymai.length(); j++){
      if(mokiniai[i].atsakymai[j] == mokytojas.atsakymai[j]){
        mokiniai[i].taskuKiekis++;
      }
    }
  }
}

void sort(vector<Mokinys>& mokiniai){
  for(int i = 0; i<mokiniai.size(); i++){
    for(int j = 0; j<mokiniai.size()-1-i; j++){
      if(mokiniai[j].taskuKiekis == mokiniai[j+1].taskuKiekis && mokiniai[j].vardas > mokiniai[j+1].vardas){
        swap(mokiniai[j],mokiniai[j+1]);
      }
      if(mokiniai[j].taskuKiekis > mokiniai[j+1].taskuKiekis){
        swap(mokiniai[j],mokiniai[j+1]);
      }
    }
  }
}

void rez(vector<Mokinys> mokiniai){
  ofstream rez("U2rez.txt");
  for(int i = 0; i<mokiniai.size(); i++){
    if(mokiniai[i].mokytojas == true){
      rez << mokiniai[i].vardas << endl;
    }
  }

  for(int i = 0; i<mokiniai.size(); i++){
    if(mokiniai[i].mokytojas == true){
      continue;
    }
    rez << mokiniai[i].vardas << " " << mokiniai[i].taskuKiekis << endl;
  }
  rez.close();
}

int main() {
  vector<Mokinys> mokiniai;
  skaitymas(mokiniai);
  taskuSkaiciavimas(mokiniai);
  sort(mokiniai);
  rez(mokiniai);
  return 0;
}
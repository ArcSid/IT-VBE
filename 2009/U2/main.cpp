#include <fstream>

using namespace std;

struct Begikas {
  string vardas;
  int minutes;
  int sekundes;

  int begimo_trukme() {
    return minutes * 60 + sekundes;
  }
};

struct Grupe {
  int begiku_kiekis = 0;
  Begikas begikai[50];
};

void spausdinimas(int grupiu_kiekis,Grupe grupe[])
{
  Begikas laimejusieji[50];
  ofstream rez("U2rez.txt");
  int temp = 0;
  for (int i = 0; i<grupiu_kiekis;i++)
    {
      int laimejusiu_skaicius= grupe[i].begiku_kiekis/2;
      for (int b = 0;b<laimejusiu_skaicius;b++)
        {
          laimejusieji[temp] = grupe[i].begikai[b];
          temp++;
        }
    }
  for (int b = 0; b< temp;b++)
    {
      for (int i = 0; i<temp-b-1;i++)
      {
        if (laimejusieji[i].begimo_trukme()>laimejusieji[i+1].begimo_trukme())
        {
          swap(laimejusieji[i],laimejusieji[i+1]);
        }
      }
    }
  for (int i = 0;i<temp;i++)
    {
      rez << laimejusieji[i].vardas << " " << laimejusieji[i].minutes << " " << laimejusieji[i].sekundes << endl;
    }
}


void sort(Grupe &grupe)
{
  for (int b = 0; b< grupe.begiku_kiekis;b++)
    {
      for (int i = 0; i<grupe.begiku_kiekis-b-1;i++)
      {
        if (grupe.begikai[i].begimo_trukme() > grupe.begikai[i+1].begimo_trukme())
        {
          swap(grupe.begikai[i], grupe.begikai[i+1]);
        }
      }
    }
}





void skaitymas(int &grupiu_skaicius, Grupe grupe[]);


int main() {
  Grupe grupe[50];
  int grupiu_skaicius;
  skaitymas(grupiu_skaicius, grupe);
  for (int i = 0;i<grupiu_skaicius;i++)
    {
      sort(grupe[i]);
    }
  spausdinimas(grupiu_skaicius,grupe);
}





void skaitymas(int &grupiu_skaicius, Grupe grupe[]) {
  ifstream data("U2.txt");
  data >> grupiu_skaicius;
  string skip_data;
  int nariu_skaicius;

  for (int a = 0; a < grupiu_skaicius; a++) {
    data >> nariu_skaicius;
    grupe[a].begiku_kiekis = nariu_skaicius;
    getline(data, skip_data);
    for (int i = 0; i < nariu_skaicius; i++) {
      string vardas = "";
      getline(data, vardas);
      string assembled = "";
      for (int c = 0; c < 20; c++) {
        assembled += vardas[c];
      }
      grupe[a].begikai[i].vardas = assembled;
      grupe[a].begikai[i].minutes = stoi(vardas.substr(20, 2));
      grupe[a].begikai[i].sekundes = stoi(vardas.substr(22, 3));
    }
  }
}
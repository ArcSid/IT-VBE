#include <fstream>
using namespace std;
struct Patiekalas
{
  int produktai[10];
  string raw_data;
};
void spausdinimas(int patiekalu_kiekis, string patiekalu_pavadinimai[], int patiekalu_kainos[], int litai, int centai)
{
  ofstream rez("U2rez.txt");
  for(int i = 0; i<patiekalu_kiekis;i++)
    {
      rez << patiekalu_pavadinimai[i] << patiekalu_kainos[i];
    }
  rez << endl << litai << " " << centai << endl;
}
void komplekto_kainos_skaiciavimas(int patiekalu_kiekis, int patiekalu_kainos[], int &litai, int &centai)
{
  int kainos_suma = 0;
  for(int i = 0; i< patiekalu_kiekis;i++)
    {
      kainos_suma += patiekalu_kainos[i];
    }
  litai = kainos_suma / 100;
  centai = kainos_suma % 100;
}

int patiekalo_kainos_skaiciavimas(int prod_kiekis, Patiekalas patiekalas, int prod_kainos[])
{
  int kaina = 0;
  for(int i =0;i<prod_kiekis;i++)
    {
      kaina+=patiekalas.produktai[i]*prod_kainos[i];
    }
  return kaina;
}

void skaitymas(int& prod_kiekis, int& pat_kiekis, string pat_pavadinimai[], Patiekalas patiekalas[], int prod_kainos[])
{
  ifstream data("U2.txt");
  data >> prod_kiekis;
  data >> pat_kiekis;

  for(int i = 0; i<prod_kiekis;i++)
    {
      data >> prod_kainos[i];
    }
  for (int i = 0; i<pat_kiekis;i++)
    {
      char name[16] = {0};
      data.read(name, 15);
      pat_pavadinimai[i] = name;
      for (int n = 0; n<prod_kiekis; n++)
        {
          int temp;
          data >> temp;
          patiekalas[i].produktai[n] = temp;
        }
    }
}

int main() {
  int produktu_kiekis, patiekalu_skaicius, prod_kainos[12];
  string patiekalu_pavadinimai[12];
  Patiekalas patiekalas[12];
  skaitymas(produktu_kiekis, patiekalu_skaicius, patiekalu_pavadinimai, patiekalas, prod_kainos);
  int patiekalu_kainos[12];
  for(int i = 0; i<patiekalu_skaicius;i++)
    {
      patiekalu_kainos[i] = patiekalo_kainos_skaiciavimas(produktu_kiekis,patiekalas[i],prod_kainos);
    }
  int litai, centai;
  komplekto_kainos_skaiciavimas(patiekalu_skaicius, patiekalu_kainos, litai, centai);
  spausdinimas(patiekalu_skaicius,patiekalu_pavadinimai,patiekalu_kainos,litai,centai);
}

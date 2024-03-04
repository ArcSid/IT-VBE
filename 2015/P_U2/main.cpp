#include <iostream>
#include <fstream>
using namespace std;

struct DalyvioDuomenys
{
  string vardas;
  string atsakymai;
  int taskuKiekis = 0;
};

void skaitymas(int &mokiniuKiekis, DalyvioDuomenys &mokytojas, DalyvioDuomenys mokiniai[])
{
  int dalyviuKiekis;
  int klausimuKiekis;
  int mokytojoIndikatorius;
  ifstream data("U2.txt");
  data >> dalyviuKiekis;
  data >> klausimuKiekis;
  data >> mokytojoIndikatorius;
  int mokytojasRastas = 0;
  for (int i = 0; i < dalyviuKiekis; i++)
  {
    // praleidziame endline
    data.ignore();

    char vardas[11];
    data.read(vardas, 10);
    vardas[10] = '\0';
    if (i == mokytojoIndikatorius - 1)
    {
      mokytojas.vardas = vardas;
      data >> mokytojas.atsakymai;
      mokytojasRastas = 1;
      continue;
    }
    mokiniai[i - mokytojasRastas].vardas = vardas;
    data >> mokiniai[i - mokytojasRastas].atsakymai;
  }
  mokiniuKiekis = dalyviuKiekis - 1;
  data.close();
}

int atsakymuPatikrinimas(DalyvioDuomenys mokytojas, DalyvioDuomenys mokinys)
{
  int sum = 0;
  for (int j = 0; j < mokinys.atsakymai.length(); j++)
  {
    if (mokinys.atsakymai[j] == mokytojas.atsakymai[j])
    {
      sum++;
    }
  }
  return sum;
}

void taskuSkaiciavimas(int mokiniuKiekis, DalyvioDuomenys mokytojas, DalyvioDuomenys mokiniai[])
{
  for (int i = 0; i < mokiniuKiekis; i++)
  {
    mokiniai[i].taskuKiekis = atsakymuPatikrinimas(mokytojas, mokiniai[i]);
  }
}

void sort(int mokiniuKiekis, DalyvioDuomenys mokiniai[])
{
  for (int i = 0; i < mokiniuKiekis; i++)
  {
    for (int j = 0; j < mokiniuKiekis - 1 - i; j++)
    {
      if (mokiniai[j].taskuKiekis == mokiniai[j + 1].taskuKiekis && mokiniai[j].vardas > mokiniai[j + 1].vardas)
      {
        swap(mokiniai[j], mokiniai[j + 1]);
      }
      if (mokiniai[j].taskuKiekis > mokiniai[j + 1].taskuKiekis)
      {
        swap(mokiniai[j], mokiniai[j + 1]);
      }
    }
  }
}

void rez(int mokiniuKiekis, DalyvioDuomenys mokytojas, DalyvioDuomenys mokiniai[])
{
  ofstream rez("U2rez.txt");
  rez << mokytojas.vardas << endl;
  for (int i = 0; i < mokiniuKiekis; i++)
  {
    rez << mokiniai[i].vardas << " " << mokiniai[i].taskuKiekis << endl;
  }
  rez.close();
}

int main()
{
  int mokiniuKiekis;
  DalyvioDuomenys mokiniai[10];
  DalyvioDuomenys mokytojas;

  skaitymas(mokiniuKiekis, mokytojas, mokiniai);
  taskuSkaiciavimas(mokiniuKiekis, mokytojas, mokiniai);
  sort(mokiniuKiekis, mokiniai);
  rez(mokiniuKiekis, mokytojas, mokiniai);

  return 0;
}
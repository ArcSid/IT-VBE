#include <fstream>
#include <iostream>
using namespace std;

struct Krepsininkas
{
  int numeris;
  int laikai[40];
  int laiku_skaicius;

  int zaidimo_laikas()
  {
    int sum = 0;
    for (int i = 0; i < laiku_skaicius; i++)
    {
      if (laikai[i] > 0)
        sum += laikai[i];
    }
    return sum;
  }

  int sedejimo_laikas()
  {
    int sum = 0;
    for (int i = 0; i < laiku_skaicius; i++)
    {
      if (laikai[i] < 0)
        sum += laikai[i];
    }
    return sum;
  }
};
void resultatas(int max, int min, Krepsininkas krepsininkai[], int pradinis_penketukas[])
{
  ofstream data("U1rez.txt");
  for (int i = 0; i < 5; i++)
  {
    data << pradinis_penketukas[i] << " ";
  }
  data << endl;
  data << krepsininkai[max].numeris << " " << krepsininkai[max].zaidimo_laikas()
       << endl;
  data << krepsininkai[min].numeris << " "
       << krepsininkai[min].sedejimo_laikas() << endl;
}

void max_zaidimo_laikas(int krepsininku_skaicius, Krepsininkas krepsininkai[],
                        int &max_indicator, int &min_indicator)
{
  int max_sk = krepsininkai[0].zaidimo_laikas();
  max_indicator = 0;
  for (int i = 0; i < krepsininku_skaicius; i++)
  {
    if (krepsininkai[i].zaidimo_laikas() > max_sk)
    {
      max_sk = krepsininkai[i].zaidimo_laikas();
      max_indicator = i;
    }
  }
  int min_sk = krepsininkai[0].zaidimo_laikas();
  min_indicator = 0;
  for (int i = 0; i < krepsininku_skaicius; i++)
  {
    if (krepsininkai[i].zaidimo_laikas() < min_sk)
    {
      min_sk = krepsininkai[i].zaidimo_laikas();
      max_indicator = i;
    }
  }
}
void sort(int krepsininku_skaicius, Krepsininkas krepsininkai[])
{
  for (int b = 0; b < krepsininku_skaicius; b++)
  {
    for (int a = 0; a < krepsininku_skaicius - 1 - b; a++)
    {
      if (krepsininkai[a].numeris > krepsininkai[a + 1].numeris)
      {
        swap(krepsininkai[a], krepsininkai[a + 1]);
      }
    }
  }
}

void pradinio_penketuko_atrinkimas(int krepsininku_skaicius,
                                   int pradinis_penketukas[],
                                   Krepsininkas krepsininkai[])
{
  int a = 0;
  for (int i = 0; i < krepsininku_skaicius; i++)
  {
    if (krepsininkai[i].laikai[0] > 0)
    {
      pradinis_penketukas[a] = krepsininkai[i].numeris;
      a++;
    }
  }
}

void skaitymas(int &skaicius, Krepsininkas krepsininkai[])
{
  ifstream data("U1.txt");
  data >> skaicius;
  for (int i = 0; i < skaicius; i++)
  {
    data >> krepsininkai[i].numeris;
    data >> krepsininkai[i].laiku_skaicius;
    for (int a = 0; a < krepsininkai[i].laiku_skaicius; a++)
    {
      data >> krepsininkai[i].laikai[a];
    }
  }
}
int main()
{
  int krepsininku_skaicius;
  Krepsininkas krepsininkai[12];
  skaitymas(krepsininku_skaicius, krepsininkai);
  sort(krepsininku_skaicius, krepsininkai);

  int pradinis_penketukas[5];
  pradinio_penketuko_atrinkimas(krepsininku_skaicius, pradinis_penketukas,
                                krepsininkai);
  int max_indicator;
  int min_indicator;
  max_zaidimo_laikas(krepsininku_skaicius, krepsininkai, max_indicator,
                     min_indicator);
  resultatas(max_indicator, min_indicator, krepsininkai, pradinis_penketukas);
}
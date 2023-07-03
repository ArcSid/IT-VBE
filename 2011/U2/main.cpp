#include <fstream>
using namespace std;

struct Grupe
{
  string vardas;
  int technika[10];
  int artistiskumas[10];
  int taskai;
};
void rez(int n, Grupe grupe[])
{
  ofstream rez("U2rez.txt");
  for (int i = 0; i < n; i++)
  {
    rez << grupe[i].vardas << " " << grupe[i].taskai;
  }
}

void sort(int kiekis, Grupe grupes[])
{
  for (int b = 0; b < kiekis; b++)
  {
    for (int a = 0; a < kiekis - b; a++)
    {
      if (grupes[a].taskai < grupes[a + 1].taskai)
      {
        swap(grupes[a], grupes[a + 1]);
      }
    }
  }
}
int tasku_skaiciavimas(int tipas[], int kiekis)
{
  int min_t = tipas[0];
  int max_t = tipas[0];
  for (int i = 0; i < kiekis; i++)
  {
    if (min_t < tipas[i])
    {
      min_t = tipas[i];
    }
    if (max_t > tipas[i])
    {
      max_t = tipas[i];
    }
  }
  int tasku_suma = 0;

  for (int i = 0; i < kiekis; i++)
  {
    tasku_suma += tipas[i];
  }

  return tasku_suma - (min_t + max_t);
}

void grupes_taskai(Grupe &grupe, int kiekis)
{
  int min_t = grupe.technika[0];
  int min_a = grupe.artistiskumas[0];
  int max_t = grupe.technika[0];
  int max_a = grupe.artistiskumas[0];

  for (int i = 0; i < kiekis; i++)
  {
    if (min_t < grupe.technika[i])
    {
      min_t = grupe.technika[i];
    }
    if (min_a < grupe.artistiskumas[i])
    {
      min_a = grupe.artistiskumas[i];
    }
    if (max_t > grupe.technika[i])
    {
      max_t = grupe.technika[i];
    }
    if (max_a > grupe.artistiskumas[i])
    {
      max_a = grupe.artistiskumas[i];
    }
  }

  int taskai_uz_techniskuma = 0;
  for (int i = 0; i < kiekis; i++)
  {
    taskai_uz_techniskuma += grupe.technika[i];
  }
  taskai_uz_techniskuma -= (min_t + max_t);

  int taskai_uz_artistiskuma = 0;
  for (int i = 0; i < kiekis; i++)
  {
    taskai_uz_artistiskuma += grupe.artistiskumas[i];
  }
  taskai_uz_artistiskuma -= (min_a + max_a);

  int tasku_suma = taskai_uz_techniskuma + taskai_uz_artistiskuma;

  grupe.taskai = tasku_suma;
}

void skaitymas(int &teiseju_kiekis, int &grupiu_kiekis, Grupe grupe[])
{

  ifstream data("U2.txt");

  data >> grupiu_kiekis;
  data >> teiseju_kiekis;

  for (int i = 0; i < grupiu_kiekis; i++)
  {
    char ch[21]; // [ 'a', 'g', 'e', '\0' ]
    data.read(ch, 20);
    grupe[i].vardas = ch;

    for (int b = 0; b < teiseju_kiekis; b++)
    {
      data >> grupe[i].technika[b];
    }
    for (int b = 0; b < teiseju_kiekis; b++)
    {
      data >> grupe[i].artistiskumas[b];
    }
  }
}

int main()
{
  Grupe grupe[100];
  int teiseju_kiekis, grupiu_kiekis;
  skaitymas(teiseju_kiekis, grupiu_kiekis, grupe);

  for (int i = 0; i < grupiu_kiekis; i++)
  {
    grupe[i].taskai =
        tasku_skaiciavimas(grupe[i].technika, teiseju_kiekis) +
        tasku_skaiciavimas(grupe[i].artistiskumas, teiseju_kiekis);
  }

  sort(grupiu_kiekis, grupe);

  rez(grupiu_kiekis, grupe);
}

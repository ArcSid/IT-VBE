#include <fstream>
using namespace std;

const int reikiamu_fig_kiekis[6] = {8, 2, 2, 2, 1, 1};

int kiek_rinkiniu(int figureles[])
{
  int kiekis = 0;
  while (1)
  {
    for (int i = 0; i < 6; i++)
    {
      if (figureles[i] - reikiamu_fig_kiekis[i] < 0)
      {
        return kiekis;
      }
      figureles[i] -= reikiamu_fig_kiekis[i];
    }
    kiekis++;
  }
}

void skaitymas(int figureles[])
{
  ifstream data("U1.txt");
  int kiekis = 0;
  int temp = 0;
  data >> kiekis;
  for (int i = 0; i < kiekis; i++)
  {
    for (int i = 0; i < 6; i++)
    {
      data >> temp;
      figureles[i] += temp;
    }
  }
}

int main()
{
  int figureles[6] = {0};
  skaitymas(figureles);
  int kiekis = kiek_rinkiniu(figureles);
  ofstream rez("U1rez.txt");
  rez << kiekis << endl;
  rez.close();
}

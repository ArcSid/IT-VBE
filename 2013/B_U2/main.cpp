#include <iostream>
#include <fstream>

using namespace std;

void skaitytiIsFailo(int &batuKiekis, int lytys[], int kojosPuse[], int dydziai[])
{
    ifstream data("U2.txt");
    data >> batuKiekis;

    for (int i = 0; i < batuKiekis; i++)
    {
        data >> lytys[i] >> kojosPuse[i] >> dydziai[i];
    }
    data.close();
}

void rastiPoruKieki(int &vyriskuKiekis, int &moteriskuKiekis, int batuKiekis, int lytys[], int kojosPuse[], int dydziai[])
{
    int panaudotuBatuKiekis = 0;
    int panaudotiBatai[100];

    for (int i = 0; i < batuKiekis; i++)
    {
        bool panaudotasElementas = false;
        for (int j = 0; j < panaudotuBatuKiekis; j++)
        {
            if (i == panaudotiBatai[j])
            {
                panaudotasElementas = true;
                break;
            }
        }

        if (panaudotasElementas)
        {
            continue;
        }

        for (int j = i; j < batuKiekis; j++)
        {
            if (lytys[i] == lytys[j] && kojosPuse[i] != kojosPuse[j] && dydziai[i] == dydziai[j])
            {
                bool panaudotasElementas = false;
                for (int k = 0; k < panaudotuBatuKiekis; k++)
                {
                    if (j == panaudotiBatai[k])
                    {
                        panaudotasElementas = true;
                        break;
                    }
                }

                if (panaudotasElementas)
                {
                    continue;
                }

                if (lytys[i] == 4)
                {
                    moteriskuKiekis++;
                }
                else
                {
                    vyriskuKiekis++;
                }

                panaudotiBatai[panaudotuBatuKiekis] = i;
                panaudotuBatuKiekis++;
                panaudotiBatai[panaudotuBatuKiekis] = j;
                panaudotuBatuKiekis++;
                break;
            }
        }
    }
}

void rez(int moteriskuKiekis, int vyriskuKiekis)
{
    ofstream rez("U2rez.txt");
    rez << vyriskuKiekis << " " << moteriskuKiekis << endl;
    rez.close();
}

int main()
{
    int batuKiekis;
    int lytys[100];
    int kojosPuse[100];
    int dydziai[100];

    skaitytiIsFailo(batuKiekis, lytys, kojosPuse, dydziai);

    int moteriskuKiekis = 0, vyriskuKiekis = 0;
    rastiPoruKieki(vyriskuKiekis, moteriskuKiekis, batuKiekis, lytys, kojosPuse, dydziai);
    rez(moteriskuKiekis, vyriskuKiekis);

    return 0;
}
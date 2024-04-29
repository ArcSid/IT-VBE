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
    int juodojoSarasoDydis = 0;
    int juodasisSarasas[100];

    for (int i = 0; i < batuKiekis; i++)
    {
        bool panaudotasElementas = false;
        for (int j = 0; j < juodojoSarasoDydis; j++)
        {
            if (i == juodasisSarasas[j])
            {
                panaudotasElementas = true;
                break;
            }
        }
        if (!panaudotasElementas)
        {
            for (int j = i; j < batuKiekis; j++)
            {
                if (lytys[i] == lytys[j] && kojosPuse[i] != kojosPuse[j] && dydziai[i] == dydziai[j])
                {
                    
                    if (lytys[i] == 4)
                    {
                        moteriskuKiekis++;
                    }
                    else
                    {
                        vyriskuKiekis++;
                    }

                    juodasisSarasas[juodojoSarasoDydis] = i;
                    juodojoSarasoDydis++;
                    juodasisSarasas[juodojoSarasoDydis] = j;
                    juodojoSarasoDydis++;
                    break;
                }
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

    int moteriskuKiekis, vyriskuKiekis;
    rastiPoruKieki(vyriskuKiekis, moteriskuKiekis, batuKiekis, lytys, kojosPuse, dydziai);
    rez(moteriskuKiekis, vyriskuKiekis);

    return 0;
}
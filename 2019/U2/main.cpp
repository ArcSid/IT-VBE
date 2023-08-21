#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Sportininkas
{
    string vardas;
    bool ar_finisavo = false;
    int identifikatorius;
    int starto_laikas_sekundemis;
    int finisavimo_laikas_sekundemis;

    int uztruko_laiko()
    {
        return finisavimo_laikas_sekundemis - starto_laikas_sekundemis;
    }

    string laikas()
    {
        int n = uztruko_laiko();
        int val = n / 3600;
        n %= 3600;
        int min = n / 60;
        n %= 60;
        string str = to_string(val) + " " + to_string(min) + " " + to_string(n);
        return str;
    }

    int suviai[4];
};

void skaitymas(int &sportininku_kiekis, int &finisavusiu_sportininku_kiekis, Sportininkas sportininkai[])
{
    ifstream data("U2.txt");
    data >> sportininku_kiekis;
    for (int i = 0; i < sportininku_kiekis; i++)
    {
        char ch[21];
        data.read(ch, 1);
        data.read(ch, 20);
        sportininkai[i].vardas = ch;
        data >> sportininkai[i].identifikatorius;
        int temp;
        int laikas = 0;
        data >> temp;
        laikas += temp * 3600;
        data >> temp;
        laikas += temp * 60;
        data >> temp;
        laikas += temp;
        sportininkai[i].starto_laikas_sekundemis = laikas;
    }
    data >> finisavusiu_sportininku_kiekis;
    int identifikatorius;
    for (int i = 0; i < finisavusiu_sportininku_kiekis; i++)
    {
        data >> identifikatorius;
        for (int j = 0; j < sportininku_kiekis; j++)
        {
            if (sportininkai[j].identifikatorius == identifikatorius)
            {
                int temp;
                int laikas = 0;
                data >> temp;
                laikas += temp * 3600;
                data >> temp;
                laikas += temp * 60;
                data >> temp;
                laikas += temp;
                sportininkai[j].finisavimo_laikas_sekundemis = laikas;
                sportininkai[j].ar_finisavo = true;
                if (identifikatorius / 100 == 1)
                {
                    data >> sportininkai[j].suviai[0];
                    data >> sportininkai[j].suviai[1];
                    break;
                }
                data >> sportininkai[j].suviai[0];
                data >> sportininkai[j].suviai[1];
                data >> sportininkai[j].suviai[2];
                data >> sportininkai[j].suviai[3];
                break;
            }
        }
    }
    data.close();
}

void suskirstymas(int kiekis, int &merginu_kiekis, int &berniuku_kiekis, Sportininkas merginos[], Sportininkas berniukai[], Sportininkas sportininkai[])
{
    for (int i = 0; i < kiekis; i++)
    {
        if (sportininkai[i].ar_finisavo)
        {
            if (sportininkai[i].identifikatorius / 100 == 1)
            {
                merginos[merginu_kiekis].starto_laikas_sekundemis = sportininkai[i].starto_laikas_sekundemis;
                merginos[merginu_kiekis].finisavimo_laikas_sekundemis = sportininkai[i].finisavimo_laikas_sekundemis;
                merginos[merginu_kiekis].identifikatorius = sportininkai[i].identifikatorius;
                merginos[merginu_kiekis].vardas = sportininkai[i].vardas;
                merginos[merginu_kiekis].suviai[0] = sportininkai[i].suviai[0];
                merginos[merginu_kiekis].suviai[1] = sportininkai[i].suviai[1];
                merginu_kiekis++;
            }
            if (sportininkai[i].identifikatorius / 100 == 2)
            {
                berniukai[berniuku_kiekis].starto_laikas_sekundemis = sportininkai[i].starto_laikas_sekundemis;
                berniukai[berniuku_kiekis].finisavimo_laikas_sekundemis = sportininkai[i].finisavimo_laikas_sekundemis;
                berniukai[berniuku_kiekis].identifikatorius = sportininkai[i].identifikatorius;
                berniukai[berniuku_kiekis].vardas = sportininkai[i].vardas;
                berniukai[berniuku_kiekis].suviai[0] = sportininkai[i].suviai[0];
                berniukai[berniuku_kiekis].suviai[1] = sportininkai[i].suviai[1];
                berniukai[berniuku_kiekis].suviai[2] = sportininkai[i].suviai[2];
                berniukai[berniuku_kiekis].suviai[3] = sportininkai[i].suviai[3];
                berniuku_kiekis++;
            }
        }
    }
}

void sort(int kiekis, Sportininkas sportininkai[])
{
    for (int i = 0; i < kiekis; i++)
    {
        for (int j = 0; j < kiekis - i - 1; j++)
        {
            if (sportininkai[i].uztruko_laiko() > sportininkai[i + 1].uztruko_laiko())
            {
                swap(sportininkai[i], sportininkai[i + 1]);
            }
            else if (sportininkai[i].uztruko_laiko() == sportininkai[i + 1].uztruko_laiko())
            {
                for (int k = 0; k < 20; k++)
                {
                    if (sportininkai[i].vardas[k] > sportininkai[i + 1].vardas[k])
                    {
                        swap(sportininkai[i], sportininkai[i + 1]);
                    }
                }
            }
        }
    }
}

void rez(string tipas, int kiekis, Sportininkas sportininkai[])
{
    ofstream rez("U2rez.txt", std::ios::app); // open the file in append mode
    rez << tipas << endl;
    for (int i = 0; i < kiekis; i++)
    {
        rez << sportininkai[i].identifikatorius << " " << sportininkai[i].vardas << sportininkai[i].laikas() << endl;
    }
}

void baudu_skaiciavimas(Sportininkas &sportininkas)
{
    int kiekis;
    if (sportininkas.identifikatorius / 100 == 1)
    {
        kiekis = 2;
    }
    else
    {
        kiekis = 4;
    }
    for (int i = 0; i < kiekis; i++)
    {
        if (sportininkas.suviai[i] < 5)
        {
            sportininkas.finisavimo_laikas_sekundemis += 60 * (5 - sportininkas.suviai[i]);
        }
    }
}

int main()
{
    Sportininkas sportininkai[30];
    int kiekis;
    int kiekis_finisavusiu;
    skaitymas(kiekis, kiekis_finisavusiu, sportininkai);
    int merginu_kiekis = 0;
    int berniuku_kiekis = 0;
    Sportininkas merginos[30];
    Sportininkas berniukai[30];

    suskirstymas(kiekis, merginu_kiekis, berniuku_kiekis, merginos, berniukai, sportininkai);

    for (int i = 0; i < merginu_kiekis; i++)
    {
        baudu_skaiciavimas(merginos[i]);
    }

    for (int i = 0; i < berniuku_kiekis; i++)
    {
        baudu_skaiciavimas(berniukai[i]);
    }

    sort(merginu_kiekis, merginos);
    sort(merginu_kiekis, merginos);
    sort(berniuku_kiekis, berniukai);
    sort(berniuku_kiekis, berniukai);

    rez("Merginos", merginu_kiekis, merginos);
    rez("Vaikinai", berniuku_kiekis, berniukai);

    return 0;
}
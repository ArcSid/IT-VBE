#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

struct Mokinys
{
    int klase;
    int zingsnio_ilgis;
    int zingsniai[7];

    bool ar_ejo_kasdiena()
    {
        for (int i = 0; i < 7; i++)
        {
            if (zingsniai[i] == 0)
            {
                return false;
            }
        }
        return true;
    }
};

struct Klase
{
    int indikatorius;
    int mokiniu_kiekis = 0;
    double nueitas_atstumas = 0;
};

void skaitymas(int &mokiniu_kiekis, Mokinys mokiniai[])
{
    ifstream data("U1.txt");
    data >> mokiniu_kiekis;
    for (int i = 0; i < mokiniu_kiekis; i++)
    {
        data >> mokiniai[i].klase;
        data >> mokiniai[i].zingsnio_ilgis;
        for (int j = 0; j < 7; j++)
        {
            data >> mokiniai[i].zingsniai[j];
        }
    }
    data.close();
}

void klases_kategorijos(int mokiniu_kiekis, Mokinys mokiniai[], vector<Klase> &klases)
{
    // eina per mokinis
    for (int i = 0; i < mokiniu_kiekis; i++)
    {
        // tikrina ar mokinys kasdien ejo
        if (!mokiniai[i].ar_ejo_kasdiena())
        {
            continue;
        }

        // tikrina ar klase egzistuoja
        int klase_i = -1;
        for (int j = 0; j < klases.size(); j++)
        {
            if (mokiniai[i].klase == klases[j].indikatorius)
            {
                klase_i = j;
                break;
            }
        }

        // jeigu neranda klases, sukuriama nauja klase
        if (klase_i == -1)
        {
            Klase temp_klase;
            temp_klase.indikatorius = mokiniai[i].klase;
            klases.push_back(temp_klase);
            klase_i = klases.size() - 1;
        }

        // klase_i rodo rasta arba naujai sukurta klase ir ten prideda bendrus duomenis, t.y. mok. kiekis, zingsniu ilgis
        klases[klase_i].mokiniu_kiekis++;
        int zingsniau_kiekis = 0;

        for (int k = 0; k < 7; k++)
        {
            zingsniau_kiekis += mokiniai[i].zingsniai[k];
        }
        double atstumas = double(zingsniau_kiekis * mokiniai[i].zingsnio_ilgis) / 100000;
        klases[klase_i].nueitas_atstumas += atstumas;
    }
}

void rez(vector<Klase> klases)
{
    ofstream rez("U1rez.txt");
    for (int i = 0; i < klases.size(); i++)
    {
        rez << klases[i].indikatorius << " " << klases[i].mokiniu_kiekis << " " << setprecision(4) << klases[i].nueitas_atstumas << endl;
    }
    rez.close();
}

int main()
{
    int mokiniu_kiekis;
    Mokinys mokiniai[50];
    vector<Klase> klases;
    skaitymas(mokiniu_kiekis, mokiniai);
    klases_kategorijos(mokiniu_kiekis, mokiniai, klases);
    rez(klases);
    return 0;
}
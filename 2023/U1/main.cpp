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
    // eina per visus mokinius
    for (int i = 0; i < mokiniu_kiekis; i++)
    {
        // ziuri tik tuos kurie ejo kasdien
        if (mokiniai[i].ar_ejo_kasdiena())
        {
            // paprastas naujo vektoriaus elemento atrinkimas pagal mokinius kurie ejo
            bool ar_nauja_klase = true;

            // eina per visas egzistuojancias klases
            for (int j = 0; j < klases.size(); j++)
            {

                // jeigu rado jau egzistuojancia klase
                if (mokiniai[i].klase == klases[j].indikatorius)
                {
                    // prideda mokini prie mokiniu kiekio

                    klases[j].mokiniu_kiekis++;

                    // randa koki atstuma mokinys nuejo kilometrais
                    int zingsniau_kiekis = 0;

                    for (int k = 0; k < 7; k++)
                    {
                        zingsniau_kiekis += mokiniai[i].zingsniai[k];
                    }
                    double atstumas = double(zingsniau_kiekis * mokiniai[i].zingsnio_ilgis) / 100000;
                    klases[j].nueitas_atstumas += atstumas;

                    // indikuoja kad naujos klases kurti nereikia
                    ar_nauja_klase = false;
                }
            }

            // jeigu nerado klases atitinkancios kasdien ejusi mokini, sukuriama nauja klase
            if (ar_nauja_klase)
            {
                // sukuriama nauja klase ir i ja idedami mokinio duomenys
                Klase temp_klase;
                temp_klase.indikatorius = mokiniai[i].klase;
                temp_klase.mokiniu_kiekis++;

                // i laikina klase idedama ir nueitas kelias
                int zingsniau_kiekis = 0;

                for (int k = 0; k < 7; k++)
                {
                    zingsniau_kiekis += mokiniai[i].zingsniai[k];
                }
                double atstumas = double(zingsniau_kiekis * mokiniai[i].zingsnio_ilgis) / 100000;
                temp_klase.nueitas_atstumas += atstumas;
                // laikina klase pridedama prie visu klasiu
                klases.push_back(temp_klase);
            }
        }
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
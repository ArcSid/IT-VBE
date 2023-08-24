#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Mokinys
{
    string vardas;
    string megstamiausias_dalykas;
    vector<int> pazymys;
    int vidurkis()
    {
        int sum = 0;
        for (int i = 0; i < pazymys.size(); i++)
        {
            sum += pazymys[i];
        }
        return sum / pazymys.size();
    }
};

struct Dalykas
{
    string pavadinimas;
    vector<string> mokiniai;
    vector<int> vidurkiai;
};

void skaitymas(int &mokiniu_kiekis, Mokinys mokiniai[])
{
    ifstream data("U2.txt");
    string str;
    data >> mokiniu_kiekis;
    for (int i = 0; i < mokiniu_kiekis; i++)
    {
        data >> str;
        mokiniai[i].vardas = str;
        data >> str;
        mokiniai[i].megstamiausias_dalykas = str;
        int pazymiu_kiekis;
        data >> pazymiu_kiekis;
        for (int j = 0; j < pazymiu_kiekis; j++)
        {
            int temp;
            data >> temp;
            mokiniai[i].pazymys.push_back(temp);
        }
    }
    data.close();
}

void pamoku_atrinkimas(int &dalyku_kiekis, int mokiniu_kiekis, Mokinys mokiniai[], vector<Dalykas> &dalykai)
{
    for (int i = 0; i < mokiniu_kiekis; i++)
    {
        int atitiko_dalyka = false;
        Dalykas laikinas_dalykas;
        for (int j = 0; j < dalykai.size(); j++)
        {
            if (dalykai[j].pavadinimas == mokiniai[i].megstamiausias_dalykas)
            {
                dalykai[j].mokiniai.push_back(mokiniai[i].vardas);
                dalykai[j].vidurkiai.push_back(mokiniai[i].vidurkis());
                atitiko_dalyka = true;
                break;
            }
        }
        if (!atitiko_dalyka)
        {
            laikinas_dalykas.pavadinimas = mokiniai[i].megstamiausias_dalykas;
            laikinas_dalykas.mokiniai.push_back(mokiniai[i].vardas);
            laikinas_dalykas.vidurkiai.push_back(mokiniai[i].vidurkis());
            dalykai.push_back(laikinas_dalykas);
        }
    }
}

void mokiniu_atrinkimas(vector<Dalykas> dalykai, vector<Dalykas> &atrinkti_dalykai)
{
    for (int i = 0; i < dalykai.size(); i++)
    {
        Dalykas laikinas_dalykas;
        laikinas_dalykas.pavadinimas = dalykai[i].pavadinimas;
        atrinkti_dalykai.push_back(laikinas_dalykas);
        for (int j = 0; j < dalykai[i].vidurkiai.size(); j++)
        {
            if (dalykai[i].vidurkiai[j] >= 9)
            {
                atrinkti_dalykai[i].mokiniai.push_back(dalykai[i].mokiniai[j]);
                atrinkti_dalykai[i].vidurkiai.push_back(dalykai[i].vidurkiai[j]);
            }
        }
    }
}
void sort(vector<Dalykas> &dalykai)
{
    int n = dalykai.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (dalykai[j].mokiniai.size() < dalykai[j + 1].mokiniai.size() || (dalykai[j].mokiniai.size() == dalykai[j + 1].mokiniai.size()) && string(dalykai[j].pavadinimas) < string(dalykai[j + 1].pavadinimas))
            {
                swap(dalykai[j], dalykai[j + 1]);
            }
        }
    }
}

void rez(vector<Dalykas> dalykai)
{
    ofstream rez("U2rez.txt");
    int dalyku_kiekis = 0;
    for (int i = 0; i < dalykai.size(); i++)
    {
        if (dalykai[i].mokiniai.size() > 0)
        {
            dalyku_kiekis++;
            rez << dalykai[i].pavadinimas << " " << dalykai[i].mokiniai.size() << endl;
            for (int j = 0; j < dalykai[i].mokiniai.size(); j++)
            {
                rez << dalykai[i].mokiniai[j] << endl;
            }
        }
    }
    if (dalyku_kiekis == 0)
    {
        rez << "Neatitinka vidurkis" << endl;
    }
    rez.close();
}

int main()
{
    int mokiniu_kiekis;
    Mokinys mokiniai[50];
    int dalyku_kiekis;
    vector<Dalykas> dalykai;

    skaitymas(mokiniu_kiekis, mokiniai);

    pamoku_atrinkimas(dalyku_kiekis, mokiniu_kiekis, mokiniai, dalykai);

    vector<Dalykas> atrinkti_mokiniai_ir_dalykai;

    mokiniu_atrinkimas(dalykai, atrinkti_mokiniai_ir_dalykai);

    sort(atrinkti_mokiniai_ir_dalykai);

    rez(atrinkti_mokiniai_ir_dalykai);

    return 0;
}
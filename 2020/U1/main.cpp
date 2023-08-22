#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Gele
{
    int identifikatorius;

    int zydejimo_pradzia_menesis;
    int zydejimo_pabaiga_menesis;
    int zydejimo_pradzia_diena;
    int zydejimo_pabaiga_diena;

    int zydejimo_pradzia()
    {
        if (zydejimo_pradzia_menesis == 6)
        {
            return zydejimo_pradzia_diena;
        }
        if (zydejimo_pradzia_menesis == 7)
        {
            return zydejimo_pradzia_diena + 31;
        }
        return zydejimo_pradzia_diena + 61;
    }

    int zydejimo_pabaiga()
    {
        if (zydejimo_pabaiga_menesis == 6)
        {
            return zydejimo_pabaiga_diena;
        }
        if (zydejimo_pabaiga_menesis == 7)
        {
            return zydejimo_pabaiga_diena + 31;
        }
        return zydejimo_pabaiga_diena + 61;
    }
};

struct Dienos
{
    vector<int> geliu_identifikatorius;
};

void skaitymas(int &kiekis, Gele geles[])
{
    ifstream data("U1.txt");
    data >> kiekis;
    for (int i = 0; i < kiekis; i++)
    {
        data >> geles[i].identifikatorius;
        data >> geles[i].zydejimo_pradzia_menesis;
        data >> geles[i].zydejimo_pradzia_diena;
        data >> geles[i].zydejimo_pabaiga_menesis;
        data >> geles[i].zydejimo_pabaiga_diena;
    }
    data.close();
}

int max_zydejimo_pradzia(int &max_zydinciu, Dienos dienos[])
{
    int max_i = 1;
    for (int i = 1; i < 93; i++)
    {
        if (dienos[i].geliu_identifikatorius.size() > max_zydinciu)
        {
            max_zydinciu = dienos[i].geliu_identifikatorius.size();
            max_i = i;
        }
    }
    return max_i;
}

int max_zydejimo_pabaiga(int max_zydinciu, int max_pradzia, Dienos dienos[])
{
    for (int i = max_pradzia; i < 93; i++)
    {
        if (dienos[i].geliu_identifikatorius.size() < max_zydinciu)
        {

            return i - 1;
        }
    }
    return 92;
}

void sudeti_dienas(int kiekis, Gele geles[], Dienos dienos[])
{
    for (int i = 0; i < kiekis; i++)
    {
        for (int j = geles[i].zydejimo_pradzia(); j <= geles[i].zydejimo_pabaiga(); j++)
        {
            dienos[j].geliu_identifikatorius.push_back(geles[i].identifikatorius);
        }
    }
}

void rez(int zydi_max, int zydejimo_pradzia, int zydejimo_pabaiga)
{
    ofstream rez("U1rez.txt");
    rez << zydi_max << endl;
    bool converted = false;

    if (zydejimo_pradzia >= 62)
    {
        rez << "8 " << zydejimo_pradzia - 62 << endl;
        converted = true;
    }
    if (!converted && zydejimo_pradzia >= 31)
    {
        rez << "7 " << zydejimo_pradzia - 31 << endl;
        converted = true;
    }
    if (!converted)
    {
        rez << "6 " << zydejimo_pradzia << endl;
    }

    if (zydejimo_pabaiga >= 62)
    {
        rez << "8 " << zydejimo_pabaiga - 62 << endl;
        rez.close();
        return;
    }
    if (zydejimo_pabaiga >= 31)
    {
        rez << "7 " << zydejimo_pabaiga - 31 << endl;
        rez.close();
        return;
    }
    rez << "6 " << zydejimo_pabaiga << endl;
    rez.close();
}

int main()
{
    int kiekis;
    Gele geles[30];
    Dienos dienos[93];
    int max_zydi = 0;
    skaitymas(kiekis, geles);
    sudeti_dienas(kiekis, geles, dienos);
    int zydejimo_pradzia = max_zydejimo_pradzia(max_zydi, dienos);
    int zydejimo_pabaiga = max_zydejimo_pabaiga(max_zydi, zydejimo_pradzia, dienos);
    rez(max_zydi, zydejimo_pradzia, zydejimo_pabaiga);
    return 0;
}
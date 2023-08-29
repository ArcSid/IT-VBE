#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int vasaros_diena(int menesis, int diena)
{
    if (menesis == 6)
    {
        return diena;
    }
    if (menesis == 7)
    {
        return diena + 31;
    }
    return diena + 61;
}

struct Gele
{
    int zydejimo_pradzia;
    int zydejimo_pabaiga;
};

void skaitymas(int &kiekis, Gele geles[])
{
    ifstream data("U1.txt");
    data >> kiekis;
    int f;
    int menesis, diena;

    for (int i = 0; i < kiekis; i++)
    {
        data >> f;
        data >> menesis;
        data >> diena;
        geles[i].zydejimo_pradzia = vasaros_diena(menesis, diena);
        data >> menesis;
        data >> diena;
        geles[i].zydejimo_pabaiga = vasaros_diena(menesis, diena);
    }
}

int max_zydejimo_pradzia(int &max_zydinciu, int dienos[])
{

    int max_i = 1;

    for (int i = 0; i < 92; i++)
    {

        if (dienos[i] > max_zydinciu)
        {
            max_zydinciu = dienos[i];
            max_i = i;
        }
    }

    return max_i;
}

int max_zydejimo_pabaiga(int max_zydinciu, int max_pradzia, int dienos[])
{
    for (int i = max_pradzia; i < 93; i++)
    {
        if (dienos[i] < max_zydinciu)
        {
            return i - 1;
        }
    }
    return 92;
}

void sudeti_dienas(int kiekis, Gele geles[], int dienos[])
{
    for (int i = 0; i < kiekis; i++)
    {
        for (int j = geles[i].zydejimo_pradzia; j <= geles[i].zydejimo_pabaiga; j++)
        {
            dienos[j]++;
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
    int dienos[93] = {0};
    int max_zydi = 0;

    skaitymas(kiekis, geles);
    sudeti_dienas(kiekis, geles, dienos);

    int zydejimo_pradzia = max_zydejimo_pradzia(max_zydi, dienos);
    int zydejimo_pabaiga = max_zydejimo_pabaiga(max_zydi, zydejimo_pradzia, dienos);

    rez(max_zydi, zydejimo_pradzia, zydejimo_pabaiga);
    return 0;
}
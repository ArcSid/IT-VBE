#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int convert_month_to_days(int m)
{
    if (m == 2)
    {
        return 31;
    }
    if (m == 3)
    {
        return 59;
    }
    if (m == 4)
    {
        return 90;
    }
    if (m == 5)
    {
        return 120;
    }
    if (m == 6)
    {
        return 151;
    }
    if (m == 7)
    {
        return 181;
    }
    if (m == 8)
    {
        return 212;
    }
    if (m == 9)
    {
        return 243;
    }
    if (m == 10)
    {
        return 273;
    }
    if (m == 11)
    {
        return 303;
    }
    if (m == 12)
    {
        return 334;
    }
    return 0;
}

struct Zmogus
{
    string vardas;

    int gimimo_metai;
    int gimimo_menesis;
    int gimimo_diena;

    int mirties_metai;
    int mirties_menesis;
    int mirties_diena;

    int gyveno()
    {
        return (mirties_metai * 365 + mirties_diena + convert_month_to_days(mirties_menesis)) - (gimimo_metai * 365 + gimimo_diena + convert_month_to_days(gimimo_menesis));
    }
};

void skaitymas(vector<Zmogus> &zmones)
{
    ifstream data("U2.txt");
    int zmoniu_kiekis;
    data >> zmoniu_kiekis;
    for (int i = 0; i < zmoniu_kiekis; i++)
    {
        char ch[26] = {0};
        data.read(ch, 1);
        data.read(ch, 25);
        Zmogus laikinas_zmogus;
        string temp = ch;
        laikinas_zmogus.vardas = temp;
        cout << "'" << temp << "'\n";
        data >> laikinas_zmogus.gimimo_metai >> laikinas_zmogus.gimimo_menesis >> laikinas_zmogus.gimimo_diena;
        data >> laikinas_zmogus.mirties_metai >> laikinas_zmogus.mirties_menesis >> laikinas_zmogus.mirties_diena;
        // cout << laikinas_zmogus.gimimo_metai << " " << laikinas_zmogus.gimimo_menesis << " " << laikinas_zmogus.gimimo_diena << " " << laikinas_zmogus.mirties_metai << " " << laikinas_zmogus.mirties_menesis << " " << laikinas_zmogus.mirties_diena << "     " << laikinas_zmogus.gyveno() << endl;
        zmones.push_back(laikinas_zmogus);
    }
}

void rez(vector<Zmogus> zmones)
{
    ofstream rez("U2rez.txt");
    for (int i = 0; i < zmones.size(); i++)
    {
        // cout << "'" << zmones[i].vardas << "'\n";
        rez << zmones[i].vardas << zmones[i].gimimo_metai << " " << zmones[i].gimimo_menesis << " " << zmones[i].gimimo_diena << " " << zmones[i].mirties_metai << " " << zmones[i].mirties_menesis << " " << zmones[i].mirties_diena << " " << zmones[i].gyveno() << endl;
    }
}

int main()
{
    vector<Zmogus> zmones;
    skaitymas(zmones);
    rez(zmones);
}

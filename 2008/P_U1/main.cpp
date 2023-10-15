#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int date_to_days(int day, int month, int year)
{
    int month_days[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 303, 334};
    int year_to_days = year * 365;
    int month_to_days = month_days[month - 1];
    return year_to_days + month_to_days + day;
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
        return date_to_days(mirties_diena, mirties_menesis, mirties_metai) - date_to_days(gimimo_diena, gimimo_menesis, gimimo_metai);
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
        laikinas_zmogus.vardas = ch;
        data >> laikinas_zmogus.gimimo_metai >> laikinas_zmogus.gimimo_menesis >> laikinas_zmogus.gimimo_diena;
        data >> laikinas_zmogus.mirties_metai >> laikinas_zmogus.mirties_menesis >> laikinas_zmogus.mirties_diena;
        zmones.push_back(laikinas_zmogus);
    }
}

void rez(vector<Zmogus> zmones)
{
    ofstream rez("U2rez.txt");
    for (int i = 0; i < zmones.size(); i++)
    {
        rez << zmones[i].vardas << zmones[i].gimimo_metai << " " << zmones[i].gimimo_menesis << " " << zmones[i].gimimo_diena << " " << zmones[i].mirties_metai << " " << zmones[i].mirties_menesis << " " << zmones[i].mirties_diena << " " << zmones[i].gyveno() << endl;
    }
}

int main()
{
    vector<Zmogus> zmones;

    skaitymas(zmones);

    rez(zmones);
}

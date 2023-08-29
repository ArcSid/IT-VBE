#include <iostream>
#include <fstream>
using namespace std;
struct Zvejas
{
    string vardas;
    int pagautas_zuvu_kiekis;
    string pagautos_zuvys[30];
    int zuvu_mase[30];
    int surinkti_taskai;
};

struct Zuvis
{
    string pavadinimas;
    int taskai;
    int kiekis_kilogramais = 0;
};

void skaitymas(int &zveju_kiekis, int &zuvu_kiekis, Zvejas zvejai[], Zuvis zuvys[])
{
    ifstream data("U2.txt");
    data >> zveju_kiekis;
    for (int i = 0; i < zveju_kiekis; i++)
    {
        char ch[21];
        data.read(ch, 1);
        data.read(ch, 20);
        zvejai[i].vardas = ch;
        data >> zvejai[i].pagautas_zuvu_kiekis;
        for (int j = 0; j < zvejai[i].pagautas_zuvu_kiekis; j++)
        {
            data.read(ch, 1);
            data.read(ch, 20);
            zvejai[i].pagautos_zuvys[j] = ch;
            data >> zvejai[i].zuvu_mase[j];
        }
    }
    data >> zuvu_kiekis;
    for (int i = 0; i < zuvu_kiekis; i++)
    {
        char ch[21];
        data.read(ch, 1);
        data.read(ch, 20);
        zuvys[i].pavadinimas = ch;
        data >> zuvys[i].taskai;
    }
    data.close();
}

int surinkti_taskai(Zvejas zvejas, int zuvu_kiekis, Zuvis zuvys[])
{
    int taskai = 0;
    for (int i = 0; i < zvejas.pagautas_zuvu_kiekis; i++)
    {
        for (int j = 0; j < zuvu_kiekis; j++)
        {
            if (zvejas.pagautos_zuvys[i] == zuvys[j].pavadinimas)
            {
                taskai += zuvys[j].taskai;
                zuvys[j].kiekis_kilogramais += zvejas.zuvu_mase[i];
                if (zvejas.zuvu_mase[i] >= 300)
                {
                    taskai += 30;
                    break;
                }
                if (zvejas.zuvu_mase[i] >= 200)
                {
                    taskai += 20;
                    break;
                }
                taskai += 10;
                break;
            }
        }
    }
    return taskai;
}

void sort_zvejai(int kiekis, Zvejas zvejai[])
{
    for (int i = 0; i < kiekis; i++)
    {
        for (int j = 0; j < kiekis - 1 - i; j++)
        {
            if (zvejai[j].surinkti_taskai < zvejai[j + 1].surinkti_taskai || (zvejai[j].surinkti_taskai == zvejai[j + 1].surinkti_taskai && string(zvejai[j].vardas) > string(zvejai[j + i].vardas)))
            {
                swap(zvejai[j], zvejai[j + 1]);
            }
        }
    }
}

void sort_zuvys(int kiekis, Zuvis zuvys[])
{
    for (int i = 0; i < kiekis; i++)
    {
        for (int j = 0; j < kiekis - 1 - i; j++)
        {
            if (zuvys[j].kiekis_kilogramais < zuvys[j + 1].kiekis_kilogramais || (zuvys[j].kiekis_kilogramais == zuvys[j + 1].kiekis_kilogramais && string(zuvys[j].pavadinimas) > string(zuvys[j + 1].pavadinimas)))
            {
                swap(zuvys[j], zuvys[j + 1]);
            }
        }
    }
}

void rez(int zveju_kiekis, Zvejas zvejai[], int zuvu_kiekis, Zuvis zuvys[])
{
    ofstream rez("U2rez.txt");
    rez << "Dalyviai" << endl;
    for (int i = 0; i < zveju_kiekis; i++)
    {
        rez << zvejai[i].vardas << zvejai[i].surinkti_taskai << endl;
    }
    rez << "Laimikis" << endl;
    for (int i = 0; i < zuvu_kiekis; i++)
    {
        rez << zuvys[i].pavadinimas << zuvys[i].kiekis_kilogramais << endl;
    }
    rez.close();
}

int main()
{
    int zveju_kiekis;
    int zuvu_kiekis;
    Zvejas zvejai[30];
    Zuvis zuvys[30];
    skaitymas(zveju_kiekis, zuvu_kiekis, zvejai, zuvys);

    for (int i = 0; i < zveju_kiekis; i++)
    {
        zvejai[i].surinkti_taskai = surinkti_taskai(zvejai[i], zuvu_kiekis, zuvys);
    }

    sort_zvejai(zveju_kiekis, zvejai);

    sort_zuvys(zuvu_kiekis, zuvys);

    rez(zveju_kiekis, zvejai, zuvu_kiekis, zuvys);
    return 0;
}
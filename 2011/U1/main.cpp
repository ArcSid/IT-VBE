#include <iostream>
#include <fstream>

using namespace std;
void resultatas(int poru_kiekis_v, int poru_kiekis_m, int liko_mot, int liko_vyr)
{
    ofstream rez("U1rez.txt");
    rez << poru_kiekis_v << endl;
    rez << poru_kiekis_m << endl;
    rez << liko_mot << endl;
    rez << liko_vyr << endl;
}
void poravimas(int kiekis, int &poru_kiekis_v, int &poru_kiekis_m, int &liko_mot, int &liko_vyr, int lyt[], int ranka[], int dydis[])
{

    int deleted[100] = {0};
    bool randa = false;

    for (int i = 0; i < kiekis; i++)
    {
        if (deleted[i] == 1)
            continue;

        randa = false;

        for (int j = i + 1; j < kiekis; j++)
        {
            if (deleted[j] == 1)
                continue;

            if ((dydis[i] == dydis[j]) && (lyt[i] == lyt[j]) && (ranka[i] != ranka[j]))
            {
                deleted[i] = 1;
                deleted[j] = 1;
                if (lyt[i] == 3)
                    poru_kiekis_v++;
                if (lyt[i] == 4)
                    poru_kiekis_m++;
                randa = true;
                break;
            }
        }

        if (!randa)
        {
            if (lyt[i] == 3)
                liko_vyr++;
            if (lyt[i] == 4)
                liko_mot++;
            deleted[i] = 1;
        }
    }
}

void skaitymas(int &kiekis, int lyt[], int ranka[], int dydis[])
{
    ifstream data("U1.txt");
    data >> kiekis;
    for (int i = 0; i < kiekis; i++)
    {
        data >> lyt[i] >> ranka[i] >> dydis[i];
    }
}

int main()
{

    int lyt[100];
    int ranka[100];
    int dydis[100];
    int pirstiniu_kiekis = 0;
    int poru_kiekis_v = 0;
    int poru_kiekis_m = 0;
    int liko_mot = 0;
    int liko_vyr = 0;
    skaitymas(pirstiniu_kiekis, lyt, ranka, dydis);
    poravimas(pirstiniu_kiekis, poru_kiekis_v, poru_kiekis_m, liko_mot, liko_vyr, lyt, ranka, dydis);
    resultatas(poru_kiekis_v, poru_kiekis_m, liko_mot, liko_vyr);
}
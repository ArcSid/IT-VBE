#include <iostream>
#include <fstream>
using namespace std;

struct Slidininkas
{
    string vardas;
    bool finisavo = false;
    int pradinis_laikas_sekundemis;
    int pabaigos_laikas_sekundemis;

    int kiek_laiko_sugaiso_sekundemis()
    {
        return pabaigos_laikas_sekundemis - pradinis_laikas_sekundemis;
    }

    int sugaiso_minuciu()
    {
        return kiek_laiko_sugaiso_sekundemis() / 60;
    }
    int sugaiso_sekundziu()
    {
        return kiek_laiko_sugaiso_sekundemis() % 60;
    }
};

void skaitymas(int &slidininku_kiekis, int &finisavusiu_kiekis, Slidininkas slidininkai[])
{
    ifstream data("U2.txt");
    data >> slidininku_kiekis;
    for (int i = 0; i < slidininku_kiekis; i++)
    {
        char ch[21] = {' '};
        data.read(ch, 1);
        data.read(ch, 20);
        slidininkai[i].vardas = ch;
        int temp = 0;
        int laikas = 0;

        data >> temp;
        laikas += temp * 3600;
        data >> temp;
        laikas += temp * 60;
        data >> temp;
        laikas += temp;
        slidininkai[i].pradinis_laikas_sekundemis = laikas;
    }
    data >> finisavusiu_kiekis;
    for (int i = 0; i < finisavusiu_kiekis; i++)
    {
        char ch[21] = {' '};
        data.read(ch, 1);
        data.read(ch, 20);
        bool atitiko_slidininka = false;
        for (int j = 0; j < slidininku_kiekis; j++)
        {
            if (ch == slidininkai[j].vardas)
            {
                slidininkai[j].finisavo = true;
                int temp = 0;
                int laikas = 0;

                data >> temp;
                laikas += temp * 3600;
                data >> temp;
                laikas += temp * 60;
                data >> temp;
                laikas += temp;
                slidininkai[j].pabaigos_laikas_sekundemis = laikas;
                atitiko_slidininka = true;
                break;
            }
        }
        if (!atitiko_slidininka)
        {
            int temp;
            data >> temp >> temp >> temp;
            slidininkai[i].pabaigos_laikas_sekundemis = temp;
        }
    }
}

void sort(int kiekis, Slidininkas slidininkai[])
{
    for (int i = 0; i < kiekis; i++)
    {
        for (int j = 0; j < kiekis - 1 - i; j++)
        {
            if (slidininkai[i].kiek_laiko_sugaiso_sekundemis() > slidininkai[i + 1].kiek_laiko_sugaiso_sekundemis())
            {
                swap(slidininkai[i], slidininkai[i + 1]);
            }
            else if (slidininkai[i].kiek_laiko_sugaiso_sekundemis() == slidininkai[i + 1].kiek_laiko_sugaiso_sekundemis())
            {
                for (int k = 0; k < 20; k++)
                {
                    if (slidininkai[i].vardas[k] > slidininkai[i + 1].vardas[k])
                    {
                        swap(slidininkai[i], slidininkai[i + 1]);
                        break;
                    }
                }
            }
        }
    }
}

void rez(int kiekis, Slidininkas slidininkai[])
{
    ofstream rez("U2rez.txt");
    for (int i = 0; i < kiekis; i++)
    {
        rez << slidininkai[i].vardas << slidininkai[i].sugaiso_minuciu() << " " << slidininkai[i].sugaiso_sekundziu() << endl;
    }
}

int main()
{
    int slidininku_kiekis;
    int finisavusiu_slidininku_kiekis;
    Slidininkas slidininkai[30];

    skaitymas(slidininku_kiekis, finisavusiu_slidininku_kiekis, slidininkai);
    Slidininkas finisave_slidininkai[30];

    int temp = 0;

    for (int i = 0; i < slidininku_kiekis; i++)
    {
        if (slidininkai[i].finisavo)
        {
            finisave_slidininkai[temp].vardas = slidininkai[i].vardas;
            finisave_slidininkai[temp].finisavo = true;
            finisave_slidininkai[temp].pradinis_laikas_sekundemis = slidininkai[i].pradinis_laikas_sekundemis;
            finisave_slidininkai[temp].pabaigos_laikas_sekundemis = slidininkai[i].pabaigos_laikas_sekundemis;
            temp++;
        }
    }
    sort(finisavusiu_slidininku_kiekis, finisave_slidininkai);
    sort(finisavusiu_slidininku_kiekis, finisave_slidininkai);

    rez(finisavusiu_slidininku_kiekis, finisave_slidininkai);
    return 0;
}
#include <iostream>
#include <fstream>
using namespace std;

struct Diena
{
    int indikatorius;

    int sugaiso_ryte;
    int sugaiso_vakare;

    bool bego_ryte = false;
    bool bego_vakare = false;

    int begimo_laikas()
    {
        return sugaiso_ryte + sugaiso_vakare;
    }
};

int kiek_sugaiso_laiko(int a, int b, int c, int d)
{
    return (c * 60 + d) - (a * 60 + b);
}

void skaitymas(int &dienu_kiekis, Diena dienos[])
{
    ifstream data("U1.txt");
    data >> dienu_kiekis;
    int valanda, minute;
    int valanda_1, minute_1;
    for (int i = 0; i < dienu_kiekis; i++)
    {
        data >> dienos[i].indikatorius;
        data >> valanda >> minute;
        data >> valanda_1 >> minute_1;

        if (valanda + minute + valanda_1 + minute_1 != 0)
        {
            dienos[i].bego_ryte = true;
        }

        dienos[i].sugaiso_ryte = kiek_sugaiso_laiko(valanda, minute, valanda_1, minute_1);
        data >> valanda >> minute;
        data >> valanda_1 >> minute_1;

        if (valanda + minute + valanda_1 + minute_1 != 0)
        {
            dienos[i].bego_vakare = true;
        }

        dienos[i].sugaiso_vakare = kiek_sugaiso_laiko(valanda, minute, valanda_1, minute_1);
    }
    data.close();
}

int min_laikas(int kiekis, Diena dienos[])
{
    int min_laikas = dienos[0].begimo_laikas();
    for (int i = 0; i < kiekis; i++)
    {
        if (!dienos[i].bego_ryte || !dienos[i].bego_vakare)
        {
            continue;
        }
        if (min_laikas > dienos[i].begimo_laikas())
        {
            min_laikas = dienos[i].begimo_laikas();
        }
    }
    return min_laikas;
}

void rez(int min, int kiekis, Diena dienos[])
{
    ofstream rez("U1rez.txt");
    rez << "Minimalus laikas" << endl;
    rez << min << endl;
    rez << "Dienos" << endl;
    for (int i = 0; i < kiekis; i++)
    {
        if (!dienos[i].bego_ryte || !dienos[i].bego_vakare)
        {
            continue;
        }
        if (dienos[i].begimo_laikas() == min)
        {
            rez << dienos[i].indikatorius << " ";
        }
    }
    rez.close();
}

int main()
{
    int dienu_kiekis;
    Diena dienos[31];
    skaitymas(dienu_kiekis, dienos);

    rez(min_laikas(dienu_kiekis, dienos), dienu_kiekis, dienos);
    return 0;
}
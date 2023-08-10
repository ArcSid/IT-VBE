#include <iostream>
#include <fstream>
using namespace std;
void skaitymas(int juosteles[])
{
    ifstream data("U1.txt");

    int kruveliu_sk;
    data >> kruveliu_sk;

    for (int i = 0; i < kruveliu_sk; i++)
    {

        int spalvos_skaicius;
        string spalvos_str;
        char temp[3];
        data.read(temp, 1);
        data.read(temp, 2);
        spalvos_str = temp;

        data >> spalvos_skaicius;

        if (spalvos_str == "G ")
        {
            juosteles[0] += spalvos_skaicius;
            continue;
        }
        if (spalvos_str == "Z ")
        {
            juosteles[1] += spalvos_skaicius;
            continue;
        }
        if (spalvos_str == "R ")
        {
            juosteles[2] += spalvos_skaicius;
            continue;
        }
    }
    data.close();
}

int veleveliu_kiekis(int juosteles[])
{
    int kiekis = 0;
    while (1)
    {
        if (juosteles[0] - 2 >= 0)
        {
            if (juosteles[1] - 2 >= 0)
            {
                if (juosteles[2] - 2 >= 0)
                {
                    kiekis++;
                    juosteles[0] -= 2;
                    juosteles[1] -= 2;
                    juosteles[2] -= 2;
                    continue;
                }
            }
        }
        break;
    }
    return kiekis;
}

void rez(int kiekis, int juosteles[])
{
    ofstream rez("U1rez.txt");
    rez << kiekis << endl;
    rez << "G = " << juosteles[0] << endl;
    rez << "Z = " << juosteles[1] << endl;
    rez << "R = " << juosteles[2] << endl;
    rez.close();
}

int main()
{
    int juosteles[3] = {0};

    skaitymas(juosteles);

    rez(veleveliu_kiekis(juosteles), juosteles);

    return 0;
}
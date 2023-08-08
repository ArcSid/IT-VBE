#include <iostream>
#include <fstream>
using namespace std;

int sunkiausiuos_kuprines_svoris()
{
    ifstream data("U1.txt");
    int kupriniu_kiekis;
    data >> kupriniu_kiekis;
    int temp_1 = 0;
    int temp_2;
    data >> temp_2;
    for (int i = 0; i < kupriniu_kiekis - 1; i++)
    {
        data >> temp_1;
        if (temp_1 > temp_2)
        {
            temp_2 = temp_1;
        }
    }
    data.close();
    return temp_2;
}

int du_kartus_lengvesniu_kupriniu_radimas(int sunkiausia)
{
    int kiekis = 0;
    ifstream data("U1.txt");
    int kupriniu_kiekis;
    data >> kupriniu_kiekis;
    int temp;
    for (int i = 0; i < kupriniu_kiekis; i++)
    {
        data >> temp;
        if (temp * 2 <= sunkiausia)
        {
            kiekis++;
        }
    }
    data.close();
    return kiekis;
}

void rez(int sunkiausia, int kiekis)
{
    ofstream rez("U1rez.txt");
    rez << sunkiausia << " " << kiekis << endl;
    rez.close();
}

int main()
{
    rez(sunkiausiuos_kuprines_svoris(), du_kartus_lengvesniu_kupriniu_radimas(sunkiausiuos_kuprines_svoris()));
    return 0;
}
#include <iostream>
#include <fstream>
using namespace std;

void skaitymas(int slyvos[], int mokiniai[])
{

    ifstream data("U1.txt");

    for (int i = 0; i < 10; i++)
    {
        data >> mokiniai[i];
    }

    for (int i = 0; i < 10; i++)
    {
        slyvos[i] = 10 - mokiniai[i];
    }
}

void kiek_slyvu_suvalge_kiekvienas_mokinys(int bliudelis, int pozicija, int mokiniai[])
{

    for (int i = pozicija; i < pozicija + 11 && bliudelis != 0; i++)
    {
        bliudelis--;
        mokiniai[i + 1]++;
    }
}

void rez(int mokiniai[])
{

    ofstream data("U1rez.txt");

    for (int i = 0; i < 20; i++)
    {
        data << mokiniai[i] << " ";
    }
}

int main()
{
    int slyvos[10] = {0};
    int mokiniai[20] = {0};

    skaitymas(slyvos, mokiniai);

    for (int i = 0; i < 10; i++)
    {
        kiek_slyvu_suvalge_kiekvienas_mokinys(slyvos[i], i, mokiniai);
    }

    rez(mokiniai);

    return 0;
}
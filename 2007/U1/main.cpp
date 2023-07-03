#include <iostream>
#include <fstream>

using namespace std;
void rez(int baravykai[], int raudonikiai[], int lepsiai[], int max)
{
    ofstream rez("U1rez.txt");
    for (int i = 0; i < 31; i++)
    {
        if (baravykai[i] != 0 && raudonikiai[i] != 0 && lepsiai[i] != 0)
        {
            rez << i << " " << baravykai[i] << " " << raudonikiai[i] << " " << lepsiai[i] << endl;
        }
    }
    rez << max << " " << baravykai[max] + raudonikiai[max] + lepsiai[max] << endl;
}

void skaitymas(int baravykai[], int raudonikiai[], int lepsiai[])
{
    ifstream data("U1.txt");
    int diena, temp;
    int grybavimo_kartai;
    data >> grybavimo_kartai;

    for (int i = 0; i < grybavimo_kartai; i++)
    {
        data >> diena;

        data >> temp;
        baravykai[diena] += temp;

        data >> temp;
        raudonikiai[diena] += temp;

        data >> temp;
        lepsiai[diena] += temp;
    }
}
int diena_kai_daugiausiai_grybavo(int a[], int b[], int c[])
{
    int diena = 0;
    int max = 0;
    for (int i = 0; i < 31; i++)
    {
        if (max < a[i] + b[i] + c[i])
        {
            max = a[i] + b[i] + c[i];
            diena = i;
        }
    }
    return diena;
}

int main()
{
    int baravykai[31] = {0};
    int raudonikiai[31] = {0};
    int lepsiai[31] = {0};
    skaitymas(baravykai, raudonikiai, lepsiai);
    int max = diena_kai_daugiausiai_grybavo(baravykai, raudonikiai, lepsiai);
    rez(baravykai, raudonikiai, lepsiai, max);
}

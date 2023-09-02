#include <iostream>
#include <fstream>
using namespace std;

struct Ivestas
{
    string slaptazodis;
    int parametrai[5];
    string stiprumas;
    int panasumai[5];
};

struct Naudotojo
{
    string slaptazodis;
    int parametrai[5];
    int panasumas[25];
    string stiprumas;
    int maziausias_panasumas;
    string panasus[25];
    int panasiu_kiekis = 0;
};

void skaitymas(int &n, int &s, Naudotojo naudotojo[], Ivestas ivesti[])
{
    ifstream data("U2.txt");
    data >> n;
    data >> s;
    for (int i = 0; i < n; i++)
    {
        char ch[16];
        data.read(ch, 1);
        data.read(ch, 15);
        naudotojo[i].slaptazodis = ch;
        for (int j = 0; j < 5; j++)
        {
            data >> naudotojo[i].parametrai[j];
        }
    }
    for (int i = 0; i < s; i++)
    {
        data >> ivesti[i].slaptazodis;
        for (int j = 0; j < 5; j++)
        {
            data >> ivesti[i].parametrai[j];
        }
        char chs[10];
        data.read(chs, 1);
        data.read(chs, 9);
        ivesti[i].stiprumas = chs;
    }
}

int panasumas(Naudotojo naudotojo, Ivestas ivestas)
{
    int sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sum += abs(naudotojo.parametrai[i] - ivestas.parametrai[i]);
    }
    return sum;
}

void stiprumo_radimas(int s, Naudotojo &naudotojo, Ivestas ivesti[])
{
    int min = naudotojo.panasumas[0];
    int min_i = 0;
    for (int i = 0; i < s; i++)
    {
        if (naudotojo.panasumas[i] < min)
        {
            min = naudotojo.panasumas[i];
            min_i = i;
        }
    }

    naudotojo.maziausias_panasumas = min;
    naudotojo.stiprumas = ivesti[min_i].stiprumas;
}

void panasiu_atrinkimas(int n, int s, Naudotojo naudotojo[], Ivestas ivesti[])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < s; j++)
        {
            if (naudotojo[i].stiprumas == ivesti[j].stiprumas && naudotojo[i].maziausias_panasumas == ivesti[j].panasumai[i])
            {
                naudotojo[i].panasus[naudotojo[i].panasiu_kiekis] = ivesti[j].slaptazodis;
                naudotojo[i].panasiu_kiekis++;
            }
        }
    }
}

void sort(Naudotojo &naudotojas)
{
    for (int i = 0; i < naudotojas.panasiu_kiekis - 1; i++)
    {
        for (int j = 0; j < naudotojas.panasiu_kiekis - 1 - i; j++)
        {
            if (naudotojas.panasus[j].length() < naudotojas.panasus[j + 1].length())
            {
                swap(naudotojas.panasus[j], naudotojas.panasus[j + 1]);
            }
        }
    }
}

void rez(int n, Naudotojo naudotojo[])
{
    ofstream rez("U2rez.txt");
    for (int i = 0; i < n; i++)
    {
        rez << naudotojo[i].slaptazodis << naudotojo[i].stiprumas << naudotojo[i].maziausias_panasumas << endl;
        for (int j = 0; j < naudotojo[i].panasiu_kiekis; j++)
        {
            rez << naudotojo[i].panasus[j] << endl;
        }
    }
    rez.close();
}

int main()
{
    int n;
    int s;
    Naudotojo naudotojo[5];
    Ivestas ivesti[25];
    skaitymas(n, s, naudotojo, ivesti);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < s; j++)
        {
            naudotojo[i].panasumas[j] = panasumas(naudotojo[i], ivesti[j]);
            ivesti[j].panasumai[i] = naudotojo[i].panasumas[j];
        }
    }

    for (int i = 0; i < n; i++)
    {
        stiprumo_radimas(s, naudotojo[i], ivesti);
    }

    panasiu_atrinkimas(n, s, naudotojo, ivesti);

    for (int i = 0; i < n; i++)
    {
        sort(naudotojo[i]);
    }

    rez(n, naudotojo);

    return 0;
}
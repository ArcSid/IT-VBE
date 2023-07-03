#include <iostream>
#include <fstream>

using namespace std;

struct Grybautojas
{
    string name;
    int baravykai = 0;
    int raudonikiai = 0;
    int lepsiai = 0;
    int grybu_kiekis()
    {
        int grybai = baravykai + raudonikiai + lepsiai;
        return grybai;
    }
};

void skaitymas(int &grybautoju_kiekis, Grybautojas grybautojai[])
{
    ifstream data("U2.txt");
    data >> grybautoju_kiekis;
    for (int i = 0; i < grybautoju_kiekis; i++)
    {
        char name[16] = {0};
        data.read(name, 1);
        data.read(name, 15);
        grybautojai[i].name = name;
        int temp;
        data >> temp;
        for (int a = 0; a < temp; a++)
        {
            int temp_2;
            data >> temp_2;
            grybautojai[i].baravykai += temp_2;
            data >> temp_2;
            grybautojai[i].raudonikiai += temp_2;
            data >> temp_2;
            grybautojai[i].lepsiai += temp_2;
        }
    }
}

int duagiausiai_grybu(int kiekis, Grybautojas grybautojai[])
{
    int max = 0;
    int indicator;
    for (int i = 0; i < kiekis; i++)
    {
        if (max < grybautojai[i].grybu_kiekis())
        {
            max = grybautojai[i].grybu_kiekis();
            indicator = i;
        }
    }
    return indicator;
}
void rez(int grybautoju_kiekis, Grybautojas grybautojai[], int daugiausiai)
{
    ofstream rez("U2rez.txt");
    for (int i = 0; i < grybautoju_kiekis; i++)
    {
        rez << grybautojai[i].name << grybautojai[i].baravykai << " " << grybautojai[i].raudonikiai << " " << grybautojai[i].lepsiai << endl;
    }
    rez << grybautojai[daugiausiai].name << grybautojai[daugiausiai].grybu_kiekis() << endl;
}

int main()
{
    Grybautojas grybautojai[100];
    int grybautoju_kiekis;
    skaitymas(grybautoju_kiekis, grybautojai);
    int daugiausiai = duagiausiai_grybu(grybautoju_kiekis, grybautojai);
    rez(grybautoju_kiekis, grybautojai, daugiausiai);
}
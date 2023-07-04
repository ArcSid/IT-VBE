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
        return baravykai + raudonikiai + lepsiai;
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
    int max_indicator=0;
    for (int i = 0; i < kiekis; i++)
    {
        if (grybautojai[max_indicator].grybu_kiekis() < grybautojai[i].grybu_kiekis())
        {
            max_indicator = i;
        }
    }
    return max_indicator;
}
void rez(int grybautoju_kiekis, Grybautojas grybautojai[], int daugiausiai_surinkes)
{
    ofstream rez("U2rez.txt");
    for (int i = 0; i < grybautoju_kiekis; i++)
    {
        rez << grybautojai[i].name << grybautojai[i].baravykai << " " << grybautojai[i].raudonikiai << " " << grybautojai[i].lepsiai << endl;
    }
    rez << grybautojai[daugiausiai_surinkes].name << grybautojai[daugiausiai_surinkes].grybu_kiekis() << endl;
}

int main()
{
    Grybautojas grybautojai[100];
    int grybautoju_kiekis;
    skaitymas(grybautoju_kiekis, grybautojai);
    int daugiausiai_surinkes = duagiausiai_grybu(grybautoju_kiekis, grybautojai);
    rez(grybautoju_kiekis, grybautojai, daugiausiai_surinkes);
}
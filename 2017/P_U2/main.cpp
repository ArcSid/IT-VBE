#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

struct Spalva
{
    int r = 255;
    int g = 255;
    int b = 255;
};

struct Kvadratas
{
    int x0;
    int y0;
    int dydis;
    Spalva spalva;
};

struct Piesinys
{
    Spalva spalvos[99][99];
    int maxX = 0;
    int maxY = 0;
    int minX = 99;
    int minY = 99;

    void atnaujintiDydzius(int x, int y, int dydis)
    {
        minX = min(minX, x);
        minY = min(minY, y);

        maxX = max(maxX, x + dydis);
        maxY = max(maxY, y + dydis);
    }
};

void printMap(Piesinys piesinys)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << setw(4) << piesinys.spalvos[j][i].r << " " << setw(4) << piesinys.spalvos[j][i].g << " " << setw(4) << piesinys.spalvos[j][i].b << " ; ";
        }
        cout << endl;
    }
}

void skaitymas(vector<Kvadratas> &kvadratai)
{
    ifstream data("U2.txt");
    int n;
    Kvadratas tempKvadratas;
    Spalva tempSpalva;

    data >> n;

    for (int i = 0; i < n; i++)
    {
        data >> tempKvadratas.x0;
        data >> tempKvadratas.y0;
        data >> tempKvadratas.dydis;

        data >> tempSpalva.r;
        data >> tempSpalva.g;
        data >> tempSpalva.b;

        tempKvadratas.spalva = tempSpalva;

        kvadratai.push_back(tempKvadratas);
    }
    data.close();
}

void kvadratoUzdejimas(Piesinys &piesinys, Kvadratas kvadratas)
{
    for (int j = kvadratas.x0; j < kvadratas.x0 + kvadratas.dydis; j++)
    {
        for (int k = kvadratas.y0; k < kvadratas.y0 + kvadratas.dydis; k++)
        {
            piesinys.spalvos[j][k] = kvadratas.spalva;
        }
    }
    piesinys.atnaujintiDydzius(kvadratas.y0, kvadratas.x0, kvadratas.dydis);
}

void mapSurinkimas(vector<Kvadratas> kvadratai, Piesinys &piesinys)
{
    for (int i = 0; i < kvadratai.size(); i++)
    {
        kvadratoUzdejimas(piesinys, kvadratai[i]);
    }
}

void rez(Piesinys piesinys)
{
    ofstream rez("U2rez.txt");
    rez << piesinys.maxX - piesinys.minX << " " << piesinys.maxY - piesinys.minY << endl;
    for (int i = piesinys.minX; i < piesinys.maxX; i++)
    {
        for (int j = piesinys.minY; j < piesinys.maxY; j++)
        {
            rez << piesinys.spalvos[j][i].r << " " << piesinys.spalvos[j][i].g << " " << piesinys.spalvos[j][i].b << endl;
        }
    }
    rez.close();
}

int main()
{
    Piesinys piesinys;
    vector<Kvadratas> kvadratai;

    skaitymas(kvadratai);
    mapSurinkimas(kvadratai, piesinys);
    rez(piesinys);
    return 0;
}
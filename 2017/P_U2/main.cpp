#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Spalva
{
    int r = 255;
    int g = 255;
    int b = 255;
    bool utilised = false;
};

struct Kvadratas
{
    int x0;
    int y0;
    int dydis;
    Spalva spalva;
};

struct Map
{
    Spalva spalvos[99][99];
    int maxX = 0;
    int maxY = 0;
    int minX = 99;
    int minY = 99;
    int l1()
    {
        return maxX - minX + 1;
    }
    int l2()
    {
        return maxY - minY + 1;
    }
};

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

        tempSpalva.utilised = true;
        tempKvadratas.spalva = tempSpalva;

        kvadratai.push_back(tempKvadratas);
    }
    data.close();
}

void kvadratoUzdejimas(Map &map, Kvadratas kvadratas)
{
    for (int j = kvadratas.x0; j < kvadratas.x0 + kvadratas.dydis; j++)
    {
        for (int k = kvadratas.y0; k < kvadratas.y0 + kvadratas.dydis; k++)
        {
            map.spalvos[j][k] = kvadratas.spalva;
        }
    }
}

void mapSurinkimas(vector<Kvadratas> kvadratai, Map &map)
{
    for (int i = 0; i < kvadratai.size(); i++)
    {
        kvadratoUzdejimas(map, kvadratai[i]);
    }
}

void maxReiksmes(Map &map)
{
    for (int i = 0; i < 99; i++)
    {
        for (int j = 0; j < 99; j++)
        {
            if (map.spalvos[i][j].utilised)
            {
                if (map.minX > i)
                {
                    map.minX = i;
                }
                if (map.minY > j)
                {
                    map.minY = j;
                }
                if (map.maxX < i)
                {
                    map.maxX = i;
                }
                if (map.maxY < j)
                {
                    map.maxY = j;
                }
            }
        }
    }
}

void printMap(Map map)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (map.spalvos[i][j].utilised)
            {
                cout << map.spalvos[i][j].r << " " << map.spalvos[i][j].g << " " << map.spalvos[i][j].b << " ";
            }
        }
        cout << endl;
    }
}

void rez(Map map)
{
    ofstream rez("U2rez.txt");
    rez << map.l1() << " " << map.l2() << endl;
    for (int i = map.minX; i < map.maxX + 1; i++)
    {
        for (int j = map.minY; j < map.maxY + 1; j++)
        {
            if (map.spalvos[i][j].utilised)
            {
                rez << map.spalvos[j][i].r << " " << map.spalvos[j][i].g << " " << map.spalvos[j][i].b << endl;
            }
            else
            {
                rez << 255 << " " << 255 << " " << 255 << endl;
            }
        }
    }
    rez.close();
}

int main()
{
    Map map;
    vector<Kvadratas> kvadratai;

    skaitymas(kvadratai);
    mapSurinkimas(kvadratai, map);
    maxReiksmes(map);
    rez(map);
}
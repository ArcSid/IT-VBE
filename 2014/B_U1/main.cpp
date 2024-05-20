#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Uzsakovas
{
    int x;
    int y;
    int atstumasNuoPicerijosIrAtgal()
    {
        return (abs(x) + abs(y)) * 2;
    }
};

void skaitytiIsFailo(int &kilometrazas, vector<Uzsakovas> &uzsakovai)
{
    Uzsakovas laikinasUzsakovas;
    int uzsakovuKiekis;
    ifstream data("U1.txt");

    data >> uzsakovuKiekis >> kilometrazas;

    for (int i = 0; i < uzsakovuKiekis; i++)
    {
        data >> laikinasUzsakovas.x >> laikinasUzsakovas.y;
        uzsakovai.push_back(laikinasUzsakovas);
    }
    data.close();
}

void skaiciuotiKiekAptarnavoIrNuvaziavo(int &aptarnautuKiekis, int &nuvaziavo, int kilometrazas, vector<Uzsakovas> uzsakovai)
{
    for (int i = 0; i < uzsakovai.size(); i++)
    {
        nuvaziavo += uzsakovai[i].atstumasNuoPicerijosIrAtgal();
        aptarnautuKiekis++;
        if (nuvaziavo > kilometrazas)
        {
            break;
        }
    }
}

void rez(int neaptarnautuKiekis, int nuvaziavo)
{
    ofstream rez("U1rez.txt");
    rez << neaptarnautuKiekis << " " << nuvaziavo << endl;
    rez.close();
}

int main()
{
    int kilometrazas;
    vector<Uzsakovas> uzsakovai;
    skaitytiIsFailo(kilometrazas, uzsakovai);

    int aptarnautuKiekis = 0;
    int nuvaziavo = 0;
    skaiciuotiKiekAptarnavoIrNuvaziavo(aptarnautuKiekis, nuvaziavo, kilometrazas, uzsakovai);
    rez(uzsakovai.size() - aptarnautuKiekis, nuvaziavo);
}
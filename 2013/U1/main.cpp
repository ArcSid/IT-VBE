#include <iostream>
#include <fstream>

using namespace std;

struct Imone
{
    string pavadinimas;
    int x;
    int y;

    int austumas_iki_ir_atgal()
    {
        int x_abs = abs(x);
        int y_abs = abs(y);
        return (x_abs + y_abs) * 2;
    }
};

void resultatai(Imone imones[], int kiek_nuvaziavo, int kiek_imoniu_aptarnavo)
{
    ofstream rez("U1rez.txt");
    rez << kiek_imoniu_aptarnavo << " " << kiek_nuvaziavo << " " << imones[kiek_imoniu_aptarnavo - 1].pavadinimas << endl;
}

void skaitymas(int &imoniu_skaicius, int &max_kilometrazas, Imone imones[])
{
    ifstream data("U1.txt");
    data >> imoniu_skaicius;
    data >> max_kilometrazas;
    for (int i = 0; i < imoniu_skaicius; i++)
    {
        char ch[11];
        data.read(ch, 1);
        data.read(ch, 10);
        imones[i].pavadinimas = ch;
        data >> imones[i].x;
        data >> imones[i].y;
    }
}

int kiek_nuvaziavo_kilometru(int imoniu_skaicius, Imone imones[], int max_kilometrazas, int &kiek_imoniu_aptarnavo)
{
    int kilometrai = 0;

    for (int i = 0; i < imoniu_skaicius; i++)
    {
        if (kilometrai + imones[i].austumas_iki_ir_atgal() > max_kilometrazas)
        {
            kiek_imoniu_aptarnavo = i;
            break;
        }
        kilometrai += imones[i].austumas_iki_ir_atgal();
    }

    return kilometrai;
}

int main()
{
    Imone imones[50];
    int imoniu_skaicius;
    int max_kilometrazas;
    int kiek_imoniu_aptarnavo = 0;

    skaitymas(imoniu_skaicius, max_kilometrazas, imones);

    int kiek_nuvaziavo = kiek_nuvaziavo_kilometru(imoniu_skaicius, imones, max_kilometrazas, kiek_imoniu_aptarnavo);

    resultatai(imones, kiek_nuvaziavo, kiek_imoniu_aptarnavo);
}
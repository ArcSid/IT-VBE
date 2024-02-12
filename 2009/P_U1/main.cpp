#include <iostream>
#include <fstream>
using namespace std;

void skaitymas(int &studentu_kiekis, int &nominaluSk, int studentuTurimiPinigai[], int nominalai[])
{
    ifstream data("U1.txt");

    data >> studentu_kiekis;
    for (int i = 0; i < studentu_kiekis; i++)
    {
        data >> studentuTurimiPinigai[i];
    }

    data >> nominaluSk;
    for (int i = 0; i < nominaluSk; i++)
    {
        data >> nominalai[i];
    }
    data.close();
}

// skaiciuoja iskeistas gilijas i monetas ir kiek ju liko
void monetuSkaiciavimas(int nominaluSk, int gilijuKiekis, int nominalai[], int nominaluoseGautuMonetuSk[], int &liko)
{
    for (int i = 0; i < nominaluSk; i++)
    {
        nominaluoseGautuMonetuSk[i] = gilijuKiekis / nominalai[i];
        gilijuKiekis = gilijuKiekis % nominalai[i];
    }
    liko = gilijuKiekis;
}

int kiekIsVisoGaus(int nominaluSk, int nominaluoseGautuMonetuSk[])
{
    int sum = 0;
    for (int i = 0; i < nominaluSk; i++)
    {
        sum += nominaluoseGautuMonetuSk[i];
    }
    return sum;
}

void rez(int monetuKiekis, int nominaluSk, int nominaluoseGautuMonetuSk[], int nominalai[], int gilijuKiekis, int liko)
{
    ofstream rez("U1rez.txt");

    rez << gilijuKiekis << endl;

    for (int i = 0; i < nominaluSk; i++)
    {
        rez << nominalai[i] << " " << nominaluoseGautuMonetuSk[i] << endl;
    }

    rez << monetuKiekis << endl;

    rez << liko << endl;

    rez.close();
}

int studentuGilijuSkaiciavimas(int studentu_kiekis, int studentuTurimiPinigai[])
{
    int sum = 0;
    for (int i = 0; i < studentu_kiekis; i++)
    {
        sum += studentuTurimiPinigai[i];
    }
    return sum;
}

int main()
{
    int nominaluSk;
    int nominalai[15];
    int studentuTurimiPinigai[30];
    int nominaluoseGautuMonetuSk[15] = {0};
    int liko = 0;
    int studentu_kiekis;

    skaitymas(studentu_kiekis, nominaluSk, studentuTurimiPinigai, nominalai);
    int gilijuKiekis = studentuGilijuSkaiciavimas(studentu_kiekis, studentuTurimiPinigai);
    monetuSkaiciavimas(nominaluSk, gilijuKiekis, nominalai, nominaluoseGautuMonetuSk, liko);
    int monetuKiekis = kiekIsVisoGaus(nominaluSk, nominaluoseGautuMonetuSk);
    rez(monetuKiekis, nominaluSk, nominaluoseGautuMonetuSk, nominalai, gilijuKiekis, liko);
    return 0;
}
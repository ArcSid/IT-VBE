#include <fstream>
#include <iostream>
using namespace std;

void skaitymas(int &islaidos, int &aliejaus_kiekis, int turimi_indai[],
               int pardavimu_kainos[])
{
    ifstream data("U1.txt");
    data >> turimi_indai[0] >> turimi_indai[1] >> turimi_indai[2];
    data >> aliejaus_kiekis >> islaidos;
    data >> pardavimu_kainos[0] >> pardavimu_kainos[1] >> pardavimu_kainos[2];
    data.close();
}

void pilnu_indu_skaiciavimas(int &aliejaus_kiekis, int turimi_indai[],
                             int pilni_indai[])
{
    pilni_indai[2] = min(aliejaus_kiekis / 5, turimi_indai[2]);
    aliejaus_kiekis -= pilni_indai[2] * 5;

    pilni_indai[1] = min(aliejaus_kiekis / 3, turimi_indai[1]);
    aliejaus_kiekis -= pilni_indai[1] * 3;

    pilni_indai[0] = min(aliejaus_kiekis, turimi_indai[0]);
    aliejaus_kiekis -= pilni_indai[0];

    turimi_indai[2] -= pilni_indai[2];
    turimi_indai[1] -= pilni_indai[1];
    turimi_indai[0] -= pilni_indai[0];
}

int pelno_slaiciavimas(int islaidos, int papildomi_indai[], int pilni_indai[],
                       int kainos[])
{
    return kainos[2] * (pilni_indai[2] + papildomi_indai[2]) +
           kainos[1] * (pilni_indai[1] + papildomi_indai[1]) +
           kainos[0] * (pilni_indai[0] + papildomi_indai[0]) - islaidos;
}

void kiek_reikia_indu(int papildomu_indu_kiekis[], int likes_aliejus)
{
    papildomu_indu_kiekis[2] = likes_aliejus / 5;
    likes_aliejus -= 5 * papildomu_indu_kiekis[2];

    papildomu_indu_kiekis[1] = likes_aliejus / 3;
    likes_aliejus -= 3 * papildomu_indu_kiekis[1];

    papildomu_indu_kiekis[0] = likes_aliejus / 1;
}

void rez(int pilni_indai[], int liko, int nepanaudoti[], int papildomi[],
         int pelnas)
{
    ofstream rez("U1rez.txt");
    rez << pilni_indai[0] << " " << pilni_indai[1] << " " << pilni_indai[2] << " "
        << liko << endl;
    rez << nepanaudoti[0] << " " << nepanaudoti[1] << " " << nepanaudoti[2]
        << endl;
    rez << papildomi[0] << " " << papildomi[1] << " " << papildomi[2] << endl;
    rez << pelnas;
    rez.close();
}

int main()
{

    int islaidos;
    int pardavimu_kainos[3] = {0};
    int turimi_indai[3] = {0};
    int aliejaus_kiekis;

    skaitymas(islaidos, aliejaus_kiekis, turimi_indai, pardavimu_kainos);

    int pilni_indai[3] = {0};
    int nepanaudoti_indai[3] = {0};
    int papildomu_indu_kiekis[3] = {0};

    pilnu_indu_skaiciavimas(aliejaus_kiekis, turimi_indai, pilni_indai);

    kiek_reikia_indu(papildomu_indu_kiekis, aliejaus_kiekis);

    int pelnas = pelno_slaiciavimas(islaidos, papildomu_indu_kiekis, pilni_indai,
                                    pardavimu_kainos);
    rez(pilni_indai, aliejaus_kiekis, turimi_indai, papildomu_indu_kiekis,
        pelnas);
    return 0;
}
#include <iostream>
#include <fstream>
using namespace std;

void skaitymas(int &skyriu_skaicius, int balsai_1[], int balsai_2[], int balsai_3[], int direktoriaus_skirti_taskai[])
{
    ifstream data("U1.txt");
    data >> skyriu_skaicius;
    for (int i = 0; i < skyriu_skaicius; i++)
    {
        data >> balsai_1[i];
        data >> balsai_2[i];
        data >> balsai_3[i];
    }
    data >> direktoriaus_skirti_taskai[0];
    data >> direktoriaus_skirti_taskai[1];
    data >> direktoriaus_skirti_taskai[2];
}

// 100x + 10y + 1z = number xyz
int tasku_paskirstymas(int b1, int b2, int b3)
{
    if (b1 == b2 && b2 == b3)
    {
        return 111;
    }
    if (b1 == b2)
    {
        return 220;
    }
    if (b2 == b3)
    {
        return 22;
    }
    if (b1 > b2 && b1 > b3)
    {
        return 400;
    }
    if (b2 > b3)
    {
        return 40;
    }
    return 4;
}

void tasku_sumavimas(int sk, int b1[], int b2[], int b3[], int &t1, int &t2, int &t3)
{
    int temp = 0;
    for (int i = 0; i < sk; i++)
    {
        temp = tasku_paskirstymas(b1[i], b2[i], b3[i]);
        t1 += temp / 100;
        t2 += (temp / 10) % 10;
        t3 += temp % 10;
    }
}

int laimejes_logotipas(int &t1, int &t2, int &t3, int dt[])
{
    bool ar_paskirti_taskai = false;
    if (t1 == t2 && t2 == t3)
    {
        t1 += dt[0];
        t2 += dt[1];
        t3 += dt[2];
    }
    if (!ar_paskirti_taskai)
    {
        if (t1 < t2 && t2 == t3)
        {
            t1 += dt[0];
            t2 += dt[1];
            t3 += dt[2];
        }
        if (t2 < t3 && t3 == t1)
        {
            t1 += dt[0];
            t2 += dt[1];
            t3 += dt[2];
        }
        if (t3 < t2 && t2 == t1)
        {
            t1 += dt[0];
            t2 += dt[1];
            t3 += dt[2];
        }
    }

    int max_i = 0;
    int arr[3] = {t1, t2, t3};

    for (int i = 0; i < 3; i++)
    {
        if (arr[i] > arr[max_i])
        {
            max_i = i;
        }
    }
    return max_i + 1;
}

void balsu_suma(int sk, int balsai_1[], int balsai_2[], int balsai_3[], int &b1, int &b2, int &b3)
{
    for (int i = 0; i < sk; i++)
    {
        b1 += balsai_1[i];
        b2 += balsai_2[i];
        b3 += balsai_3[i];
    }
}

void rez(int b1, int b2, int b3, int t1, int t2, int t3, int laimejo)
{
    ofstream rez("U1rez.txt");
    rez << b1 << " " << b2 << " " << b3 << endl;
    rez << t1 << " " << t2 << " " << t3 << endl;
    rez << laimejo;
}

int main()
{
    int balsai_1[10];
    int balsai_2[10];
    int balsai_3[10];
    int skyriu_skaicius;
    int direktoriaus_skirti_taskai[3];
    skaitymas(skyriu_skaicius, balsai_1, balsai_2, balsai_3, direktoriaus_skirti_taskai);
    int taskai_1 = 0;
    int taskai_2 = 0;
    int taskai_3 = 0;
    tasku_sumavimas(skyriu_skaicius, balsai_1, balsai_2, balsai_3, taskai_1, taskai_2, taskai_3);
    int laimejo = laimejes_logotipas(taskai_1, taskai_2, taskai_3, direktoriaus_skirti_taskai);
    int b1 = 0, b2 = 0, b3 = 0;
    balsu_suma(skyriu_skaicius, balsai_1, balsai_2, balsai_3, b1, b2, b3);
    rez(b1, b2, b3, taskai_1, taskai_2, taskai_3, laimejo);
}
#include <fstream>
using namespace std;

void skaitymas(int &N1, int &N2, int &pirkejuKiekis, int pirkejuPageidavimai[])
{
    ifstream data("U1.txt");
    data >> N1 >> N2 >> pirkejuKiekis;
    for (int i = 0; i < pirkejuKiekis; i++)
    {
        data >> pirkejuPageidavimai[i];
    }
    data.close();
}

void zirniuPardavimuSkaiciavimas(int &N1, int &N2,
                                 int &parduotaN1, int &parduotaN2,
                                 int &paskutinioPirkejoZirniuKiekis,
                                 int &aptarnautuPirkejuKiekis,
                                 int pirkejuKiekis, int pirkejuPageidavimai[])
{

    for (int i = 0; i < pirkejuKiekis; i++)
    {
        int panaudotiN1 = 0;
        int panaudotiN2 = 0;
        for (int j = 0; j < N2; j++)
        {
            if (pirkejuPageidavimai[i] - 2 >= 0)
            {
                pirkejuPageidavimai[i] -= 2;
                panaudotiN2++;
            }
            else
            {
                break;
            }
        }
        N2 -= panaudotiN2;
        for (int j = 0; j < N1; j++)
        {
            if (pirkejuPageidavimai[i] - 1 >= 0)
            {
                pirkejuPageidavimai[i] -= 1;
                panaudotiN1++;
            }
            else
            {
                break;
            }
        }
        N1 -= panaudotiN1;
        paskutinioPirkejoZirniuKiekis = panaudotiN1 + panaudotiN2 * 2;
        parduotaN1 += panaudotiN1;
        parduotaN2 += panaudotiN2;
        aptarnautuPirkejuKiekis++;
        if (pirkejuPageidavimai[i] > 0)
        {
            break;
        }
    }
}

void rez(int parduotaN1, int parduotaN2, int aptarnautuPirkejuKiekis, int paskutinioPirkejoZirniuKiekis)
{
    ofstream rez("U1rez.txt");
    rez << parduotaN1 << " " << parduotaN2 << endl;
    rez << aptarnautuPirkejuKiekis << endl;
    rez << paskutinioPirkejoZirniuKiekis << endl;
    rez.close();
}

int main()
{
    int N1, N2, pirkejuKiekis;
    int pirkejuPageidavimai[100];
    skaitymas(N1, N2, pirkejuKiekis, pirkejuPageidavimai);

    int paskutinioPirkejoZirniuKiekis = 0;
    int aptarnautuPirkejuKiekis = 0;
    int parduotaN1 = 0, parduotaN2 = 0;
    zirniuPardavimuSkaiciavimas(N1, N2, parduotaN1, parduotaN2, paskutinioPirkejoZirniuKiekis, aptarnautuPirkejuKiekis, pirkejuKiekis, pirkejuPageidavimai);

    rez(parduotaN1, parduotaN2, aptarnautuPirkejuKiekis, paskutinioPirkejoZirniuKiekis);
    return 0;
}

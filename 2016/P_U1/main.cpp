#include <fstream>
using namespace std;

int vidurkis()
{
    int ugiuSuma = 0;
    int kiekis;
    int ugis;
    ifstream data("U1.txt");

    data >> kiekis;
    for (int i = 0; i < kiekis; i++)
    {
        data >> ugis;
        ugiuSuma += ugis;
    }

    data.close();
    return ugiuSuma / kiekis;
}

int didesniUzVidurki(int vidurkis)
{
    int ugis;
    int visuKiekis;
    int aukstesniuKiekis = 0;
    ifstream data("U1.txt");

    data >> visuKiekis;
    for (int i = 0; i < visuKiekis; i++)
    {
        data >> ugis;
        if (ugis > vidurkis)
        {
            aukstesniuKiekis++;
        }
    }

    data.close();
    return aukstesniuKiekis;
}

void rez(int vidurkis, int daugiauUzVidurkiKiekis)
{
    ofstream rez("U1rez.txt");
    rez << vidurkis << " " << daugiauUzVidurkiKiekis << endl;
    rez.close();
}

int main()
{
    int ugiuVidurkis = vidurkis();
    rez(ugiuVidurkis, didesniUzVidurki(ugiuVidurkis));
    return 0;
}
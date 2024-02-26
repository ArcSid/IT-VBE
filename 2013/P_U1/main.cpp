#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

struct Uzsakovas
{
    string pavadinimas;
    int x;
    int y;
    int atstumas()
    {
        return 2 * (abs(x) + abs(y));
    }
};

void skaitymas(int &kilometrazas, vector<Uzsakovas> &uzsakovai)
{
    ifstream data("U1.txt");
    int n;
    data >> n;
    data >> kilometrazas;
    for (int i = 0; i < n; i++)
    {
        data.ignore();
        char ch[11];
        data.read(ch, 10);
        ch[10] = '\0';
        Uzsakovas tempUzsakovas;
        tempUzsakovas.pavadinimas = ch;
        data >> tempUzsakovas.x;
        data >> tempUzsakovas.y;
        uzsakovai.push_back(tempUzsakovas);
    }
    data.close();
}

// skaiciuoja koki atstuma nuvaziavo, kiek uzsakovu liko, ir paskutines aplankytos vietos pavadinimas

void skaiciavimai(int &likoUzsakovu, int &kiekNuvaziavo, string &paskutinis, int kilometrazas, vector<Uzsakovas> uzsakovai)
{
    for (int i = 0; i < uzsakovai.size(); i++)
    {
        if (uzsakovai[i].atstumas() <= kilometrazas)
        {
            kiekNuvaziavo += uzsakovai[i].atstumas();
            kilometrazas -= uzsakovai[i].atstumas();
            likoUzsakovu--;
            paskutinis = uzsakovai[i].pavadinimas;
        }
        else
        {
            likoUzsakovu--;
            kiekNuvaziavo += uzsakovai[i].atstumas();
            paskutinis = uzsakovai[i].pavadinimas;
            break;
        }
    }
}

void rez(int likoUzsakovu, int kiekNuvaziavo, string paskutinis)
{
    ofstream rez("U1rez.txt");
    rez << likoUzsakovu << " " << kiekNuvaziavo << " " << paskutinis << endl;
    rez.close();
}

int main()
{
    int kilometrazas;
    vector<Uzsakovas> uzsakovai;

    skaitymas(kilometrazas, uzsakovai);

    int likoUzsakovu = uzsakovai.size();
    int kiekNuvaziavo = 0;
    string paskutinis;

    skaiciavimai(likoUzsakovu, kiekNuvaziavo, paskutinis, kilometrazas, uzsakovai);
    rez(likoUzsakovu, kiekNuvaziavo, paskutinis);
    
    return 0;
}
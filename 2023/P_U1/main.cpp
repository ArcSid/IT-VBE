#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Mokinys
{
    string variantas;
    int taskai[10];

    int gautasTaskuKiekis()
    {
        int sum = 0;
        for (int i = 0; i < 10; i++)
        {
            sum += taskai[i];
        }
        return sum;
    }
};

struct Testas
{
    string variantas;
    vector<int> mokiniuTaskai;
    int islaikiusiuKiekisProcentais;
    int daugiausiaiTasku;
};

void skaitymas(vector<Mokinys> &mokiniai)
{
    ifstream data("U1.txt");
    int mokiniuKiekis;
    char ch[7];
    Mokinys tempMokinys;

    data >> mokiniuKiekis;
    for (int i = 0; i < mokiniuKiekis; i++)
    {
        data.ignore();
        data.read(ch, 6);
        tempMokinys.variantas = ch;
        for (int j = 0; j < 10; j++)
        {
            data >> tempMokinys.taskai[j];
        }
        mokiniai.push_back(tempMokinys);
    }

    data.close();
}

void surinktiTestuDuomenis(vector<Mokinys> mokiniai, vector<Testas> &testai)
{

    // suskirsto mikinius i unikalius variantus. taip pat skaiciuoja dalyvavusiu mokiniu kieki
    for (int i = 0; i < mokiniai.size(); i++)
    {
        bool naujasVariantas = true;
        for (int j = 0; j < testai.size(); j++)
        {
            if (mokiniai[i].variantas == testai[j].variantas)
            {
                naujasVariantas = false;
                testai[j].mokiniuTaskai.push_back(mokiniai[i].gautasTaskuKiekis());
                break;
            }
        }
        if (naujasVariantas)
        {
            Testas naujasTestas;
            naujasTestas.variantas = mokiniai[i].variantas;
            naujasTestas.mokiniuTaskai.push_back(mokiniai[i].gautasTaskuKiekis());
            testai.push_back(naujasTestas);
        }
    }

    // skaiciuoja unikaliu testu variantu islaikiusiu mokiniu procentus
    for (int i = 0; i < testai.size(); i++)
    {
        int islaikiusiuKiekis = 0;
        for (int j = 0; j < testai[i].mokiniuTaskai.size(); j++)
        {
            if (testai[i].mokiniuTaskai[j] >= 15)
            {
                islaikiusiuKiekis++;
            }
        }
        testai[i].islaikiusiuKiekisProcentais = ((float)islaikiusiuKiekis / testai[i].mokiniuTaskai.size()) * 100;
    }

    // skaiciuoja daugiausiai surinkta tasku kieki teste
    for (int i = 0; i < testai.size(); i++)
    {
        int max_i = 0;
        for (int j = 0; j < testai[i].mokiniuTaskai.size(); j++)
        {
            if (testai[i].mokiniuTaskai[max_i] < testai[i].mokiniuTaskai[j])
            {
                max_i = j;
            }
        }
        testai[i].daugiausiaiTasku = testai[i].mokiniuTaskai[max_i];
    }
}

void rez(vector<Testas> testai)
{
    ofstream rez("U1rez.txt");
    for (int i = 0; i < testai.size(); i++)
    {
        rez << testai[i].variantas << " " << testai[i].mokiniuTaskai.size() << " " << testai[i].islaikiusiuKiekisProcentais << "% " << testai[i].daugiausiaiTasku << endl;
    }
    rez.close();
}

int main()
{
    vector<Mokinys> mokiniai;
    skaitymas(mokiniai);

    vector<Testas> testai;
    surinktiTestuDuomenis(mokiniai, testai);
    rez(testai);

    return 0;
}
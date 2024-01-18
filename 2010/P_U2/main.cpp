#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct Svecias{
    string vardas;
    vector<int> patiekalai;
    int kaina;
};

void skaitymas(vector<Svecias>& sveciai, vector<int>& kainos){
    ifstream data("U2.txt");
    int n;
    data >> n;
    int temp;
    for(int i = 0; i<n; i++){
        data >> temp;
        kainos.push_back(temp);
    }
    data >> n;
    for(int i = 0; i<n; i++){
        char ch[16];
        data.read(ch,1);
        data.read(ch,15);
        ch[15] = '\0';
        Svecias tempSvecias;
        tempSvecias.vardas = ch;
        for(int j = 0; j<kainos.size(); j++){
            data >> temp;
            tempSvecias.patiekalai.push_back(temp);
        }
        sveciai.push_back(tempSvecias);
    }
    data.close();
}

void patiekaluKainuSkaiciavimas(vector<Svecias>& sveciai, vector<int> kainos){
    for(int i = 0; i<sveciai.size(); i++){
        int sum = 0;
        for(int j = 0; j<kainos.size(); j++){
            sum+=sveciai[i].patiekalai[j]*kainos[j];
        }
        sveciai[i].kaina = sum;
    }
}

int gimtadienioKaina(vector<Svecias> sveciai){
    int sum = 0;
    for(int i = 0; i<sveciai.size(); i++){
        sum += sveciai[i].kaina;
    }
    return sum;
}

void rez(vector<Svecias> sveciai, int n){
    ofstream rez("U2rez.txt");
    for(int i = 0; i<sveciai.size(); i++){
        rez << sveciai[i].vardas << " " << sveciai[i].kaina << endl;
    }
    rez << n/100 << " " << n%100 << endl;
    rez.close();
}

int main(){
    vector<Svecias> sveciai;
    vector<int> kainos;
    skaitymas(sveciai, kainos);
    patiekaluKainuSkaiciavimas(sveciai, kainos);
    rez(sveciai,gimtadienioKaina(sveciai));
    // cout << gimtadienioKaina(sveciai) << endl;
    // cout << sveciai[0].vardas << endl;
    // cout << sveciai.size() << " " << kainos.size() << endl;
    // for(int i = 0; i<sveciai.size(); i++){
    //     cout << sveciai[i].vardas << " ";
    //     for(int j = 0; j<kainos.size(); j++){
    //         cout << sveciai[i].patiekalai[j] << " ";
    //     }
    //     cout << endl << sveciai[i].kaina << endl;
    // }
    return 0;
}

#include <fstream>
#include <vector>
using namespace std;

struct VedziojimoVieta{
    string pavadinimas;
    int laikas;
};

void skaitymas(vector<VedziojimoVieta>& vedziojimoVietos){
    VedziojimoVieta tempVedziojimoVieta;
    int vietuKiekis;
    ifstream data("U2.txt");
    data >> vietuKiekis;
    for(int i = 0; i<vietuKiekis; i++){
        char ch[21];
        data.ignore();
        data.read(ch,20);
        ch[20] = '\0';
        tempVedziojimoVieta.pavadinimas = ch;
        data >> tempVedziojimoVieta.laikas;
        vedziojimoVietos.push_back(tempVedziojimoVieta);
    }
    data.close();
}

vector<VedziojimoVieta> atrinktiUnikalius(vector<VedziojimoVieta>& vedziojimoVietos){
    vector<VedziojimoVieta> unikaliosVietos;
    for(int i = 0; i<vedziojimoVietos.size(); i++){
        bool unikalusElementas = true;
        for(int j = 0; j<unikaliosVietos.size(); j++){
            if(vedziojimoVietos[i].pavadinimas == unikaliosVietos[j].pavadinimas){
                unikaliosVietos[j].laikas+=vedziojimoVietos[i].laikas;
                unikalusElementas = false;
                break;
            }
        }
        if(unikalusElementas){
            unikaliosVietos.push_back(vedziojimoVietos[i]);
        }
    }
    return unikaliosVietos;
}

void sort(vector<VedziojimoVieta>& vedziojimoVietos){
    for(int i = 0; i<vedziojimoVietos.size(); i++){
        for(int j = 0; j<vedziojimoVietos.size()-1-i; j++){
            if(vedziojimoVietos[j].laikas < vedziojimoVietos[j+1].laikas){
                swap(vedziojimoVietos[j], vedziojimoVietos[j+1]);
            }
            else if(vedziojimoVietos[j].laikas == vedziojimoVietos[j+1].laikas && vedziojimoVietos[j].pavadinimas > vedziojimoVietos[j+1].pavadinimas){
                swap(vedziojimoVietos[j], vedziojimoVietos[j+1]);
            }
        }
    }
}

void rez(vector<VedziojimoVieta> vedziojimoVietos){
    ofstream rez("U2rez.txt");
    for(int i = 0; i<vedziojimoVietos.size(); i++){
        rez << vedziojimoVietos[i].pavadinimas << " " << vedziojimoVietos[i].laikas << endl;
    }
    rez.close();
}

int main(){
    vector<VedziojimoVieta> vedziojimoVietos;

    skaitymas(vedziojimoVietos);
    vector<VedziojimoVieta> unikaliosVietos = atrinktiUnikalius(vedziojimoVietos);
    sort(unikaliosVietos);
    rez(unikaliosVietos);

    return 0;
}
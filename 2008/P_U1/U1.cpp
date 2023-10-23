#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;


void subtract_data(int stociu_kiekis,
                   int stoties_numeriai[],
                   int ilipimai_pagal_numerius[],
                   int islipimai_pagal_numerius[],
                   int& naujas_stociu_kiekis,
                   int naujas_stoties_numeriai[],
                   int naujas_ilipimai_pagal_numerius[]){

    naujas_stoties_numeriai[0] = stoties_numeriai[0];
    naujas_ilipimai_pagal_numerius[0] += ilipimai_pagal_numerius[0] + islipimai_pagal_numerius[0];
    naujas_stociu_kiekis++;

    for(int i = 1; i<stociu_kiekis; i++){
        bool does_exist = false;
        for(int j = 0; j<naujas_stociu_kiekis; j++){
            if(stoties_numeriai[i] == naujas_stoties_numeriai[j]){
              naujas_ilipimai_pagal_numerius[j] += ilipimai_pagal_numerius[i];
              naujas_ilipimai_pagal_numerius[j] += islipimai_pagal_numerius[i];
              does_exist = true;
              break;
            }
        }
        if(does_exist){
            continue;
        }
        naujas_stoties_numeriai[naujas_stociu_kiekis] = stoties_numeriai[i];
        naujas_ilipimai_pagal_numerius[naujas_stociu_kiekis] += ilipimai_pagal_numerius[i];
        naujas_ilipimai_pagal_numerius[naujas_stociu_kiekis] += islipimai_pagal_numerius[i];
        naujas_stociu_kiekis++;
    }
}


void skaitymas(int& stociu_kiekis, int stoties_numeriai[], int stoties_dienos_pagal_numerius[], int ilipimai_pagal_numerius[], int islipimai_pagal_numerius[]){
    ifstream data("U1.txt");
    data >> stociu_kiekis;
    for(int i = 0; i<stociu_kiekis; i++){
        data >> stoties_numeriai[i];
        data >> stoties_dienos_pagal_numerius[i];
        data >> ilipimai_pagal_numerius[i];
        data >> islipimai_pagal_numerius[i];
    }
    data.close();
}

void sort(int stoteles[], int stoteliu_kiekis, int ilipimai[]){
    for(int i = 0; i<stoteliu_kiekis; i++){
        for(int j = 0; j<stoteliu_kiekis-i-1; j++){
            if(stoteles[j] > stoteles[j+1]){
                swap(stoteles[j],stoteles[j+1]);
                swap(ilipimai[j],ilipimai[j+1]);
            }
        }
    }
}

int find_max_indicator(int stociu_kiekis, int islipimai[]){
    int max_i = 0;
    for(int i = 0; i<stociu_kiekis; i++){
        if(islipimai[i] > islipimai[max_i]){
            max_i = i;
        }
    }
    return max_i;
}

int suma(int stociu_kiekis, int ilipimai[]){
    int sum = 0;
    for(int i = 0; i<stociu_kiekis; i++){
        sum+=ilipimai[i];
    }
    return sum;
}

void rez(int stociu_kiekis, int stoties_numeriai[], int stoties_islipimai[], int max_indicator, int sum){
    ofstream rez("U1rez.txt");
    for(int i = 0; i<stociu_kiekis; i++){
        rez << setw(6) << stoties_numeriai[i] << " ";
    }
    rez << endl;
    for(int i = 0; i<stociu_kiekis; i++){
        rez << setw(6) << stoties_islipimai[i] << " ";
    }
    rez << endl;
    rez << setw(6) << stoties_numeriai[max_indicator] << endl;
    rez << setw(6) << sum << endl;
}

int main(){
    int duom_stociu_kiekis;
    int duom_stoties_numeriai[100];
    int duom_stoties_dienos_pagal_numerius[100];
    int duom_ilipimai_pagal_numerius[100];
    int duom_islipimai_pagal_numerius[100];
    skaitymas(duom_stociu_kiekis,duom_stoties_numeriai,duom_stoties_dienos_pagal_numerius,duom_ilipimai_pagal_numerius,duom_islipimai_pagal_numerius);
    int stociu_kiekis = 0;
    int stoties_numeriai[100] = {0};
    int stoties_islipimai[100] = {0};


    subtract_data(duom_stociu_kiekis,
                  duom_stoties_numeriai,
                  duom_ilipimai_pagal_numerius,
                  duom_islipimai_pagal_numerius,
                  stociu_kiekis, stoties_numeriai,
                  stoties_islipimai);
    sort(stoties_numeriai, stociu_kiekis, stoties_islipimai);

    int max_indikatorius = find_max_indicator(stociu_kiekis, stoties_islipimai);
    int sum = suma(duom_stociu_kiekis, duom_ilipimai_pagal_numerius);

    rez(stociu_kiekis, stoties_numeriai, stoties_islipimai, max_indikatorius, sum);
    cout << max_indikatorius << endl;

    for(int i = 0; i<stociu_kiekis; i++){
        cout << stoties_numeriai[i] << " " << stoties_islipimai[i] << endl;
    }

    return 0;
}

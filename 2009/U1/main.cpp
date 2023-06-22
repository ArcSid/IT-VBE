#include <fstream>
using namespace std;
void spausdinimas(int nominalu_kiekis_gilijos, int nominalu_kiekis_eglijos,
                  int kiek_monetu_gilijos_mokinys,
                  int kiek_monetu_eglijos_mokinys,
                  int kiek_gavo_gilijos_nuo_eglijos[],
                  int kiek_gavo_eglijos_nuo_gilijos[],
                  int gilijos_nominalu_sarasas[],
                  int eglijos_nominalu_sarasas[]) {
  ofstream rez("U1rez.txt");
  for (int i = 0; i < nominalu_kiekis_eglijos; i++) {
    rez << eglijos_nominalu_sarasas[i] << " "
        << kiek_gavo_gilijos_nuo_eglijos[i] << endl;
  }
  rez << kiek_monetu_gilijos_mokinys << endl;
  for (int i = 0; i < nominalu_kiekis_gilijos; i++) {
    rez << gilijos_nominalu_sarasas[i] << " "
        << kiek_gavo_eglijos_nuo_gilijos[i] << endl;
  }
  rez << kiek_monetu_eglijos_mokinys << endl;
}

int keitimas(int nominalu_kiekis, int pinigu_suma, int nominalai[],
             int panaudojimas[]) {
  int monetu_suma = 0;
  for (int i = 0; i < nominalu_kiekis; i++) {
    int kiek_kartu_panaudota = 0;
    while (pinigu_suma >= nominalai[i]) {
      pinigu_suma -= nominalai[i];
      kiek_kartu_panaudota++;
      monetu_suma++;
    }
    panaudojimas[i] = kiek_kartu_panaudota;
  }
  return monetu_suma;
}

int sumavimas(int nominalu_kiekis, int nominalu_sarasas[],
              int studento_pinigai_pagal_nominala[]) {
  int suma = 0;
  for (int i = 0; i < nominalu_kiekis; i++) {
    suma += nominalu_sarasas[i] * studento_pinigai_pagal_nominala[i];
  }
  return suma;
}

void skaitymas(int gilijos_nominalu_sarasas[],
               int gilijos_mokinio_turimos_monetos_pagal_nominalus[],
               int &gilijos_nominalai, int eglijos_nominalu_sarasas[],
               int eglijos_mokinio_turimos_monetos_pagal_nominalus[],
               int &eglijos_nominalai) {
  fstream data("U1.txt");
  data >> gilijos_nominalai;
  for (int i = 0; i < gilijos_nominalai; i++) {
    data >> gilijos_nominalu_sarasas[i];
  }
  for (int i = 0; i < gilijos_nominalai; i++) {
    data >> gilijos_mokinio_turimos_monetos_pagal_nominalus[i];
  }
  data >> eglijos_nominalai;
  for (int i = 0; i < eglijos_nominalai; i++) {
    data >> eglijos_nominalu_sarasas[i];
  }
  for (int i = 0; i < eglijos_nominalai; i++) {
    data >> eglijos_mokinio_turimos_monetos_pagal_nominalus[i];
  }
}

int main() {
  int gilijos_nominalu_sarasas[50];
  int gilijos_mokinio_turimos_monetos_pagal_nominalus[50];
  int gilijos_nominalai = 0;
  int kiek_gavo_gilijos_nuo_eglijos[50];

  int eglijos_nominalu_sarasas[50];
  int eglijos_nominalai = 0;
  int eglijos_mokinio_turimos_monetos_pagal_nominalus[50];
  int kiek_gavo_eglijos_nuo_gilijos[50];
  skaitymas(gilijos_nominalu_sarasas,
            gilijos_mokinio_turimos_monetos_pagal_nominalus, gilijos_nominalai,
            eglijos_nominalu_sarasas,
            eglijos_mokinio_turimos_monetos_pagal_nominalus, eglijos_nominalai);

  int gilijos_mokinio_pinigu_suma =
      sumavimas(gilijos_nominalai, gilijos_nominalu_sarasas,
                gilijos_mokinio_turimos_monetos_pagal_nominalus);
  int eglijos_mokinio_pinigu_suma =
      sumavimas(eglijos_nominalai, eglijos_nominalu_sarasas,
                eglijos_mokinio_turimos_monetos_pagal_nominalus);

  int kiek_monetu_gilijos_mokinys =
      keitimas(eglijos_nominalai, gilijos_mokinio_pinigu_suma,
               eglijos_nominalu_sarasas, kiek_gavo_gilijos_nuo_eglijos);
  int kiek_monetu_eglijos_mokinys =
      keitimas(gilijos_nominalai, eglijos_mokinio_pinigu_suma,
               gilijos_nominalu_sarasas, kiek_gavo_eglijos_nuo_gilijos);

  spausdinimas(gilijos_nominalai, eglijos_nominalai,
               kiek_monetu_gilijos_mokinys, kiek_monetu_eglijos_mokinys,
               kiek_gavo_gilijos_nuo_eglijos, kiek_gavo_eglijos_nuo_gilijos,
               gilijos_nominalu_sarasas, eglijos_nominalu_sarasas);
}
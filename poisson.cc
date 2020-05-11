#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;


double poisson(double mu, int k) {
    double a = pow(mu, k);
    double b = exp(-mu);
    double c = tgamma(k+1);
    return (a*b)/c;
}

int main() {
  // Datei laden
    ifstream fin("datensumme.txt");
    ofstream fout("hist.txt");

  // Vektor füllen
    vector<int> zaehler(11);
    int n_i;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        zaehler[n_i]+=1;
    }
    fin.close();

  // Vektor ausgeben
  for (int i=0; i<zaehler.size(); ++i)
  {
    double wahr = poisson(i, 3.11538);
    fout << i << "\t" << zaehler[i] << "\t" << 234*wahr;
    if (i<zaehler.size()-1)
    {
      fout << "\n";
    }
  }
}
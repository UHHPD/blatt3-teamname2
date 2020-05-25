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

double prob(vector<int> daten, double mu)
{
  double L=1;
  for (int k : daten)
  {
    L*=poisson(mu, k);
  }
  return L;
}

double norm(vector<int> daten)
{
  double L=1;
  for (int k : daten)
  {
    L*=poisson(k, k);
  }
  return L; 
}

int main() {

    

    ifstream fin("datensumme.txt");
    vector<int> messwerte;
    int n_i;
    for(int i = 0 ; i < 234 ; ++i) {
        fin >> n_i;
        messwerte.push_back(n_i);
    }
    fin.close();

    ofstream fout("likelihood.txt");
    ofstream fout2("nll.txt");
    ofstream fout3("deltanll.txt");
    for(int i=0; i<=60; ++i)
    {
      double mu = i*0.1;
      double l = prob(messwerte, mu);
      fout<<mu<<"\t"<<l;
      fout2<<mu<<"\t"<<(-2*log(l));

      //Minimum bei 3.1+-0.1
      fout3<<mu<<"\t"<<(-2*log(l)+2*log(prob(messwerte, 3.11538)));
      if (i<60)
      {
        fout<<"\n";
        fout2<<"\n";
        fout3<<"\n";
      }
    }
    fout.close();
    fout2.close();
    fout3.close();

    double Lambda = prob(messwerte, 3.11538)/norm(messwerte);
    cout<<"L(mu): "<<prob(messwerte, 3.11538)<<"\n";
    cout<<norm(messwerte)<<"\n";
    cout<<"Lambda: " << Lambda << "\n";
    cout<< "-2*ln(Lambda):" << -2*log(Lambda) <<"\n";
    cout<<"z = "<< (-2*log(Lambda)-233)/sqrt(466) << "\n";
    
}
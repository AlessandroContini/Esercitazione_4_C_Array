#include "Utils.hpp"

#include "iostream"
#include "fstream"
#include "sstream"
#include <vector>
#include <iomanip>

using namespace std;

bool ImportData(const string& inputFilePath,
				double& S,
				unsigned int& n, 
				double*& w,
				double*& r)
{
	ifstream fstr(inputFilePath);
	
	if(fstr.fail())
		return false;
	
	string tmp;
	//prima riga
	getline(fstr, tmp); //legge la prima riga
	stringstream ss1(tmp); //dalla prima riga estrae due stringhe separate dal ';'
	string totalsum, value;
	getline(ss1, totalsum, ';'); //legge la prima stringa creata (totalsum)
	getline(ss1, value); //legge la seconda stringa creata (value)
	S = stod(value); //trasforma la stringa value in un double
	
	//seconda riga
	getline(fstr, tmp);
	stringstream ss2(tmp);
	string numassets, number;
	getline(ss2, numassets, ';');
	getline(ss2, number);
	n = stoi(number); //trasforma la stringa number in un intero
	
	//terza riga
	getline(fstr, tmp);
	
	//dati
	vector<double> pesi; //inizializzo due vettori vuoti associati a pesi e rendimenti
	vector<double> rendimenti;
	
	
	while(getline(fstr, tmp)){
		stringstream ss(tmp);
        string pesoStr, rendimentoStr;
		
        getline(ss, pesoStr, ';');
		getline(ss, rendimentoStr);
		double peso = stod(pesoStr);
		double rendimento = stod(rendimentoStr);

		pesi.push_back(peso);
		rendimenti.push_back(rendimento);
	}
	
	fstr.close();
	
	w = new double[n];
	r = new double[n];

	for (unsigned int i = 0; i < n; ++i) {
		w[i] = pesi[i];
		r[i] = rendimenti[i];
	}
	
	return true;
}

double rateOfReturn(const unsigned int& n,
					const double* const& w,
					const double* const& r)
{
	double rate_of_return = 0.0;
    for (unsigned int i = 0; i < n; ++i) {
        rate_of_return += w[i] * r[i]; //calcolo il rendimento
    }
	
	return rate_of_return;
}


bool ExportResult(const string& outputFilePath,
				  const double& S,
				  const unsigned int& n, 
				  const double* const& w,
				  const double* const& r,
				  const double& rateOfReturn)
{
	ofstream file;
    file.open(outputFilePath);

    if (file.fail())
    {
        cerr<< "file open failed"<< endl;
        return false;
    }
	
	file << "S = " << fixed << setprecision(2) << S << ", n = " << n << endl;
	file.unsetf(ios::fixed);
	file << "w = [ ";
	for (unsigned int i = 0; i < n; ++i)
		file << w[i] << " ";
	file << "]" << endl;
	
	file << "r = [ ";
	for (unsigned int i = 0; i < n; ++i)
		file << r[i] << " ";
	file << "]" << endl;
	
	file << "Rate of return of the portfolio: " << setprecision(4) << rateOfReturn << endl;
	
	double V = S * (1 + rateOfReturn); //Valore finale V=(1+r)*S
	file << "V: " << fixed << setprecision(2) << V << endl;
	
	file.close();
	return true;
}

string ArrayToString(const unsigned int& n,
                     const double* const& v)
{
    string str;
    ostringstream toString;
    toString << "[ ";
    for (unsigned int i = 0; i < n; i++)
        toString<< v[i]<< " ";
    toString << "]";

    return toString.str();
}
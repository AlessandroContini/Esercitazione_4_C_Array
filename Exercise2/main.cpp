#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Utils.hpp" 

using namespace std;

int main()
{
	string inputFile = "data.txt";
	string outputFile = "result.txt";
	double S;
	unsigned int n;
	double* ptr1 = nullptr;
	double* ptr2 = nullptr;
	
	if(!ImportData(inputFile, S, n, ptr1, ptr2)){
		cerr << "Errore nell'apertura del file" << endl;
		return 1;
	}
	
	double r = rateOfReturn(n, ptr1, ptr2);
	double V = S * (1+r);
	
	if (!ExportResult(outputFile, S, n, ptr1, ptr2, r)) {
        cerr << "Errore nella scrittura del file." << endl;
        delete[] ptr1;
        delete[] ptr2;
        return 1;
    }
	
	cout << "S = " << fixed << setprecision(2) << S << ", n = " << n << endl;
	cout << "w = " << ArrayToString(n, ptr1) << endl;
	cout << "r = " << ArrayToString(n, ptr2) << endl;
	cout << "Rate of return of the portfolio: " << fixed << setprecision(4) << r << endl;
	cout << "V: " << fixed << setprecision(2) << V << endl;
	
	delete[] ptr1;
	delete[] ptr2;
	
    return 0;
}


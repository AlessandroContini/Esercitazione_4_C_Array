#pragma once

#include<iostream>

using namespace std;

bool ImportData(const string& inputFilePath,
				double& S,
				unsigned int& n, 
				double*& w,
				double*& r);
				
double rateOfReturn(const unsigned int& n,
					const double* const& w,
					const double* const& r);

bool ExportResult(const string& outputFilePath,
				  const double& S,
				  const unsigned int& n, 
				  const double* const& w,
				  const double* const& r,
				  const double& rateOfReturn);
				  
string ArrayToString(const unsigned int& n,
                     const double* const& v);
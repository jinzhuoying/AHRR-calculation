#include <iostream>
#include <fstream>
#include <cmath>
#include "volume.cpp"
#define PI 3.14159
using namespace std;


double p(double);
double dpdCA(double);
double V(double);
double dVdCA(double _CA);

double T0=300; //Unit:K

int main()
{
	ofstream OF("test.txt",ios::out);
int N=1440;//the number of data points

	double DX=0.5;
	double T=N*DX;

	double *CA 		= new double [N];
	double *p		= new double [N];
	double *_dVdCA	= new double [N];
	double *_dpdCA	= new double [N];
	double *_V		= new double [N];
	
/////////////////////////////////////////// Read Cylinder Pressure
	ifstream IF("PressureFile.txt",ios::in);
	if(!IF)
	{
		cout<<"file open error! pre_pressure.cpp"<<endl;
		system("pause");
		exit(0);
	}
	IF.clear();

	for(int i = 0; i < N; i++)
	{
		char c = 0;
		IF >> CA[i] >> p[i];
		p[i] *= 1e5;
		_dVdCA[i] = dVdCA(CA[i]);
		_V[i] = V(CA[i]);

		do
		{
			c=IF.get();
		}while((c!='\n')&&(IF.good()));
		if(!IF.good())
		{
			cout<<"pre_pressure.cpp! IF.rdstate:"<<IF.rdstate()<<endl;
			system("pause");
			exit(0);
		}
	}
	IF.close();
//////////////////////////////////////////////// Reading Cylinder Pressure

//////////////////////////////////////////////// Calculate _dpdCA and _dp2dCA

	_dpdCA[0] = 0;
	for(int i = 1; i < N; i++)
	{
		_dpdCA[i] = (p[i] - p[i-1])/(CA[i] - CA[i-1]);
	}

	
	OF<<"i"<<'\t'<<"T"<<'\t'<<"p(i)"<<'\t'<<"dpdCA(i)"<<'\t'<<"V(i)"<<'\t'<<"dVdCA(i)"<<'\t'<<"dqdCA"<<'\t'<<endl;
	 for(int i = 0; i < 1440; i++)
	 {
		 double T = p[i]*_V[i]*T0/p[431]/_V[431]; //the reference temperature corresponding to IVC time
		 double gamma = 1.38-0.08*(T-300)/1000;

		 double dqdCA=gamma/(gamma-1)*p[i]*_dVdCA[i]+1/(gamma-1)*_V[i]*_dpdCA[i];

		OF<<i<<'\t'<<T<<'\t'<<p[i]<<'\t'<<_dpdCA[i]<<'\t'<<_V[i]<<'\t'<<_dVdCA[i]<<'\t'<<dqdCA<<'\t'<<endl;
		 cout<<i<<endl;
	 }
	 
	delete [] CA;
	delete [] p;
	delete [] _dVdCA;
	delete [] _dpdCA;
	delete [] _V;

	return 0;
}

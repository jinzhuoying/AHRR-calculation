#include<iostream>
#include<cmath>
using namespace std;
double V(double _CA)//Unit:m3
{
	double r=0.065;//Unit:m
	double l=0.216;//Unit:m
	double CR=18;
	double bore=0.114;//Unit:m
	double h=r+l-(r*cos(_CA/180*3.14159)+l*sqrt(1-pow(r/l*sin(_CA/180*3.14159),2)))+2*r/(CR-1);//Unit:m
	return 3.14159*bore*bore*h/4.0;
}

double dVdCA(double _CA)
{
	double r=0.065;//Unit:m
	double l=0.216;//Unit:m
	double CR=18;
	double bore=0.114;//Unit:m
	double dhdCA=r*sin(_CA*3.14159/180)+l*r*r/l/l*pow(1-pow(r/l*sin(_CA/180*3.14159),2),-0.5)*sin(_CA*3.14159/180)*cos(_CA*3.14159/180);
	return 3.14159*bore*bore*dhdCA/4.0*3.14159/180;
}

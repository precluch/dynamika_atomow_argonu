#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <time.h>
#include "argon.h"

using namespace std;

int main(int argc,char *argv[]){
	
	int f=1;
	string par, HVT, XYZ;

	if (argc<3){
		cout << "Podaj plik z parametrami" << endl;
		cin >> par;
		cout << "Podaj plik na srednie HVTP" << endl;
		cin >> HVT;
		cout << "Podaj plik na polozenia" << endl;
		cin >> XYZ;
		f=0;
	}
	clock_t tp = clock();
	Argon a;

	if(f)
		a.getParam(argv[1]);
	else
		a.getParam(par.data());

	a.init();

	//a.test(argv[2]);
	
	if(f){
		a.sim(argv[2], argv[3]);
	}
	else{
		a.sim(HVT.data(), XYZ.data());
	}
	
	cout << "T0 = " << a.getT0() << endl;
	cout << "T_sr = " << a.getT_sr() << endl;
	cout << "H_sr = " << a.getH_sr() << endl;
	cout << "P_sr = " << a.getP_sr() << endl;

	clock_t tk = clock() - tp;
	cout << endl << "Obliczenia trwaly " << (tk/CLOCKS_PER_SEC) << " s" << endl;
	
	return 0;
}

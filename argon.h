#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include "vector.h"

using namespace std;

class Argon{
	public:
	
		int n;				//liczba atomow na krawedzi
		int N;				//liczba wszystkich atomow
		double m0;			//masa atomu
		double e;			//
		double L;			//promien kuli
		double f;			//stala sprezystosci
		double RR;			//odleglosc miedzy atomami
		double a;			//stala sieciowa
		double T0;			//temperatura poczatkowa
		double t;			//czas chwilowy
		double tau;			//krok czasowy
		double kB;			//stala Boltzmana
		double P;			//cisnienie wywierane na kule
		double V;			//en. potencjalna
		double E;			//en. kinetyczna
		double T;			//temperatura chwilowa
		int So;				//
		int Sd;				//
		int Sout;			//
		int Sxyz;			//
		double T_sr;		//srednia temperatura
		double P_sr;		//srednie cisnienie
		double H_sr;		//sredni hamiltonian

		vector b[3];		//wektory sieciowe
		vector *R;			//wektory polozen
		vector *F;			//wektory sil
		vector *p;			//wektory polozen		
		
		Argon();
		~Argon();
		
		void init();
		void getVFP();
		void getFW(vector u, vector uF, vector w, vector wF);
		void getFP(vector w, vector wF);
		void getParam(string paramFile);

		double getVW(vector u, vector w);
		double getVP(vector w);
		double getV();
		double getP();
		double getT_sr();
		double getP_sr();
		double getH_sr();
		double getT0();
		
		void write(vector *v, const char *name);
		void writeR(const char *name);

		void test(string f1);
		void sim(string f1, string f2);
};

#include "argon.h"

using namespace std;

Argon::~Argon(){
	delete[] R;
	delete[] p;
	delete[] F;
}

Argon::Argon(){
	n=10; N=1000; m0=39.948; kB=0.00831; e=1; L=4; f=10000;								//inicjalizacja parametrow ukladu
	a=0.37317; T0=1000;																	//inicjalizacja parametrow stanu poczatkowego
	t=0.0; tau=0.001; P=0.0; V=0.0; E=0.0; T=0.0; So=2000; Sd=5000;						//inicjalizacja parametrow dynamiki
	T_sr=0.0; P_sr=0.0; H_sr=0.0;
	Sout=10; Sxyz=10;																	//inicjalizacja parametrow wyjscia

	R = new vector [N];
	p = new vector [N];
	F = new vector [N];

	
	for(int i=0; i<N; i++){
		R[i].x=0.; R[i].y=0.; R[i].z=0.;												//zerowanie
		p[i].x=0.; p[i].y=0.; p[i].z=0.;												//wektorow
		F[i].x=0.; F[i].y=0.; F[i].z=0.;												//R, p i F
  }
}

void Argon::init(){
	srand48(time(NULL));
	double l=sqrt(3*T0*m0*kB);
  
	b[0].x=a;		b[0].y=0.;				b[0].z=0.;									//inicjalizacja
	b[1].x=a/2.;	b[1].y=a*sqrt(3.)/2.;	b[1].z=0.;									//wektorow
	b[2].x=a/2.;	b[2].y=a*sqrt(3.)/6.;	b[2].z=a*sqrt(2./3.);						//bazowych
		
	int m=0;																			//poczatkowe polozenia i pedy
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			for(int k=0; k<n; k++){
				R[m].x=(i-(n-1)/2)*b[0].x+(j-(n-1)/2)*b[1].x+(k-(n-1)/2)*b[2].x;		//skladowa x-owa R
				R[m].y=(i-(n-1)/2)*b[0].y+(j-(n-1)/2)*b[1].y+(k-(n-1)/2)*b[2].y;		//skladowa y-owa R
				R[m].z=(i-(n-1)/2)*b[0].z+(j-(n-1)/2)*b[1].z+(k-(n-1)/2)*b[2].z;		//skladowa z-owa R

				p[m].x=l*(2.*drand48()-1.);												//skladowa x-owa p
				p[m].y=l*(2.*drand48()-1.);												//skladowa y-owa p
				p[m].z=l*(2.*drand48()-1.);												//skladowa z-owa p
				m++;
			}
		}
	}
  
	write(&p[0], "p.dat");
}
void Argon::getVFP(){
	vector uw, zero(.0,.0,.0);
	double ruw, r;
	V=.0;
	P=.0;

	for(int i=0; i<N; ++i)
		F[i]=zero;

	for(int i=0; i<N; ++i){
		V+=getVP(R[i]);
		r=R[i].length();
		if(r>=L){
			F[i]=(f*(L-r)/r)*R[i];
			P+=F[i].length();
		}
		for(int j=0; j<i; ++j){
			V+=getVW(R[i],R[j]);
			uw=R[i]-R[j];
			ruw=uw.length();
			F[i]+=uw*(12*e*(pow(RR/ruw,12)-pow(RR/ruw,6))/pow(ruw,2));
			uw=R[j]-R[i];
			F[j]+=uw*(12*e*(pow(RR/ruw,12)-pow(RR/ruw,6))/pow(ruw,2));
		}
	}
	P/=(4.*M_PI*pow(L,2));
}

void Argon::getFW(vector u, vector uF, vector w, vector wF){
	vector v(.0,.0,.0);
	double ruw;

	v=u-w;
	ruw=v.length();
	uF+=(12*e*(pow(RR/ruw,12)-pow(RR/ruw,6))/pow(ruw,2))*v;

	v=w-u;
	ruw=v.length();
	wF+=(12*e*(pow(RR/ruw,12)-pow(RR/ruw,6))/pow(ruw,2))*v;
}

void Argon::getFP(vector w, vector wF){
	double r=w.length();
	if(r>=L){
		wF+=(f*(L-r)/r)*w;
		P+=wF.length();
	}
}
		
void Argon::getParam(string paramFile){
	ifstream fileOut(paramFile.c_str());
	fileOut>>n>>N>>m0>>e>>L>>f>>RR>>a>>T0>>tau>>So>>Sd>>Sout>>Sxyz;
	fileOut.close();
}

double Argon::getVW(vector u, vector w){
	double ruw=(u-w).length();
	return e*(pow(RR/ruw,12)-2*pow(RR/ruw,6));
}

double Argon::getVP(vector w){
	double r=w.length();
	if(r<L)
		return 0;
	else
		return f*pow((r-L),2)*.5;
}

double Argon::getV(){return V;}

double Argon::getP(){return P;}

double Argon::getT_sr(){return T_sr;}

double Argon::getP_sr(){return P_sr;}

double Argon::getH_sr(){return H_sr;}

double Argon::getT0(){return T0;}

void Argon::write(vector *v, const char *name){
	fstream file;
	file.open(name, ios::in | ios::out | ios::app);
	
	for(int i=0; i<N; i++)
		file << v[i].x << "\t" << v[i].y <<"\t" << v[i].z << endl;
	
	file << endl << endl;
	file.close();
}

void Argon::writeR(const char *name){
	fstream file;
	file.open(name, ios::in | ios::out | ios::app);
	for(int i=0; i<N; i++){
 		file << R[i].x << "\t" << R[i].y << "\t" << R[i].z << endl;
		
	}
	file.close();
}

void Argon::test(string f1){
	ofstream of1(f1.c_str());
	of1 << "a\tV" << endl;
	
	double l=sqrt(3*T0*m0*kB);
	for(int i=0; i<1000; ++i){
		a = 0.37 + i*0.00001;
		
		b[0].x=a;		b[0].y=0.;				b[0].z=0.;								//inicjalizacja
		b[1].x=a/2.;	b[1].y=a*sqrt(3.)/2.;	b[1].z=0.;								//wektorow
		b[2].x=a/2.;	b[2].y=a*sqrt(3.)/6.;	b[2].z=a*sqrt(2./3.);					//bazowych
	
		for(int i=0; i<N; i++){
			R[i].x=0.; R[i].y=0.; R[i].z=0.;											//zerowanie
			p[i].x=0.; p[i].y=0.; p[i].z=0.;											//wektorow
			F[i].x=0.; F[i].y=0.; F[i].z=0.;											//R, p i F
		}

		int m=0;																		//poczatkowe polozenia i pedy
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				for(int k=0; k<n; k++){
					R[m].x=(i-(n-1)/2)*b[0].x+(j-(n-1)/2)*b[1].x+(k-(n-1)/2)*b[2].x;	//skladowa x-owa R
					R[m].y=(i-(n-1)/2)*b[0].y+(j-(n-1)/2)*b[1].y+(k-(n-1)/2)*b[2].y;	//skladowa y-owa R
					R[m].z=(i-(n-1)/2)*b[0].z+(j-(n-1)/2)*b[1].z+(k-(n-1)/2)*b[2].z;	//skladowa z-owa R
	
					p[m].x=l*(2.*drand48()-1.);											//skladowa x-owa p
					p[m].y=l*(2.*drand48()-1.);											//skladowa y-owa p
					p[m].z=l*(2.*drand48()-1.);											//skladowa z-owa p
					m++;
				}
			}
		}
		
		getVFP();		
		of1 << a << "\t" << V << endl;
	}
	of1.close();
}
void Argon::sim(string f1, string f2){
	getVFP();
	double Ekin=.0, t=.0, H=.0;

	T_sr=.0;
	P_sr=.0;
	H_sr=.0;

	ofstream fo1(f1.c_str());
	//fo1 << "t\tH\tV\tT\tP" << endl;

	ofstream fo2(f2.c_str());

	for(int s=0; s<So+Sd; ++s){
		Ekin=.0;
		H=.0;

		for(int i=0; i<N; ++i){
			p[i]+=.5*tau*F[i];
			R[i]+=(tau/m0)*p[i];
		}

		getVFP();

		for(int i=0; i<N; ++i){
			p[i]+=.5*tau*F[i];
			Ekin+=pow(p[i].length(), 2);
		}

		Ekin/=(2.0*m0);
		T=(2.0*Ekin)/(3.0*N*kB);
		H=V+Ekin;

		if(s%Sout==0){
			fo1 << t << "\t" << H << "\t" << V << "\t" << T << "\t" << P << endl;
		}

		if(s%Sxyz==0){
			for (int i=0;i<N;++i){
				fo2 << R[i].x << "\t" << R[i].y << "\t" << R[i].z << endl;
			}
		}

		if(s >= So){
			T_sr+=T;
			P_sr+=P;
			H_sr+=H;
		}
		t+=tau;
	}

	T_sr/=Sd;
	P_sr/=Sd;
	H_sr/=Sd;
	
	fo1.flush();
	fo2.flush();

	fo1.close();
	fo2.close();
}

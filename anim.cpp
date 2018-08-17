#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>


#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

using namespace std;

double l=3;										// rozmiar ekranu
int step;										// liczba krokow
int displayInterval=1;							// czestotliwosc wyswietlania
const double pi=4*atan(1.0);					// zmienna pomocnicza
double radius = 0.15;                      		// promien atomu argonu
double minExtent[3], maxExtent[3];        		// rozciaglosc ukladu
int xWindowSize = 800, yWindowSize = 800; 		// rozmiar okna
GLdouble aspectRatio;                     		// window aspect ratio
GLdouble fovy, nearClip, farClip;         		// pomocnicze do wyswietlania 3D
GLdouble eye[3], center[3], up[3];        		// jw
GLuint sphereID, configID;                		// identyfikacja
int phi, theta;                           		// katy do obrotu strzalkami
int angle=5;                            		// kat obrotu w stopniach
int pos=0;										// aktualna pozycja w pliku z danymi
double Ar[10000];								// tablica pedow atomow
ifstream datafile;								// plik wejsciowy z danymi XYZ
bool running=false;								// zmienna pomocnicza			
	
int n;											// liczba atomow na krawedzi
int N;											// liczba wszystkich atomow
double m0;										// masa atomu
double e;										// -eps to min potencjal
double RR;										// odleglosc miedzyatomowa
double f;										// stala sprezystosci
double L;										// promien kuli
double a;										// odleglosc miedzy atomami
double T0;
double tau;
int So;
int Sd;
int Sout;
int Sxyz;


void getParameters(string paramFile){
	ifstream fileOut(paramFile.c_str());
	fileOut>>n>>N>>m0>>e>>L>>f>>RR>>a>>T0>>tau>>So>>Sd>>Sout>>Sxyz;
	fileOut.close();
}

void makeAtom(GLuint listID,double radius){
	int nTheta=9;                       		// polar slices
	int nPhi=18;                        		// azimuthal slices
	glNewList(listID,GL_COMPILE);
	glutSolidSphere(radius,nPhi,nTheta);
	glEndList();
}

void makeCrystal(){
	glNewList(configID,GL_COMPILE);
	glColor3f(0.97,.5,1.);             			// kolor atomu
	glPushMatrix();
	glRotated(phi,0,1,0);              			// obrot wzdluz osi y
    	glPushMatrix();
    	glRotated(theta, 1, 0, 0);            	// obrot wzdluz osi x
    	for (int i=0;i<3*N;i+=3){
	        glPushMatrix();
	        glTranslated(Ar[i],Ar[i+1],Ar[i+2]);
	        glCallList(sphereID);
	        glPopMatrix();
	}
	glColor3ub(130,130,200);            	
	glutWireSphere(L, 32, 32);					// naczynie sferyczne
	glPopMatrix();
	glPopMatrix();
	glEndList();
}

void takeStep(){
	++step;
	do{
		for (int i=0;i<3*N;i+=3){
			datafile>>Ar[i]>>Ar[i+1]>>Ar[i+2];
		}
		pos+=N;
	}while (!datafile.eof() && pos%N!=0);

	if (step%displayInterval==0){
        	makeCrystal();
        	glutPostRedisplay();
    	}
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(eye[0],eye[1],eye[2],center[0],center[1],center[2],up[0],up[1],up[2]);
	glCallList(configID);                	 // rysuj atomy
	glutSwapBuffers();
}

void reshape(int w,int h){
    	glViewport(0,0,w,h);
    	aspectRatio=w/double(h);
    	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
    	gluPerspective(fovy, aspectRatio, nearClip, farClip);
    	glMatrixMode(GL_MODELVIEW);
}

void initView(double *minExtent, double *maxExtent){

    // pojedyncze zrodlo swiatla
	GLfloat lightDiffuse[]={1.0,1.0,1.0,1.0};
	GLfloat lightPosition[]={0.5,0.5,1.0,0.0};
	glLightfv(GL_LIGHT0,GL_DIFFUSE,lightDiffuse);
	glLightfv(GL_LIGHT0,GL_POSITION,lightPosition);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);              
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

    // obliczanie skali sceny
	double difExtent[3];
	for (int i=0;i<3;++i)
        	difExtent[i]=maxExtent[i]-minExtent[i];
    double dist=0;
    for (int i=0;i<3;++i)
       	dist+=difExtent[i]*difExtent[i];
    dist=sqrt(dist);

    // ustalenie srodka, pozycji kamery i orientacji
    for (int i=0;i<3;++i)
    center[i]=minExtent[i]+difExtent[i]/2;
    eye[0]=center[0]+dist*1.5;
    eye[1]=center[1];
    eye[2]=center[2];
    up[0]=0;
    up[1]=1;
    up[2]=0;

    // ustawienia pola widzenia
	nearClip=(dist-difExtent[2]/2)/2;
	farClip=2*(dist+difExtent[2]/2);
    fovy=difExtent[1]/(dist-difExtent[2]/2)/2;
    fovy=2*atan(fovy)/pi*180;
    fovy*=1.2;
}

void special(int key,int x,int y){
	switch(key){
      	case GLUT_KEY_LEFT:	
			phi=(phi-angle)%360;      
			break;
		case GLUT_KEY_RIGHT:
			phi=(phi+angle)%360;
			break;
      	case GLUT_KEY_UP:
			theta=(theta-angle)%360;
			break;
      	case GLUT_KEY_DOWN:
			theta=(theta+angle)%360;
			break;
      	default: 
			break;
    	}
}

void mouse(int button,int state,int x,int y){
	switch (button){
		case GLUT_LEFT_BUTTON:
			if (state==GLUT_DOWN){
				if (running){
					glutIdleFunc(NULL);
					running=false;
				} else{
					glutIdleFunc(takeStep);
					running=true;
				}
			}
	}
}

int main(int argc, char *argv[]){
	int f=1;
	string par, rrr;

	if (argc<2){
		cout << "Podaj plik z parametrami" << endl;
		cin >> par;
		cout << "Podaj plik na polozenia" << endl;
		cin >> rrr;
		f=0;
	}

	if(f){
		getParameters(argv[1]);
		datafile.open(argv[2],ifstream::in);
	}
	else{
		getParameters(par.data());
		datafile.open(rrr.data());
	}

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(xWindowSize, yWindowSize);
	glutCreateWindow("Symulacje krysztalu argonu metoda dynamiki molekularnej");

	for (int i=0;i<3;++i){
		minExtent[i]=-l/2;
		maxExtent[i]=l/2;
	}

	initView(minExtent,maxExtent);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutMouseFunc(mouse);

	sphereID=glGenLists(1);
	makeAtom(sphereID,radius);
	configID=glGenLists(1);
	makeCrystal();

	glutMainLoop();
	
	datafile.close();
}

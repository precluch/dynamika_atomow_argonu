#include "vector.h"
#include <math.h>

double vector::length() const{
	return sqrt(pow(this->x,2)+pow(this->y,2)+pow(this->z,2));
}

double vector::getX(){return this->x;}
double vector::getY(){return this->y;}
double vector::getZ(){return this->z;}

vector& vector::operator=(const vector& w){
	this->x=w.x;
	this->y=w.y;
	this->z=w.z;
	return *this;
}

vector& vector::operator+=(const vector& w){
	this->x=w.x+this->x;
	this->y=w.y+this->y;
	this->z=w.z+this->z;
	return *this;
}

vector& vector::operator-=(const vector& w){
	this->x=this->x-w.x;
	this->y=this->y-w.y;
	this->z=this->z-w.z;
	return *this;
}

vector& vector::operator/(double c){
	this->x=this->x/c;
	this->y=this->y/c;
	this->z=this->z/c;
	return *this;
}

vector& vector::operator*(double c){
	this->x=this->x*c;
	this->y=this->y*c;
	this->z=this->z*c;
	return *this;
}

vector operator+(const vector& u,const vector& w){
	vector vec;
	vec.x=u.x+w.x;
	vec.y=u.y+w.y;
	vec.z=u.z+w.z;
	return vec;
}

vector operator-(const vector& u,const vector& w){
	vector vec;
	vec.x=u.x-w.x;
	vec.y=u.y-w.y;
	vec.z=u.z-w.z;
	return vec;
}

vector operator*(double c,const vector& w){
	vector vec;
	vec.x=c*w.x;
	vec.y=c*w.y;
	vec.z=c*w.z;
	return vec;
}

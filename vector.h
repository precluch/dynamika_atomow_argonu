class vector
{
	public:
		double x, y, z;
		vector(): x(.0), y(.0), z(.0){}
		vector(double xx, double yy, double zz): x(xx), y(yy), z(zz){}

		double length() const;
		double getX();
		double getY();
		double getZ();
		vector& operator=(const vector& w);
		vector& operator+=(const vector& w);
		vector& operator-=(const vector& w);
		friend vector operator+(const vector&,const vector&);
		friend vector operator-(const vector&,const vector&);
		friend vector operator*(double,const vector&);
		vector& operator/(double);
		vector& operator*(double);
};


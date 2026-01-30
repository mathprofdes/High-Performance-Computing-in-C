#ifndef VEC3_H_
#define VEC3_H_

#include <string>
#include <iostream>
#include <cmath>

using namespace std;

class Vec3 {
private:
	double x, y, z;

public:
	Vec3(double a = 0, double b = 0, double c = 0);
	virtual ~Vec3();

	void setX(double a);
	void setY(double a);
	void setZ(double a);
	void setVec(double a, double b, double c);

	double getX();
	double getY();
	double getZ();

	double norm();
	Vec3 unit();

	Vec3 operator +(const Vec3&);
	Vec3 operator -(const Vec3&);
	void operator +=(const Vec3&);
	void operator -=(const Vec3&);

	Vec3 operator*(double);
	Vec3 operator/(double);

	friend Vec3 operator *(double, const Vec3&);

	string toString();
	friend ostream& operator <<(ostream&, const Vec3&);
};

#endif /* VEC3_H_ */

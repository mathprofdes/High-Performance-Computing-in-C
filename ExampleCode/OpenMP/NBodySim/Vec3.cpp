#include "Vec3.h"

Vec3::Vec3(double a, double b, double c) {
	x = a;
	y = b;
	z = c;
}

Vec3::~Vec3() {
}

void Vec3::setX(double a) {
	x = a;
}

void Vec3::setY(double a) {
	y = a;
}

void Vec3::setZ(double a) {
	z = a;
}

void Vec3::setVec(double a, double b, double c) {
	x = a;
	y = b;
	z = c;
}

double Vec3::getX() {
	return x;
}

double Vec3::getY() {
	return y;
}

double Vec3::getZ() {
	return z;
}

double Vec3::norm() {
	return sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::unit() {
	Vec3 retvec(x, y, z);
	return retvec / retvec.norm();
}

Vec3 Vec3::operator +(const Vec3 &v) {
	Vec3 result(x + v.x, y + v.y, z + v.z);
	return result;
}

Vec3 Vec3::operator -(const Vec3 &v) {
	Vec3 result(x - v.x, y - v.y, z - v.z);
	return result;
}

void Vec3::operator +=(const Vec3 &rhs) {
	*this = *this + rhs;
}

void Vec3::operator -=(const Vec3 &rhs) {
	*this = *this - rhs;
}

Vec3 Vec3::operator*(double a) {
	Vec3 retvec(a * x, a * y, a * z);
	return retvec;
}

Vec3 Vec3::operator/(double a) {
	Vec3 retvec(x / a, y / a, z / a);
	return retvec;
}

Vec3 operator *(double a, const Vec3 &v) {
	Vec3 retvec(a * v.x, a * v.y, a * v.z);
	return retvec;
}

string Vec3::toString() {
	string retstr = "(" + to_string(x) + ", " + to_string(y) + ", "
			+ to_string(z) + ")";
	return retstr;
}

ostream& operator <<(ostream &strm, const Vec3 &v) {
	strm << "(" << v.x << ", " << v.y << ", " << v.z << ")";
	return strm;
}

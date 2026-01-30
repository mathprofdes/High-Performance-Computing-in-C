#include "particle.h"

particle::particle() {
	mass = 0;
}

particle::particle(Vec3 pos, Vec3 vel, double m) {
	position = pos;
	velocity = vel;
	mass = m;
}

particle::~particle() {
}

double particle::Mass() {
	return mass;
}

Vec3 particle::Position() {
	return position;
}

Vec3 particle::Velocity() {
	return velocity;
}

void particle::setMass(double m) {
	mass = m;
}

void particle::setPosition(Vec3 p) {
	position = p;
}

void particle::setVelocity(Vec3 v) {
	velocity = v;
}

string particle::toString() {
	string retstr = to_string(mass) + " / " + position.toString() + " / "
			+ velocity.toString();
	return retstr;
}

ostream& operator <<(ostream &strm, const particle &p) {
	strm << p.mass << " / " << p.position << " / " << p.velocity;
	return strm;
}

#ifndef PARTICLE_H_
#define PARTICLE_H_

#include "Vec3.h"

class particle {
private:
	Vec3 position;
	Vec3 velocity;
	double mass;

public:
	particle();
	particle(Vec3 pos, Vec3 vel, double m);
	virtual ~particle();

	double Mass();
	Vec3 Position();
	Vec3 Velocity();

	void setMass(double);
	void setPosition(Vec3);
	void setVelocity(Vec3);

	string toString();
	friend ostream& operator <<(ostream&, const particle&);
};

#endif /* PARTICLE_H_ */

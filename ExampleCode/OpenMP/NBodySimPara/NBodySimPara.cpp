#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <omp.h>

#include "particle.h"
#include "Vec3.h"
#include "tinyfiledialogs.h"

using namespace std;

Vec3 CalculateForce(particle &p1, particle &p2);
double frand();
double frand(double, double);
Vec3 randUnitVec();
bool endswith(string const&, string const&);

int compareSimulations(particle*, particle*, int, double);

// (gravitational constant)
// G = 6.673 × 10^−11 m/(kg * s^2)
const double G = 1.0;

int main() {
	char saveYN;
	int n, timesteps;
	double mlb, mub, poslb, posub, vellb, velub, deltaT;
	srand(time(0));

	cout << "Input the number of particles: ";
	cin >> n;

	cout << "Input the lower and upper bounds for the mass (lb ub): ";
	cin >> mlb >> mub;

	cout
			<< "Input the lower and upper bounds for the initial position (lb ub): ";
	cin >> poslb >> posub;

	cout
			<< "Input the lower and upper bounds for the initial velocity (lb ub): ";
	cin >> vellb >> velub;

	cout << "Input the time step (deltaT): ";
	cin >> deltaT;

	cout << "Input the number of time steps in the simulation: ";
	cin >> timesteps;

	particle *particles = new particle[n];
	particle *initialparticles = new particle[n];
	Vec3 *totalforces = new Vec3[n];
	particle *simdata = new particle[n * timesteps];
	particle *parasimdata = new particle[n * timesteps];

	// Initialize

	for (int i = 0; i < n; i++) {
		particles[i].setMass(frand(mlb, mub));
		particles[i].setPosition(frand(poslb, posub) * randUnitVec());
		particles[i].setVelocity(frand(vellb, velub) * randUnitVec());
	}

	for (int i = 0; i < n; i++) {
		initialparticles[i] = particles[i];
	}

	// Serial calculation.
	double start = omp_get_wtime();
	for (int step = 0; step < timesteps; step++) {
		// Calculate Forces

		for (int i = 0; i < n; i++) {
			totalforces[i] = 0;
			for (int j = 0; j < n; j++)
				if (i != j)
					totalforces[i] += CalculateForce(particles[i],
							particles[j]);
		}

		// Update Positions

		for (int i = 0; i < n; i++) {
			Vec3 oldpos = particles[i].Position();
			Vec3 oldvel = particles[i].Velocity();
			Vec3 acc = totalforces[i] / particles[i].Mass();
			Vec3 newpos = 0.5 * acc * deltaT * deltaT + oldvel * deltaT
					+ oldpos;
			Vec3 newvel = acc * deltaT + oldvel;
			particles[i].setPosition(newpos);
			particles[i].setVelocity(newvel);
		}

		// Store Results
		for (int i = 0; i < n; i++)
			simdata[step * n + i] = particles[i];
	}
	double stop = omp_get_wtime();
	printf("\nSequential Simulation Runtime (sec.) %.16f\n\n", stop - start);

	for (int i = 0; i < n; i++) {
		particles[i] = initialparticles[i];
	}

// Define a new reduction based on the overloaded operator + of the Vec3 class.
#pragma omp declare reduction (+:Vec3:omp_out=omp_out+omp_in) \
	initializer(omp_priv = {0.,0.,0.})

	// Parallel calculation.
	start = omp_get_wtime();
	for (int step = 0; step < timesteps; step++) {
		// Calculate Forces
		for (int i = 0; i < n; i++) {
			Vec3 sum;
#pragma omp parallel for reduction(+:sum)
			for (int j = 0; j < n; j++) {
				if (i == j)
					continue;
				sum += CalculateForce(particles[i], particles[j]);
			}
			totalforces[i] = sum;
		}

		// Update Positions and store results.
#pragma omp parallel for
		for (int i = 0; i < n; i++) {
			Vec3 oldpos = particles[i].Position();
			Vec3 oldvel = particles[i].Velocity();
			Vec3 acc = totalforces[i] / particles[i].Mass();
			Vec3 newpos = 0.5 * acc * deltaT * deltaT + oldvel * deltaT
					+ oldpos;
			Vec3 newvel = acc * deltaT + oldvel;
			particles[i].setPosition(newpos);
			particles[i].setVelocity(newvel);
			parasimdata[step * n + i] = particles[i];
		}
	}
	stop = omp_get_wtime();
	printf("Parallel Simulation Runtime (sec.) %.16f\n\n", stop - start);

	// One thing to note is that with this particular application, the different
	// sum order in the parallel version will introduce small roundoff errors that
	// will accumulate with increased numbers of time steps in the simulation.
	// This comparison will track the relative differences in the simulations.
	// A final parameter of 0.05 means a 5% difference in the corresponding values.
	int numoff = compareSimulations(simdata, parasimdata, n * timesteps, 0.05);
	if (numoff == 0)
		printf("All particles equal between simulations.\n");
	else
		printf("A total of %d differences between the simulations.\n", numoff);

// Note that this only saves the position data for each particle.
// An update would be needed if you want to store the mass and velocity as well.
	cout << "\n\nDo you want to save the simulation data to a file (Y/N): ";
	cin >> saveYN;
	cin.ignore();

	saveYN = toupper(saveYN);
	if (saveYN == 'Y') {
		cout << "Saving file" << endl;
		char const *lFilterPatterns[1] = { "*.dat" };

		char *filename = tinyfd_saveFileDialog("Save Simulation Data", NULL, 1,
				lFilterPatterns, "Simulation Data File");

		if (filename) {
			string filenamestr = filename;
			if (!endswith(filenamestr, ".dat")) {
				filenamestr += ".dat";
			}

			fstream datastream(filenamestr, ios::out | ios::binary);
			Vec3 siminfo(n, timesteps, 0);
			datastream.write(reinterpret_cast<char*>(&siminfo),
					sizeof(siminfo));

			for (int i = 0; i < n * timesteps; i++) {
				Vec3 pt = simdata[i].Position();
				datastream.write(reinterpret_cast<char*>(&pt), sizeof(pt));
			}

			datastream.close();
			cout << "File saved to " << filenamestr << endl;
		} else {
			cout << "Canceled: No file was saved." << endl;
		}
	}

	delete[] particles;
	delete[] totalforces;
	delete[] simdata;
	delete[] initialparticles;
	delete[] parasimdata;

	return 0;
}

Vec3 CalculateForce(particle &p1, particle &p2) {
	Vec3 diff = p1.Position() - p2.Position();
	double d3 = pow(diff.norm(), 3);
	Vec3 force = (-G * (p1.Mass() * p2.Mass()) / d3) * diff;
	return force;
}

double frand() {
	return 1.0 * rand() / RAND_MAX;
}

double frand(double lb, double ub) {
	return frand() * (ub - lb) + lb;
}

Vec3 randUnitVec() {
	Vec3 retvec(frand(-1, 1), frand(-1, 1), frand(-1, 1));
	return retvec.unit();
}

bool endswith(string const &str, string const &end) {
	if (str.length() >= end.length()) {
		return (0 == str.compare(str.length() - end.length(), end.length(), end));
	} else {
		return false;
	}
}

double perOff(double a, double b) {
	double max = fabs(a);
	if (fabs(b) > max)
		max = fabs(b);
	return fabs(a - b) / max;
}

int compareSimulations(particle *A, particle *B, int n, double pertol) {
	int count = 0;
	for (int i = 0; i < n; i++) {
		particle p1 = A[i];
		particle p2 = B[i];
		if (perOff(p1.Position().getX(), p2.Position().getX()) > pertol)
			count++;
		if (perOff(p1.Position().getY(), p2.Position().getY()) > pertol)
			count++;
		if (perOff(p1.Position().getZ(), p2.Position().getZ()) > pertol)
			count++;

		if (perOff(p1.Velocity().getX(), p2.Velocity().getX()) > pertol)
			count++;
		if (perOff(p1.Velocity().getY(), p2.Velocity().getY()) > pertol)
			count++;
		if (perOff(p1.Velocity().getZ(), p2.Velocity().getZ()) > pertol)
			count++;
	}

	return count;
}


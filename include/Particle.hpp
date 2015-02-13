#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <vector>
#include <opencv2/opencv.hpp>
#include "World.hpp"

class Particle
{
protected:
	double x;
	double y;
	double h;
	double w;

public:
	Particle(double x_, double y_, double h_, double w_ = 1, bool noisy = false);
	virtual ~Particle();

	double getX() const { return x; }
	double getY() const { return y; }
	double getH() const { return h; }
	double getW() const { return w; }

    void setW(double weight) { w = weight; }
    void setH(double heading) { h = heading; }

    virtual double read_sensor(const World& world);
    virtual bool move(const World& world, double speed, bool check = false, bool noisy = false);

	// create set of random particles
    static void CreateRandom(std::vector<Particle>& particles, const int count, const World& world);
    // update particle weights based on observation
    static void update_particle_weights(std::vector<Particle>& particles, double observation, const World& world);
    // resample using low variance sampler (Probabilistic Robotics, p.110)
    static void low_variance_sampler(std::vector<Particle>& particles);


    friend std::ostream& operator<<(std::ostream& os, const Particle& particle);
};
#endif
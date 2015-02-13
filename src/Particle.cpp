#include "Particle.hpp"	
#include "Utils.hpp"
#include "boost/lambda/lambda.hpp"
#include "boost/lambda/bind.hpp"
#include <cmath>

using namespace boost::lambda;

Particle::Particle(double x_, double y_, double h_, double w_, bool noisy)
{
	x = x_;
	y = y_;
	h = h_;
	w = w_;

	if(noisy)
	{
		x = Utils::add_noise(0.1, x);
		y = Utils::add_noise(0.1, y);
		h = Utils::add_noise(0.1, h);
	}
}

Particle::~Particle()
{

}


void Particle::CreateRandom(std::vector<Particle>& particles, const int count, const World& world)
{
	particles.clear();
	for(int i =0; i < count; ++i)
	{
		double x = Utils::sample_uniform(0, world.GetWidth());
		double y = Utils::sample_uniform(0, world.GetHeight());
		double h = Utils::sample_uniform(0, 2*M_PI);
		particles.push_back(Particle(x, y, h));
	}
}

// get distance to the closest beacon (no noise)
double Particle::read_sensor(const World& world)
{
    return world.get_distance_to_nearest_beacon(x, y);
}

bool Particle::move(const World& world, double speed, bool check, bool noisy)
{
    if (noisy)
    {
        speed = Utils::add_noise(0.02, speed);
        h = Utils::add_noise(0.1, h);
    }

    double delta_x = cos(h) * speed;
    double delta_y = sin(h) * speed;

    if (check)
    {
        // this is the robot
        if ( world.is_free( this->x + delta_x, this->y + delta_y) )
        {
            this->x += delta_x;
            this->y += delta_y;

            return true;
        } else
        {
            return false;
        }
    } else
    {
        this->x += delta_x;
        this->y += delta_y;

        return true;
    }
}

// updates particle weights - no normalisation because we're using Thrun's low variance sampler
void Particle::update_particle_weights(std::vector<Particle>& particles, double observation, const World& world)
{
    double Z = observation;

    // double eta = 0; // normaliser
    for (size_t i = 0; i < particles.size(); ++i) {
        if (world.is_free(particles[i].getX(), particles[i].getY())) {
            double particle_dist = particles[i].read_sensor(world);

            double new_w = Utils::w_Gaussian(Z, particle_dist);
            particles[i].setW(new_w);
            // eta += new_w;
        }
        else {
            particles[i].setW(0);
        }
    }

    // normalise weights
    //if (eta)
    //    for (size_t i = 0; i < particles.size(); ++i)
    //        particles[i].setW(particles[i].getW() / eta);
}

// resample using low variance sampler (Probabilistic Robotics, p.110)
void Particle::low_variance_sampler(std::vector<Particle> &particles)
{
    std::vector<Particle> new_particles;

    int index = int( Utils::sample_uniform(0,1) * particles.size() );

    double beta = 0;

    std::vector<Particle>::const_iterator iter = std::max_element(particles.begin(), particles.end(), bind(&Particle::w, _2) > bind(&Particle::w, _1 ));
    double max_w = iter->w;

    for (size_t i = 0; i < particles.size(); ++i)
    {
        beta += Utils::sample_uniform(0, 1) * 2 * max_w;
        while (beta > particles[index].w)
        {
            beta -= particles[index].w;
            index = (index + 1) % particles.size();
        }
        new_particles.push_back(particles[index]);
    }

    particles = new_particles;
}


std::ostream &operator<<(std::ostream &os, const Particle &particle) {
    os << '(' << particle.x << ' ' << particle.y << ' ' << particle.h << ' ' << particle.w << ')';
    return os;
}

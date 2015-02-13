#include "Robot.hpp"

Robot::~Robot()
{

}

void Robot::choose_random_direction()
{
    this->h = Utils::sample_uniform(0, 2*M_PI);
}

// get noisy measurement of closest beacon for Chappie
double Robot::read_sensor()
{
    return Utils::add_noise(1, Particle::read_sensor(theWorld));
}

bool Robot::move()
{
    while(true)
    {
        if ( Particle::move(theWorld, speed, true, true) )
            break;

        // bumped into something
        choose_random_direction();
    }
    return true;
}
#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <vector>
#include <opencv2/opencv.hpp>
#include "Utils.hpp"
#include "Particle.hpp"
#include "World.hpp"

class Robot : public Particle
{
private:
    const World& theWorld;
    double speed = 1;

public:
    // initialise at given location
    Robot(const World& world, double x_, double y_, double h_, double w_ = 1, bool noisy = false) : Particle(x_, y_, h_, w_, noisy), theWorld(world)
    {
        // check that location is free, otherwise set to a new free & random location
        // if ()
    }

    // initialise at a free location in given world
    Robot(const World& world) : Particle(0,0,0,1,false), theWorld(world)
    {
        cv::Point free_location = world.get_random_free_place();
        this->x = free_location.x;
        this->y = free_location.y;
        choose_random_direction();
    }

    double getSpeed() { return speed; }
    // change heading to a new random direction
    void choose_random_direction();
    // get a noisy measurement of the distance to the closest beacon
    double read_sensor();
    bool move();

    ~Robot();
};
#endif
#ifndef PARTICLEFILTERGUI_HPP
#define PARTICLEFILTERGUI_HPP

#include <vector>
#include <opencv2/opencv.hpp>
#include "World.hpp"
#include "Particle.hpp"
#include "Robot.hpp"

class ParticleFilterGUI
{

private:
    cv::Mat maze_img;

    const World& theWorld;
    const std::vector<Particle>& theParticles;
    const Robot& theRobot;

    void drawWorld();
    void drawMaze();
    void drawBeacons();
    void drawParticles();
    void drawRobot();

public:
    ParticleFilterGUI(const World& world, const std::vector<Particle>& particles, const Robot& robot);
    ~ParticleFilterGUI();

    void render();
    // this returns exactly the same image; (guess) it's OK to send copy, but copying is redundant
    const cv::Mat& getImage() const { return maze_img; }

};
#endif
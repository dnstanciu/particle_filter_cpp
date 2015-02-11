#ifndef PARTICLEFILTERGUI_HPP
#define PARTICLEFILTERGUI_HPP

#include <vector>
#include <opencv2/opencv.hpp>
#include "World.hpp"
#include "Particle.hpp"

class ParticleFilterGUI
{

private:
    cv::Mat maze_img;

    const World& theWorld;
    const std::vector<Particle>& theParticles;

    void drawWorld();
    void drawMaze();
    void drawBeacons();
    void drawParticles();

public:
    ParticleFilterGUI(const World& world, const std::vector<Particle>& particles);
    ~ParticleFilterGUI();

    void render();
    // this returns exactly the same image; guess it's OK to send a copy...
    const cv::Mat& getImage() const { return maze_img; }

};
#endif
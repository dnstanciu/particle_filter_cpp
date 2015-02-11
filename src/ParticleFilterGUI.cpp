//#include <World.hpp>
#include "ParticleFilterGUI.hpp"

using namespace cv;

ParticleFilterGUI::ParticleFilterGUI(const World& world, const std::vector<Particle>& particles) : theWorld(world), theParticles(particles)
{
    this->maze_img.create(world.GetHeight(), world.GetWidth(), CV_8UC3);
}

ParticleFilterGUI::~ParticleFilterGUI()
{
}

void ParticleFilterGUI::render()
{
    drawWorld();
    drawParticles();
}


void ParticleFilterGUI::drawWorld()
{
    maze_img.setTo(cv::Scalar(255,255,255));
    drawMaze();
    drawBeacons();
}

void ParticleFilterGUI::drawMaze()
{
    Size maze_block_size = theWorld.getMazeBlockSize();

    for(size_t i = 0; i < theWorld.getMaze().size(); ++i)
    {
        for(size_t j = 0; j < theWorld.getMaze().size(); ++j)
        {
            if(theWorld.getMaze()[i][j])
            {
                Point pt1 = Point(j * maze_block_size.width, i * maze_block_size.height);
                Point pt2 = Point(pt1.x +  maze_block_size.width, pt1.y + maze_block_size.height);
                rectangle(maze_img, pt1, pt2, Scalar(0, 0, 0), FILLED);
            }
        }
    }
}

void ParticleFilterGUI::drawBeacons()
{
    for(size_t i = 0; i < theWorld.getBeacons().size(); ++i)
        circle(maze_img, theWorld.getBeacons()[i], 3, Scalar(0, 0, 255), FILLED);
}

void ParticleFilterGUI::drawParticles()
{
    for(size_t i = 0; i < theParticles.size(); ++i)
    {
        cv::Point pt1 = cv::Point(theParticles[i].GetX(), theParticles[i].GetY());
        cv::circle(maze_img, pt1, 3, Scalar(255, 0, 255), FILLED);

        const int r = 8;
        cv::Point pt2 = pt1 + cv::Point(cos(theParticles[i].GetH()) * r, sin(theParticles[i].GetH()) * r);
        cv::line(maze_img, pt1, pt2, Scalar(255, 0, 255), 1);
    }
}
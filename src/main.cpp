#include <iostream>

#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/video.hpp"

#include "Utils.hpp"
#include "World.hpp"
#include "Particle.hpp"
#include "Robot.hpp"
#include "ParticleFilterGUI.hpp"


using std::cout;
using std::endl;


const int WORLD_HEIGHT = 500;
const int WORLD_WIDTH = 500;
std::vector< std::vector<int> > maze_data = 
	{std::vector<int>{ 1, 1, 0, 0, 2, 0, 0, 0, 0, 1 },
 	 std::vector<int>{ 1, 2, 0, 0, 1, 1, 0, 0, 0, 0 },
 	 std::vector<int>{ 0, 1, 1, 0, 0, 0, 0, 1, 0, 1 },
 	 std::vector<int>{ 0, 0, 0, 0, 1, 0, 0, 1, 1, 2 },
 	 std::vector<int>{ 1, 1, 0, 1, 1, 2, 0, 0, 1, 0 },
 	 std::vector<int>{ 1, 1, 1, 0, 1, 1, 1, 0, 2, 0 },
 	 std::vector<int>{ 2, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
 	 std::vector<int>{ 1, 2, 0, 1, 1, 1, 1, 0, 0, 0 },
 	 std::vector<int>{ 0, 0, 0, 0, 1, 0, 0, 0, 1, 0 },
 	 std::vector<int>{ 0, 0, 1, 0, 0, 2, 1, 1, 1, 0 }};

const int PARTICLES_COUNT = 10000;


int main(int argc, char const *argv[])
{
    // model (world, particles, robot)
	World world(maze_data, WORLD_WIDTH, WORLD_HEIGHT);
	std::vector<Particle> particles;

	Particle::CreateRandom(particles, PARTICLES_COUNT, world);

    Robot chappie(world);

    // view
    ParticleFilterGUI view(world, particles, chappie);

    Utils::init();

    cv::namedWindow( "Particle Filter Demo", cv::WINDOW_NORMAL);

	char key;
	do
	{
        // update model state

        // measurement (read Chappie's sensor)
        double Z = chappie.read_sensor();

        // update particle weights
        Particle::update_particle_weights(particles, Z, world);

        // update view
        view.render();

        // Particle::CreateRandom(particles, PARTICLES_COUNT, world);
        // resampling
        Particle::low_variance_sampler(particles);

        // move robot
        double old_h = chappie.getH();
        chappie.move();
        double delta_h = chappie.getH() - old_h;


        // move particles
        for (size_t i = 0; i < particles.size(); ++i)
        {
            // particles[i].setH( particles[i].getH() + delta_h );

            // robot has compass for orientation (i.e. we have heading)
             particles[i].setH(chappie.getH());

            particles[i].move(world, chappie.getSpeed(), false, true);
        }

        cv::imshow("Particle Filter Demo", view.getImage());

        // Press Q or ESC to exit the program
        key = cv::waitKey(10);
	}
	while(key != 'q' && key != 27);

	return 0;
}
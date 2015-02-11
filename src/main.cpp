#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/video.hpp"

#include "Utils.hpp"
#include "World.hpp"
#include "Particle.hpp"
#include "ParticleFilterGUI.hpp"


using namespace cv;
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

const int PARTICLES_COUNT = 1000;


int main(int argc, char const *argv[])
{


    // model
	World world(maze_data, WORLD_WIDTH, WORLD_HEIGHT);

	std::vector<Particle> particles;

	Particle::CreateRandom(particles, PARTICLES_COUNT, world);

    // view
    ParticleFilterGUI view(world, particles);
    //Mat maze_img(WORLD_HEIGHT, WORLD_WIDTH, CV_8UC3);

    Utils::init();

    // cout << "BEGIN LOOP " << endl;

	char key;
	do
	{
        // update state
        Particle::CreateRandom(particles, PARTICLES_COUNT, world);

        // render
        view.render();
        //world.DrawWorld(maze_img);
        // Particle::DrawParticles(maze_img, particles);



		imshow("Particle Filter", view.getImage());

        // Press Q or ESC to exit the program
        key = waitKey(2000);
	}
	while(key != 'q' && key != 27);

	return 0;
}
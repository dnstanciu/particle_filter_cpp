#include "World.hpp"	

#include <iostream>
#include "Utils.hpp"
#include <cmath>

using namespace cv;

World::World(const std::vector<std::vector<int>>& m, int w, int h)
{
	width = w;
	height = h;
	maze_block_size = Size(width / m[0].size(), height / m.size());
	
	maze.resize(m.size());
	for(size_t i = 0; i < maze.size(); ++i)
	{

		maze[i].resize(m[0].size());	
		for(size_t j = 0; j < maze[i].size(); ++j)
		{
			maze[i][j] = m[i][j];

            // as this is a "beacon" square, add 4 beacons at the corners
			if(maze[i][j] == 2)
			{
				Point pt = Point(j * maze_block_size.width, i * maze_block_size.height);
				beacons.push_back(pt);
				beacons.push_back(pt + Point(maze_block_size.width, 0));
				beacons.push_back(pt + Point(0, maze_block_size.height));
				beacons.push_back(pt + Point(maze_block_size.width, maze_block_size.height));
			}
		}

	}
	
}

World::~World()
{
}

cv::Point World::get_random_free_place() const
{
    while(true)
    {
        double x = Utils::sample_uniform(0, width);
        double y = Utils::sample_uniform(0, height);
        if (is_free(x, y))
            return Point(x,y);
    }

}

// Checks if position is free
bool World::is_free(double x, double y) const
{
    // check if values are outside of world
    if ((x < 0) || (y < 0) || (x > width) || (y > height))
        return false;

    // maps (x, y) world position to (yy, xx) maze square
    int xx = int(x/maze_block_size.width);
    int yy = int(y/maze_block_size.height);

    return maze[yy][xx] == 0;
}

double World::get_distance_to_nearest_beacon (double x, double y) const
{
    double d1 = 99999;
    //double d2 = 99999;

    for(size_t i = 0; i < beacons.size(); ++i)
    {
        double x_beacon = beacons[i].x;
        double y_beacon = beacons[i].y;
        double distance = sqrt( pow(x_beacon - x, 2) + pow(y_beacon - y, 2) );

        if (distance < d1)
        {
            //d2 = d1;
            d1 = distance;
        }

    }

    return d1;//+d2;
}
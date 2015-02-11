#ifndef WORLD_HPP
#define WORLD_HPP 

#include <vector>
#include <opencv2/opencv.hpp>

class World
{
private:
	int width;
	int height;
	//std::vector<cv::Point> blocks;
	std::vector<cv::Point> beacons;
	std::vector< std::vector<int> > maze;
	cv::Size maze_block_size;

	//void drawMaze(cv::Mat& img);
	//void drawBeacons(cv::Mat& img);

public:
	World(const std::vector<std::vector<int>>& m, int w, int h);
	~World();

	//void DrawWorld(cv::Mat& img);

	double GetWidth() const {return width;}
	double GetHeight() const {return height;}

    const std::vector< std::vector<int> >& getMaze() const { return maze; }

    const cv::Size getMazeBlockSize() const { return maze_block_size; }
	const std::vector<cv::Point>& getBeacons() const { return beacons; }

};
#endif


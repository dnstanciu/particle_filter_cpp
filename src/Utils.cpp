#include "Utils.hpp"

#include <chrono>

std::default_random_engine Utils::generator;

void Utils::init()
{
	generator = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());
}

double Utils::add_noise(double level, double x)
{
	std::uniform_real_distribution<double> distribution(-level,level);
	double noise = distribution(generator);
	return x + noise;
}

double Utils::sample_uniform(double from, double to)
{
	std::uniform_real_distribution<double> distribution(from,to);
	return distribution(generator);
}

double Utils::w_Gaussian(double observation, double prediction)
{
    double sigma_sq = 100;
    double error = observation - prediction;
    double g = exp( - pow(error, 2) / (2*sigma_sq) );
    return g;
}
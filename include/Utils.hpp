#ifndef UTILS_HPP
#define UTILS_HPP
#include <random>
#include <cmath>

class Utils
{	
public:
	static void init();
	static double add_noise(double level, double x);
	static double sample_uniform(double from, double to);
    static double w_Gaussian(double observation, double prediction);

private:
	Utils();
	~Utils();

	static std::default_random_engine generator;
};
#endif
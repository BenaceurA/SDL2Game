#pragma once
#include <vector>
#include "PerlinNoise.hpp"

class Map
{
public:
	Map(unsigned int width,unsigned int height);
	void generateHeightMap();
	static double getHeightAtLocation(unsigned int x,unsigned int y);
	static const siv::PerlinNoise::seed_type seed = 123456u;
	static const siv::PerlinNoise perlin;
private:
	//IDEA : I should generate every cell on the spot, not generating all the map and storing it
	/*std::vector<double> heightMap; */
};

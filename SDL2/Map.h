#pragma once
#include <vector>

class Map
{
public:
	Map(unsigned int width,unsigned int height);
	void generateHeightMap();
	double getHeightAtLocation(unsigned int x,unsigned int y);
	unsigned int width;
	unsigned int height;
private:
	std::vector<double> heightMap; //each value corresponds to a cell
	
};

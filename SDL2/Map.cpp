#include "Map.h"
#include "PerlinNoise.hpp"

Map::Map(unsigned int width,unsigned int height)
	:
	width(width),
	height(height)
{
	heightMap.resize(height * width);
}

void Map::generateHeightMap() {
	const siv::PerlinNoise::seed_type seed = 123456u;

	const siv::PerlinNoise perlin{ seed };

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			const double noise = perlin.octave2D_01((x * 0.02), (y * 0.02), 4);
			heightMap[(width * y) + x] = noise;
		}

	}
}

double Map::getHeightAtLocation(unsigned int x,unsigned int y)
{
	return heightMap[(width * y) + x];
}

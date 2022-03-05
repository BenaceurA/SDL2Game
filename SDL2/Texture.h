#pragma once

class Texture
{
public:
	Texture(const char* path);
	~Texture();
	void bind(unsigned int slot);
private:
	unsigned int id;
};

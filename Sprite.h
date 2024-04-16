#pragma once
#include <luna.hpp>

class Sprite
{
public:
	Sprite(const char* filepath, int frames = 1);
	void Draw(glm::vec3 position, glm::vec3 scale, float rotation, luna::Renderer* renderer);
	void Draw(glm::vec3 position, glm::vec3 scale, luna::Renderer* renderer);
	void Draw(glm::vec3 position, float rotation, luna::Renderer* renderer);
	void Draw(glm::vec3 position, luna::Renderer* renderer);
private:
	luna::Material material;
	int frames;

	
};


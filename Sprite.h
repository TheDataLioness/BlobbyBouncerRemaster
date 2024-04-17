#pragma once
#include <luna.hpp>


struct FrameCountData
{
	int numRows;
	int numCols;
};

class Sprite
{
public:
	Sprite(const char* filepath, FrameCountData frameCountData = {1, 1});

	void SetFrame(int row, int column);

	void Draw(glm::vec3 position, glm::vec3 scale, float rotation, luna::Renderer* renderer);
	void Draw(glm::vec3 position, glm::vec3 scale, luna::Renderer* renderer);
	void Draw(glm::vec3 position, float rotation, luna::Renderer* renderer);
	void Draw(glm::vec3 position, luna::Renderer* renderer);

	glm::vec3 GetScale() const { return glm::vec3(texture.getWidth() / pixelsPerUnit, texture.getHeight() / pixelsPerUnit, 1.0f); }

private:
	luna::Material material;
	luna::Texture texture;
	float pixelsPerUnit = 16.0f;

	FrameCountData frameCountData;
	
};


#include "Sprite.h"
#include <luna.hpp>

Sprite::Sprite(const char* filepath, FrameCountData frameCountData):
	material(*luna::getDefaultUnlitMaterial()),
	texture(luna::Texture::loadFromFile(filepath)),
	frameCountData(frameCountData)
{
	material.setMainTexture(&texture);
}

void Sprite::SetFrame(int row, int column)
{
	float frameWidth = 1.0f / frameCountData.numCols;
	float frameHeight = 1.0f / frameCountData.numRows;

	float x = column * frameWidth;
	float y = row * frameHeight;

	material.setMainTextureScaleTranslation(glm::vec4(frameWidth, frameHeight, x, y));
}

void Sprite::Draw(glm::vec3 position, glm::vec3 scale, float rotation, luna::ForwardRenderer* renderer)
{

	glm::vec3 drawScale{ 
		texture.getWidth()/pixelsPerUnit*frameCountData.numCols, 
		texture.getHeight()/pixelsPerUnit*frameCountData.numRows, 1.0f };
	drawScale *= scale;

	renderer->push(
		luna::getPrimitive(luna::Primitive::Quad),
		luna::Transform(position, glm::vec3(0.0f, 0.0f, rotation), drawScale).matrix(),
		&material
	);
}
void Sprite::Draw(glm::vec3 position, glm::vec3 scale, luna::ForwardRenderer* renderer)
{
	Draw(position, scale, 0.0f, renderer);
}
void Sprite::Draw(glm::vec3 position, float rotation, luna::ForwardRenderer* renderer)
{
	Draw(position, glm::vec3(1.0f), rotation, renderer);
}
void Sprite::Draw(glm::vec3 position, luna::ForwardRenderer* renderer)
{
	Draw(position, glm::vec3(1.0f), 0.0f, renderer);
}
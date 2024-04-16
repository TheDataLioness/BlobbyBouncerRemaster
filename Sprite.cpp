#include "Sprite.h"
#include <luna.hpp>

Sprite::Sprite(const char* filepath, int frames)
{
	material = luna::Material(luna::getDefaultShader());
	luna::Texture texture = luna::Texture::loadFromFile(filepath);
	material.setMainTexture(&texture);
	
}

void Sprite::Draw(glm::vec3 position, glm::vec3 scale, float rotation, luna::Renderer* renderer)
{
	renderer->push(
		luna::getPrimitive(luna::Primitive::Quad),
		luna::Transform(position, glm::vec3(0.0f, 0.0f, rotation), scale).matrix(),
		&material
	);
}
void Sprite::Draw(glm::vec3 position, glm::vec3 scale, luna::Renderer* renderer)
{
	Draw(position, scale, 0.0f, renderer);
}
void Sprite::Draw(glm::vec3 position, float rotation, luna::Renderer* renderer)
{
	Draw(position, glm::vec3(1.0f), rotation, renderer);
}
void Sprite::Draw(glm::vec3 position, luna::Renderer* renderer)
{
	Draw(position, glm::vec3(1.0f), 0.0f, renderer);
}
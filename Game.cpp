#include "Game.h"
#include <luna.hpp>
#include "Sprite.h"

Game::Game(luna::Camera* camera_, luna::Renderer* renderer_) :
	camera(camera_),
	renderer(renderer_)
{}

void Game::Initialize()
{
	// Setup the camera
	camera->setProjectionType(luna::ProjectionType::Orthographic);
	camera->setOrthographicSize(10.0f);
	camera->setBackgroundColor(luna::Color::White);

	// Load the sprite
	sprite = new Sprite("assets/Blobby.png");
}

void Game::Tick(float deltaTime)
{
	// Draw the sprite
	sprite->Draw(glm::vec3(0.0f), renderer);
}

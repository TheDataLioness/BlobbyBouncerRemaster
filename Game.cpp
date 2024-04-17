#include "Game.h"
#include <luna.hpp>
#include "Sprite.h"
#include "AssetManager.h"
#include "Blobby.h"

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

	// Load assets
	AssetManager& assetManager = AssetManager::GetInstance();
	assetManager.GetSprite("assets/Blobby.png");
	assetManager.GetSprite("assets/BlobbyFace.png");

	blobby = new Blobby();
}

void Game::Tick(float deltaTime)
{
	blobby->Update(deltaTime);
	blobby->Draw(renderer);
}

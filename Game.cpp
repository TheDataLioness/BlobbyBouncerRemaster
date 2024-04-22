#include "Game.h"
#include <luna.hpp>
#include "Sprite.h"
#include "AssetManager.h"
#include "Blobby.h"

#include <thread>
#include <chrono>

Game::Game(luna::Camera* camera_, luna::ForwardRenderer* renderer_) :
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

	ImGui::Begin("Blobby Debug Window");

	ImGui::Text("Fps: %f", 1.0f / deltaTime);
	ImGui::DragInt("Max Fps", &maxFps, 1, 12, 1000);

	ImGui::BeginTabBar("##TabBar");


	blobby->Update(deltaTime);
	blobby->Draw(renderer);

	ImGui::EndTabBar();
	ImGui::End();

	

}

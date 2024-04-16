#pragma once

namespace luna
{
	class Camera;
	class Renderer;
}

class Sprite;

class Game
{
public:
	Game(luna::Camera* camera, luna::Renderer* renderer);
	void Initialize();
	void Tick(float deltaTime);
	void Shutdown();
private:
	luna::Camera* camera;
	luna::Renderer* renderer;
	Sprite* sprite;
};


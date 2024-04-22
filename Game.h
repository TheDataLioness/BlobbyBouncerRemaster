#pragma once

namespace luna
{
	class Camera;
	class ForwardRenderer;
}

class Sprite;
class Blobby;

class Game
{
public:
	Game(luna::Camera* camera, luna::ForwardRenderer* renderer);
	void Initialize();
	void Tick(float deltaTime);
	void Shutdown();
private:
	luna::Camera* camera;
	luna::ForwardRenderer* renderer;
	int maxFps = 60.0f;

	Blobby* blobby;
};


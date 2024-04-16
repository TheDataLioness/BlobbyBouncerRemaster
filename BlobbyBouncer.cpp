#include <iostream>
#include <luna.hpp>
#include "Game.h"

int main() {
	luna::setMessageCallback([](const char* message, const char* prefix, luna::MessageSeverity severity) {
		std::cout << '<' << prefix << "> " << message << std::endl;
	});

	luna::initialize();

	luna::Window window;
	luna::Renderer renderer;

	luna::Camera camera(&window);
	Game game(&camera, &renderer);
	game.Initialize();

	while (!luna::isCloseRequested() && !window.isCloseRequested()) {
		luna::update();
		camera.updateAspect();
		renderer.beginFrame();

		// Game tick
		game.Tick(luna::getDeltatime());

		renderer.endFrame();
		renderer.render(camera);
		window.update();
	}

	luna::terminate();
}
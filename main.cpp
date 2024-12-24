#include <SDL.h>
#include <vector>

//cube

//std::vector<Point3D> points { }

//std::vector<Vertex> vertices { }

int main(int argc, char* argv[]) {
	//creating window;

	SDL_Window* window;
	SDL_Renderer* renderer;
	window = SDL_CreateWindow("3D Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	bool running = true;

	//Renderer3D renderer3D1(window, renderer, points, vertices);

	while (running) {
		if (SDL_QuitRequested()) {
			running = false;
			break;
		}
		//renderer3D1.render();
	}

	return 0;
}
#include "Renderer3D.h"

Renderer3D::Renderer3D(SDL_Window* _window, SDL_Renderer* _renderer, std::vector<Point3D>& _points, std::vector<Vertex>& _vertices) {
	SDL_GetWindowSize(_window, &WindowSizeX, &WindowSizeY);
	renderer = _renderer;
	points = _points;
	vertices = _vertices;
}

void Renderer3D::render() {
	auto time1 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration(0); // measuring time for frame independent timing

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE); 
	SDL_RenderClear(renderer); // ^setting renderer to black and clearing the renderer;
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE); // setting the renderer color to white;

	rotation += 1 * DeltaTime;

	for (auto& vertex : vertices) { // going through every vertex
		Point3D rotatedStartPoint = (rotateX(rotateY(points[vertex.start]))); // taking its starting point and rotating it on x and y
		Point3D rotatedEndPoint = (rotateX(rotateY(points[vertex.end]))); // same as above, just the vertex end point
		Point2D start = projection(rotatedStartPoint); //converting from 3d into 2d
		Point2D end = projection(rotatedEndPoint);
		SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
	}
	SDL_RenderPresent(renderer); // updating the screen

	auto time2 = std::chrono::high_resolution_clock::now();
	duration = time2 - time1;
	DeltaTime = duration.count();
	time1 = time2;
}

Point3D Renderer3D::rotateX(Point3D point) {
	Point3D returnPoint;
	returnPoint.x = point.x;
	returnPoint.y = cos(rotation) * point.y - sin(rotation) * point.z; //formula resulting from matrix multiplication
	returnPoint.z = sin(rotation) * point.y + cos(rotation) * point.z;
	return returnPoint;
}

Point3D Renderer3D::rotateY(Point3D point) {
	Point3D returnPoint;
	returnPoint.x = cos(rotation) * point.x - sin(rotation) * point.z;
	returnPoint.y = point.y;
	returnPoint.z = sin(rotation) * point.x + cos(rotation) * point.z;
	return returnPoint;
}

Point2D Renderer3D::projection(Point3D point) {
	return Point2D{
		WindowSizeX / 2 + (FOV * point.x) / (FOV + point.z) * 100, // this is the simplified rotation formula for Px(Projection X)
		WindowSizeY / 2 + (FOV * point.y) / (FOV + point.z) * 100 // this is the simplified rotation formula for Py(Projection y)
	};
}
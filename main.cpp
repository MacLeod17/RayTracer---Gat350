
#include "Camera.h"
#include "Canvas.h"
#include "Image.h"
#include "Tracer.h"
#include "Math.h"
#include "Material.h"
#include "Plane.h"
#include "Scene.h"
#include "Sphere.h"
#include "SDL.h"
#include <iostream>
#include <vector>

int main(int, char**)
{
	const int width = 800;
	const int height = 600;
	const int samples = 10;
	const int depth = 20;
	const int numObjects = 20;
	const int numFrames = 30;
	glm::vec3 eye = glm::vec3{ 0, 2, 5 };
	glm::vec3 lookAt = glm::vec3{ 0, 0, -1 };
	const glm::vec3 translate = glm::vec3{ 0.2f, 0, 0 };
	std::vector<Image*> images;

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("2D Renderer", 100, 100, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	Canvas canvas{ renderer, width, height };
	//Image image{ width, height };
	//Camera camera{ glm::vec3{5, 5, 5}, glm::vec3{0, 0, 0}, glm::vec3{0, 1, 0}, 80.0f, &image };
	Tracer tracer{ samples, depth };
	Scene scene;

	for (int i = 0; i < numObjects; i++)
	{
		glm::vec3 color = glm::rgbColor(glm::vec3{ random(0, 360), 1, 1 });
		glm::vec3 position = glm::vec3{ random(-12, 15), random(-2, 12), random(0, -10) };
		float radius = random(0.1f, 1.5f);
		Material* material = nullptr;

		float fuzz = random(0.1f, 1.0f);
		float index = random(1.0f, 2.0f);

		switch (rand() % 3)
		{
			case 0:
				material = new Lambertian{ color };
				break;
			case 1:
				material = new Metal{ color, fuzz };
				break;
			case 2:
				material = new Dielectric{ color, index };
				break;
		}

		scene.Add(new Sphere{ position, radius, material });
	}

	//scene.Add(new Sphere{ { 2, 2, -4 },		1.0f,	new Lambertian{ glm::vec3{ 0, 1, 0 } } });
	//scene.Add(new Sphere{ { 0, 0, -6 },		2.0f,	new Metal{ glm::vec3{ 1, 0, 1 }, 0.1f } });
	//scene.Add(new Sphere{ { -2, -2, -3 },	1.0f,	new Lambertian{ glm::vec3{ 1, 1, 1 } } });
	//scene.Add(new Sphere{ { 0, 0, 0 },		1.0f,	new Dielectric{ glm::vec3{ 0.8f, 0.8f, 1 }, 1.33f } });
	scene.Add(new Plane{ { 0, -2, 0 }, { 0, 1, 0 }, new Metal{ glm::vec3{ 0.5f, 0.5f, 0.5f }, 1.0f } });

	for (int i = 0; i < numFrames; i++)
	{
		Image* image = new Image{ width, height };
		Camera camera{ eye, eye + lookAt, glm::vec3{0, 1, 0}, 80.0f, image };
		tracer.Trace(*image, scene, camera);
		images.push_back(image);
		eye += translate;
	}

	//image.Clear({ 0, 0, 0 });
	//tracer.Trace(image, scene, camera);

	int frame = 0;
	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				quit = true;
				break;
			}
			break;
		}

		canvas.Clear({ 0, 0, 0 });
		
		canvas.DrawImage(*images[frame]);
		frame++;
		if (frame >= images.size()) frame = 0;
		canvas.Update();

		SDL_RenderClear(renderer);
		canvas.Draw(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_Quit();

	return 0;
}


#include "Canvas.h"
#include "Image.h"
#include "Tracer.h"
#include "Sphere.h"
#include "SDL.h"
#include <iostream>
#include <vector>

int main(int, char**)
{
	const int width = 800;
	const int height = 600;

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

	Canvas canvas(renderer, width, height);
	Image image(width, height);
	Tracer tracer;
	std::vector<Geometry*> scene;
	scene.push_back(new Sphere{ { 2, 2, -3 }, 1.0f, { 1, 0, 0} });
	scene.push_back(new Sphere{ { 0, 0, -1 }, 1.0f, { 0, 1, 0} });
	scene.push_back(new Sphere{ { 4, -1, -2 }, 1.0f, { 0, 0, 1} });

	image.Clear({ 0, 0, 0 });

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
		tracer.Trace(image, scene);
		canvas.DrawImage(image);
		canvas.Update();

		SDL_RenderClear(renderer);
		canvas.Draw(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_Quit();

	return 0;
}

/**
 * @file BaseGame.cpp
 * @author lilitharcana (lilithalicecrawford@gmail.com)
 * @brief Implementation for BaseGame class from BaseGame.hpp.
 * @version 0.1
 * @date 2021-07-09
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "BaseGame.hpp"
#include <iostream>


/**
 * @brief Construct a BaseGame object, with a given title, window size, and autorun flag.
 * Initializes SDL and its subsystems, creates SDL window and renderer, and sets up LilyEngine systems.
 * If autorun is true, the game will automatically start and run inside the constructor.
 * If you need an exit code for the game, call run() seperately.
 * 
 * @param title The title of the window.
 * @param width width of the window.
 * @param height height of the window.
 * @param autorun Whether or not to automatically run the game.
 */
BaseGame::BaseGame(const char* title, int width, int height, bool autorun)
{
	isRunning = false;
	frame = 0;

	bool sdl_initialized = SDL_Init(SDL_INIT_EVERYTHING);
	if(sdl_initialized != 0)
	{
		std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
		return;
	}
	bool ttf_initialized = TTF_Init();
	if(ttf_initialized == -1)
	{
		std::cout << "SDL_TTF could not initialize! SDL Error: " << TTF_GetError() << std::endl;
		return;
	}

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
	if(window == NULL)
	{
		std::cout << "SDL could not make a window! SDL Error: " << SDL_GetError() << std::endl;
		return;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	if(window == NULL)
	{
		std::cout << "SDL could not make a renderer! SDL Error: " << SDL_GetError() << std::endl;
		return;
	}

	isRunning = true;
	std::cout << "Game Initialized!" << std::endl;

	if(autorun)
	{
		run();
	}
}

/**
 * @brief The main game loop. Updates clock, checks for events, updates game logic, and renders the screen.
 * Exits if isRunning is false.
 */
void BaseGame::run()
{
	std::cout << "Running game..." << std::endl;
	SDL_Event event;

	while (isRunning)
	{
		frame++;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;

			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					isRunning = false;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, frame, frame, frame, 255);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
	}
}

/**
 * @brief Frees your resources with cleanup(), destroys LilyEngine and SDL systems.
 */
BaseGame::~BaseGame()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	SDL_Quit();
}
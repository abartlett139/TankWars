#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
class Item
{
public:
	SDL_Rect rect;
	SDL_Texture *texture;

	char* file;
	double x, y, angle, speed;

	Item();
	Item(SDL_Renderer *ren, char* file, float x, float y);
	~Item();

	void update(float deltaTime);
	void draw(SDL_Renderer *ren);
};


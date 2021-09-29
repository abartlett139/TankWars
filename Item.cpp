#include "Item.h"



Item::Item()
{
}

Item::Item(SDL_Renderer *ren, char* file, float x, float y) {
	texture = IMG_LoadTexture(ren, file);
	if (!texture)printf(SDL_GetError());
	SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);

	rect.x = x;
	rect.y = y;
	angle = 0;
	speed = 0;
}


Item::~Item()
{
	SDL_DestroyTexture(texture);
}

void Item::update(float deltaTime) {

}

void Item::draw(SDL_Renderer *ren) {
	SDL_RenderCopy(ren, texture, NULL, &rect);
}

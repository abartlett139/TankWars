#include "Turret.h"



Turret::Turret(SDL_Renderer *ren, float x, float y)
{

	active = true;
	fire = Mix_LoadWAV("fire.wav");
	baseTexture = IMG_LoadTexture(ren, "turret.png");
	barrelTexture = IMG_LoadTexture(ren, "turretBarrel.png");

	basePos.x = x;
	basePos.y = y;
	angle = 0;
	SDL_QueryTexture(baseTexture, NULL, NULL, &basePos.w, &basePos.h);
	SDL_QueryTexture(barrelTexture, NULL, NULL, &barrelPos.w, &barrelPos.h);

	center.x = 10;
	center.y = 10;

	barrelPos.x = x + 21/2;
	barrelPos.y = y + 21/2;

	turretBullet *temp;

	for (int i = 0; i < 10; i++) {
		temp = new turretBullet(ren, 500, 500);
		bulletList.push_back(temp);
	}

}


Turret::~Turret()
{
}

void Turret::draw(SDL_Renderer *ren) {
	for (int i = 0; i < bulletList.size(); i++) {
	if(bulletList[i]->active)
	bulletList[i]->draw(ren);
	}

	SDL_RenderCopy(ren, baseTexture, NULL, &basePos);

	SDL_RenderCopyEx(ren, barrelTexture, NULL, &barrelPos, angle, &center, SDL_FLIP_NONE);
}

void Turret::update(float deltaTime, SDL_Rect playerPos) {

	x = (playerPos.x + playerPos.w / 2) - (basePos.x + basePos.w / 2);
	y = (playerPos.y + playerPos.h / 2) - (basePos.y + basePos.h / 2);
	angle = atan2(y, x) * 180 / 3.14159;

	if (SDL_GetTicks() > fireTime) {
		createBullet(playerPos);
		fireTime = SDL_GetTicks() + (rand() % 3 + 1) * 1000;
	}

	for (int i = 0; i < bulletList.size(); i++) {
		if (bulletList[i]->active)
			bulletList[i]->update(deltaTime);
	}
}

void Turret::createBullet(SDL_Rect target) {
	for (int i = 0; i < bulletList.size(); i++) {
		if (!bulletList[i]->active)
			bulletList[i]->start(target, basePos);
			bulletList[i]->active = true;
			Mix_PlayChannel(-1, fire, 0);
			bulletList[i]->pos.x = (basePos.x + basePos.w / 2) - (bulletList[i]->pos.w / 2);
			bulletList[i]->pos.y = (basePos.y + basePos.h / 2) - (bulletList[i]->pos.h / 2);
			bulletList[i]->x = bulletList[i]->pos.x;
			bulletList[i]->y = bulletList[i]->pos.y;
			break;
	}
}
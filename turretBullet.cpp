#include "turretBullet.h"



turretBullet::turretBullet(SDL_Renderer *ren, float x, float y)
{
	active = false;
	speed = 600;
	texture = IMG_LoadTexture(ren, "bullet.png");
	SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
	pos.x = x;
	pos.y = y;
	this->x = x;
	this->y = y;
	
}


turretBullet::~turretBullet()
{
}


void turretBullet::reset() {
	pos.x = -1000;
	x = -1000;
	active = false;
}


void turretBullet::start(SDL_Rect playerPos, SDL_Rect turretPos) {
	player.x = playerPos.x;
	player.y = playerPos.y;

	turret.x = turretPos.x;
	turret.y = turretPos.y;

	distance = sqrt((player.x - turret.x)*(player.x - turret.x) + (player.y - turret.y)*(player.y - turret.y));
}


void turretBullet::update(float deltaTime) {
	float vx = ((player.x - 20) - turret.x) / distance;
	float vy = ((player.y - 40) - turret.y) / distance;

	x += vx*speed*deltaTime;
	y += vy*speed*deltaTime;

	pos.x = x;
	pos.y = y;

	if (x > 1024 || x < -pos.w || y > 768 || y < -pos.h)
		reset();
}


void turretBullet::draw(SDL_Renderer *ren) {
	SDL_RenderCopy(ren, texture, NULL, &pos);
}

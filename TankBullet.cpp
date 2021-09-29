#include "TankBullet.h"



TankBullet::TankBullet(SDL_Renderer *ren, char *file, float x, float y, Sint16 xDir, Sint16 yDir)
{
	active = false;
	this->x = xDir;
	this->y = yDir;
	speed = 200;

	texture = IMG_LoadTexture(ren, "bullet.png");

	SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);
	pos.x = x - pos.w / 2;
	pos.y = y - pos.h / 2;

}


TankBullet::~TankBullet()
{
	//SDL_DestroyTexture(texture);
}


void TankBullet::update(float deltaTime){
		
	x += speed*deltaTime*xDir;
	y += speed*deltaTime*yDir;

	pos.x = x;
	pos.y = y;

	//reset if off screen
	if (x > 1024+pos.w || x < -pos.w || y>768+pos.h || y < -pos.h) {
		reset();
	}
}

void TankBullet::draw(SDL_Renderer *ren){
	SDL_RenderCopy(ren, texture, NULL, &pos);
}

void TankBullet::reset(){
	pos.x = -1000;
	active = false;
}
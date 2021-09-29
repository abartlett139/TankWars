#include "Tank.h"



Tank::Tank(SDL_Renderer *ren, int playerNumber, char* textureFile, char *turretFile, char *audioFile, float x, float y)
{
	active = true;
	this->playerNumber - playerNumber;
	this->x = x;
	this->y = y;
	speed = .005f;

	fire = Mix_LoadWAV(audioFile);
	



	texture = IMG_LoadTexture(ren, textureFile);
	if (!texture)printf(SDL_GetError());

	turretTexture = IMG_LoadTexture(ren, turretFile);
	if (!turretTexture)printf(SDL_GetError());

	turretCenter.x = 11;
	turretCenter.y = 11;

	turretPos.x = x + 20;
	turretPos.y = y + 12;

	SDL_QueryTexture(turretTexture, NULL, NULL, &turretPos.w, &turretPos.h);

	pos.x = x;
	pos.y = y;

	SDL_QueryTexture(texture, NULL, NULL, &pos.w, &pos.h);

	xDir = 0;
	yDir = 0;
	xDirOld = 0;
	yDirOld = 0;

	angle = 0;
	oldAngle = 0;
	turretAngle = 0;
	oldTurretAngle = 0;
	targetAngle = 0;
	turretTargetAngle = 0;

	for (int i = 0; i < 20; i++) {
		TankBullet temp(ren, "bullet.png", -1000, -1000, 0, 0);
		bulletList.push_back(temp);
	}


	equipment.x = 900;
	equipment.y = 0;
	equipment.w = 60;
	equipment.h = 60;

	backdrop.x = 340;
	backdrop.y = 250;
	backdrop.h = 180;
	backdrop.w = 380;

	selection.x = backdrop.x + 20;
	selection.y = backdrop.y + 20;
	selection.w = 40;
	selection.h = 40;
}


Tank::~Tank()
{
}



void Tank::update(float deltaTime) {
	//update tank position/direction
	if (xDir > 5000 || xDir < -5000 || yDir > 5000 || yDir < -5000) {
		if (xDir != 0 || yDir != 0) {
			turretAngle = angle = atan2(yDir, xDir)toDeg;
			oldAngle = angle;
			xDirOld = xDir;
			yDirOld = yDir;
			//printf("%d, %d\n", xDir, yDir);
		}
		else {
			turretAngle = angle = oldAngle;
		}
		x += speed*xDir*deltaTime;
		y += speed*yDir*deltaTime;
		turretPos.x = x + 20;
		turretPos.y = y + 12;
		pos.x = x;
		pos.y = y;
	}
	//update turret angle
	if (turretxDir > 5000 || turretxDir < -5000 || turretyDir > 5000 || turretyDir < -5000) {
		turretAngle = atan2(turretyDir, turretxDir)toDeg;
	}

	//update tank bullets
	for (int i = 0; i < bulletList.size(); i++) {
		if (bulletList[i].active) {
			bulletList[i].update(deltaTime);
		}
	}
	
}

void Tank::draw(SDL_Renderer *ren) {

	

	//draw tank
	SDL_RenderCopyEx(ren, texture, NULL, &pos, angle, NULL, SDL_FLIP_NONE);

	//draw tank bullets
	for (int i = 0; i < bulletList.size(); i++) {
		if (bulletList[i].active) {
			bulletList[i].draw(ren);
		}
	}
	//draw tank turret
	SDL_RenderCopyEx(ren, turretTexture, NULL, &turretPos, turretAngle, &turretCenter, SDL_FLIP_NONE);

	
}

void Tank::reset() {

}

void Tank::createBullet() {
	for (int i = 0; i < bulletList.size(); i++) {
		if (!bulletList[i].active) {
			bulletList[i].active = true;
			bulletList[i].x = x + pos.w / 2;
			bulletList[i].y = y + pos.h / 2;
			bulletList[i].xDir = cos(turretAngle*3.14159/180);
			bulletList[i].yDir = sin(turretAngle*3.14159/180);
			Mix_PlayChannel(-1, fire, 0);
			break;
		}
	}
}


void Tank::openInv(SDL_GameController *gc, SDL_Renderer *ren, float& lastTime) {
	bool quit = false;

	SDL_Event e;

	Sint16 xDir = 0, yDir = 0;

	float time = 0, deltaTime, deltaTime2=0;


	while (!quit) {
		deltaTime = (SDL_GetTicks() - time) / 1000;
		time = SDL_GetTicks();
		deltaTime2 += deltaTime;
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_CONTROLLERAXISMOTION:
				xDir = SDL_GameControllerGetAxis(gc, SDL_CONTROLLER_AXIS_LEFTX);
				yDir = SDL_GameControllerGetAxis(gc, SDL_CONTROLLER_AXIS_LEFTY);
				break;
			case SDL_CONTROLLERBUTTONDOWN:
				if (e.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
					if (e.cbutton.which == 0) {
						//find out which item is in the selection box
						for (int i = 0; i < inventory.size(); i++) {
							//if item is in the box, set that item to the tanks equipped item
							if (selection.x == inventory[i]->rect.x && inventory[i]->rect.y) {
								equipped = inventory[i];
								break;
							}
							else {
								equipped = NULL;
							}
						}
					}
				}
				quit = true; //exit after selection

				if (e.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
					if (e.cbutton.which == 0) {
						quit = true;
						break;
					}
				}
				break;
			}
		}

		//move the selection rectangle
		if (deltaTime2 > .1) {
			if (xDir > 20000)
				selection.x += 50;
			if (xDir < -20000)
				selection.x -= 50;
			if (yDir > 20000)
				selection.y += 50;
			if (yDir < -20000)
				selection.y -= 50;


			if (selection.x < backdrop.x)
				selection.x = (backdrop.x + 6 * 50) + 20;
			if (selection.x > backdrop.x + 50 * 7)
				selection.x = backdrop.x + 20;

			if (selection.y < backdrop.y)
				selection.y = (backdrop.y + 2 * 50) + 20;
			if (selection.y > backdrop.y + 50 * 3)
				selection.y = backdrop.y + 20;

			//reset timer so rectangle doesn't fly all over the place
			deltaTime2 = 0;
		}


		//draw stuff
		//set blendmode, also set it back to opaque in main
		SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(ren, 100, 100, 100, 10);
		SDL_RenderFillRect(ren, &backdrop);
		SDL_SetRenderDrawColor(ren, 200, 0, 200, 255);
		SDL_RenderDrawRect(ren, &selection);

		for (int i = 0; i < inventory.size(); i++) {
			SDL_RenderCopy(ren, inventory[i]->texture, NULL, &inventory[i]->rect);
		}
		SDL_RenderPresent(ren);
	}
	//resent last time
	lastTime = SDL_GetTicks();

}

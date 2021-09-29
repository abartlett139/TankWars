#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_mixer.h>
#include "Tank.h"
#include "Turret.h"
#include "Item.h"
#include <vector>


float deltaTime = 0;
float lastTime = 0;

int main(int argc, char** argv) {

	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window *window = SDL_CreateWindow("TANKS OUT FOR HARAMBE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);

	SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	bool quit = false;

	SDL_Event e;

	SDL_GameController *gc = SDL_GameControllerOpen(0);

	SDL_JoystickID p1id = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(gc));

	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	Mix_Music *bgm = Mix_LoadMUS("TSWIFT.mp3");
	if (!Mix_PlayingMusic())
		Mix_PlayMusic(bgm, -1);

	Tank tank1 = Tank(ren, 0, "tank.png", "tankTurret.png", "fire.wav", 50, 50);

	Turret turret1 = Turret(ren, 700, 500);

	std::vector<Item*> item;

	item.push_back(new Item(ren, "icon.png", 200, 200));
	item.push_back(new Item(ren, "icon2.png", 300, 0));
	item.push_back(new Item(ren, "icon3.png", 400, 400));



	while (!quit) {
		deltaTime = (SDL_GetTicks() - lastTime) / 1000;
		lastTime = SDL_GetTicks();
		while (SDL_PollEvent(&e) != 0) {
			switch (e.type) {
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_CONTROLLERAXISMOTION:
				tank1.xDir = SDL_GameControllerGetAxis(gc, SDL_CONTROLLER_AXIS_LEFTX);
				tank1.yDir = SDL_GameControllerGetAxis(gc, SDL_CONTROLLER_AXIS_LEFTY);

				tank1.turretxDir = SDL_GameControllerGetAxis(gc, SDL_CONTROLLER_AXIS_RIGHTX);
				tank1.turretyDir = SDL_GameControllerGetAxis(gc, SDL_CONTROLLER_AXIS_RIGHTY);
				break;
			case SDL_CONTROLLERBUTTONDOWN:
				if (e.cbutton.which == p1id) {
					if (e.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
						tank1.createBullet();
					}
					if (e.cbutton.button == SDL_CONTROLLER_BUTTON_Y) {
						tank1.openInv(gc, ren, lastTime);
					}
				}
				break;
			}
		}

		//update stuff
		tank1.update(deltaTime);
		turret1.update(deltaTime, tank1.pos);
		//draw stuff
		SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_NONE);
		SDL_RenderClear(ren);

		for (int i = 0; i < item.size(); i++) {
			item[i]->draw(ren);
			if (SDL_HasIntersection(&tank1.pos, &item[i]->rect)) {
				item[i]->rect.x = tank1.backdrop.x + 20 + tank1.inventory.size() * 50;
				item[i]->rect.y = tank1.backdrop.y + 20;
				tank1.inventory.push_back(item[i]);

				item.erase(item.begin() + i);
			}
			
		}

		for (int i = 0; i < item.size(); i++) {
			
		}

		SDL_SetRenderDrawColor(ren, 61, 61, 61, 255);
		//tank1.turretAngle += .05;
		tank1.draw(ren);
		turret1.draw(ren);
		SDL_RenderPresent(ren);
	}

	SDL_Quit();
	return 0;
}
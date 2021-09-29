#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include <math.h>
#include <stdlib.h>
#include "turretBullet.h"

class Turret
{
public:
	bool active;
	std::vector<turretBullet*> bulletList;
	SDL_Texture *baseTexture, *barrelTexture;
	SDL_Rect basePos, barrelPos;
	float speed, angle, x, y, distance, fireTime, fireDelay;
	SDL_Point turret, player, center;
	Mix_Chunk *fire;

	Turret(SDL_Renderer *ren, float x, float y);
	~Turret();

	void update(float deltaTime, SDL_Rect player);
	void draw(SDL_Renderer *ren);
	void createBullet(SDL_Rect target);

};


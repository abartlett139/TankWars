#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <SDL_mixer.h>
#include <vector>
#include <math.h>
#include "TankBullet.h"
#include "Item.h"

#define toDeg *(180/3.14159)

class Tank
{
public:
	bool active;

	std::vector<TankBullet>bulletList;
	std::vector<Item*> inventory;


	Item *equipped = NULL;

	//add backdrop, equipment and selection rectangle
	SDL_Rect backdrop, selection, equipment;

	char* file;
	int playerNumber;
	SDL_Texture *texture, *turretTexture;
	SDL_Rect pos, turretPos;

	SDL_Point turretCenter;

	Sint16 xDir, yDir, xDirOld, yDirOld, turretxDir, turretyDir;

	float speed, x, y, angle, oldAngle, targetAngle, oldTurretAngle, turretAngle, turretTargetAngle;

	Mix_Chunk *fire;

	bool showInventory;

	Tank(SDL_Renderer *ren, int playerNumber, char* textureFile, char *turrentTexture, char *audioFile, float x, float y);
	~Tank();

	void update(float deltaTime);
	void draw(SDL_Renderer *ren);
	void reset();
	void createBullet();

	void openInv(SDL_GameController *gc, SDL_Renderer *ren, float& lastTime);

};


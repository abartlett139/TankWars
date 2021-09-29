#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include <math.h>
#include <stdlib.h>
class turretBullet
{
public:
	bool active;
	SDL_Texture *texture;
	SDL_Rect pos;
	float speed, angle, x, y, distance;
	SDL_Point turret, player;
	Sint16 xDir, yDir;

	turretBullet(SDL_Renderer *ren, float x, float y);
	~turretBullet();

	void reset();
	void start(SDL_Rect playerPos, SDL_Rect turretPos);
	void update(float deltaTime);
	void draw(SDL_Renderer *ren);
};


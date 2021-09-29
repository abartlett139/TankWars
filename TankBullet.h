#include <SDL.h>
#include <SDL_image.h>

class TankBullet
{
public:

	bool active;
	SDL_Texture *texture;
	SDL_Rect pos;
	float xDir, yDir, speed, angle, x, y;

	TankBullet(SDL_Renderer *ren, char *file, float x, float y, Sint16 xDir, Sint16 yDir);
	~TankBullet();

	void update(float deltaTime);
	void draw(SDL_Renderer *ren);
	void reset();
};


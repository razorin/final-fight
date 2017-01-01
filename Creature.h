#ifndef CREATURE_H
#define CREATURE_H

#include "Entity.h"

struct SDL_Texture;


class Creature : public Entity {
public:
	Creature(SDL_Texture* graphics);
	~Creature();

public:
	int max_life;
	int life;
	int lives;
};

#endif // !CREATURE_H


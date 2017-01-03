#ifndef CREATURE_H
#define CREATURE_H

#include "Entity.h"

struct SDL_Texture;


class Creature : public Entity {
public:
	Creature(ENTITY_TYPE type);
	~Creature();

public:
	int max_life = 100;
	int life = 100;
	int lives = 1;
};

#endif // !CREATURE_H


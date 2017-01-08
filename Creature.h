#ifndef CREATURE_H
#define CREATURE_H

#include "Entity.h"
#include "Point.h"
#include "Parson.h"

struct SDL_Texture;


class Creature : public Entity {
public:
	Creature(const JSON_Object *playerConfig, ENTITY_TYPE type);
	Creature(Creature const *other);
	~Creature();
	void Move(const iPoint &movement);

public:
	int max_life = 100;
	int life = 100;
	int lives = 1;
	int attack = 0;
	iPoint speed{ 0,0,0 };
	int baseSpeed = 1;
};

#endif // !CREATURE_H


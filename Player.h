#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "Globals.h"
#include "Point.h"
#include "Parson.h"

class Animation;
struct Frame;
struct SDL_Texture;

class Player : public Creature {
public:
	Player(const JSON_Object *playerConfig);
	~Player();
	void Update();
	void OnCollision(const Collider &other);
	void Move(const iPoint &movement);
	void Init(const iPoint &initialPosition);

private:
	bool is_attacking = false;
	bool is_jumping = false;
	bool is_falling = false;
	iPoint previousPosition;
};

#endif // !PLAYER_H


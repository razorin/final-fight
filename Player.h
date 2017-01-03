#ifndef PLAYER_H
#define PLAYER_H
#include "Creature.h"
#include "Globals.h"
#include "Point.h"

struct Animation;
struct Frame;
struct SDL_Texture;


class Player : public Creature {
public:
	Player();
	~Player();
	void Update();
	void OnCollision(COLLIDER_TYPE type);
	void Move(const iPoint &movement);

private:
	bool is_attacking = false;
	iPoint previousPosition;
};

#endif // !PLAYER_H


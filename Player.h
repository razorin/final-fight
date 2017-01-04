#ifndef PLAYER_H
#define PLAYER_H
#include "Creature.h"
#include "Globals.h"
#include "Point.h"

struct Animation;
struct Frame;
struct SDL_Texture;
class Timer;

class Player : public Creature {
public:
	Player();
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
	Timer *timer;
};

#endif // !PLAYER_H


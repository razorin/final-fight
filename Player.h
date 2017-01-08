#ifndef PLAYER_H
#define PLAYER_H

#include "Creature.h"
#include "Globals.h"
#include "Point.h"
#include "Parson.h"
#include "PlayerStateMachine.h"

class Animation;
struct Frame;
struct SDL_Texture;
class Enemy;
class Timer;

class Player : public Creature {

public:
	Player(const JSON_Object *playerConfig);
	~Player();
	void Update();
	void OnCollision(const Collider &other);
	void TakeDamage(Enemy *enemy);
	void Init(const iPoint &initialPosition);
	void AddHit();

private:
	iPoint previousPosition = {0,0,0};
	PlayerStateMachine *state = nullptr;
public:
	int hits = 0;
	Collider *attackCollider = nullptr;
	Timer *hitsTimer;
};

#endif // !PLAYER_H


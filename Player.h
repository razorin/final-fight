#ifndef PLAYER_H
#define PLAYER_H
#include "Creature.h"

struct Animation;
struct Frame;
struct SDL_Texture;


class Player : public Creature {
public:
	Player(SDL_Texture* graphics);
	~Player();
	void Update();
public:
	Animation *idle = nullptr;
	Animation *movement = nullptr;
	Animation *jump = nullptr;
	Animation *attack1 = nullptr;
};

#endif // !PLAYER_H


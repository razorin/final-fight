#ifndef PLAYER_H
#define PLAYER_H
#include "Creature.h"

struct SDL_Texture;


class Player : public Creature {
public:
	Player(SDL_Texture* graphics);
	~Player();
	void Update();
};

#endif // !PLAYER_H


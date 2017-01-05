#ifndef CODY_IDLE_FALL_H
#define CODY_IDLE_FALL_H

#include "CodyStateMachine.h"

class Player;

class CodyIdleFall : public CodyStateMachine {
public:
	CodyIdleFall();
	~CodyIdleFall();
	void Start(Player *player);
	PlayerStateMachine * Update(Player *player);
};

#endif // !CODY_IDLE_FALL_H


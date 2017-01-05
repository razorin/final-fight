#ifndef CODY_STATE_MACHINE_H
#define CODY_STATE_MACHINE_H

#include "PlayerStateMachine.h"

class Player;

class CodyStateMachine : public PlayerStateMachine {
public:
	CodyStateMachine() {

	}
	~CodyStateMachine() {

	}
	
	void Start(Player *player) {

	}

	PlayerStateMachine * Update(Player *player) {
		return nullptr;
	}

};

#endif // !CODY_STATE_MACHINE_H


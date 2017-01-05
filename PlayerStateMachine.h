#ifndef PLAYER_STATE_MACHINE_H
#define PLAYER_STATE_MACHINE_H

enum PLAYER_STATES {
	IDLE,
	IDLE_JUMP,
	IDLE_JUMP_ATTACK,
	MOVEMENT,
	ATTACK_1,
	MOVEMENT_JUMP,
	MOVEMENT_JUMP_ATTACK
};

class Player;

class PlayerStateMachine {
public:
	PlayerStateMachine() {

	}
	virtual void Start(Player *player) = 0;
	virtual PlayerStateMachine * Update(Player *player) = 0;
	virtual ~PlayerStateMachine() {

	}
};

#endif // !PLAYER_STATE_MACHINE_H


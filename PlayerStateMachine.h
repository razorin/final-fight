#ifndef PLAYER_STATE_MACHINE_H
#define PLAYER_STATE_MACHINE_H

//Only for dynamic changes
enum PLAYER_STATE {
	PLAYER_DAMAGE_STATE,
	PLAYER_KILLED_STATE,
	PLAYER_OTHER_STATE
};

class Player;

class PlayerStateMachine {
public:
	PlayerStateMachine(PLAYER_STATE state = PLAYER_STATE::PLAYER_OTHER_STATE);
	virtual void Start(Player *player) = 0;
	virtual PlayerStateMachine * Update(Player *player) = 0;
	virtual PlayerStateMachine * ChangeState(PLAYER_STATE playerState) = 0;
	virtual ~PlayerStateMachine();

protected:
	PLAYER_STATE state;
};

#endif // !PLAYER_STATE_MACHINE_H


#include "CodyStateMachine.h"
#include "CodyDamageState.h"
#include "CodyKilledState.h"

CodyStateMachine::CodyStateMachine(PLAYER_STATE state) : PlayerStateMachine(state) {

}
CodyStateMachine::~CodyStateMachine() {

}

void CodyStateMachine::Start(Player *player) {

}

PlayerStateMachine * CodyStateMachine::Update(Player *player) {
	return nullptr;
}

PlayerStateMachine *CodyStateMachine::ChangeState(PLAYER_STATE playerState) {
	if (playerState == state)
		return nullptr;

	switch (playerState) {
	case PLAYER_DAMAGE_STATE:
		return new CodyDamageState();
		break;
	default:
		return new CodyKilledState();
		break;
	}
}
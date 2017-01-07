#include "CodyAttackStateOne.h"
#include "Player.h"
#include "Animation.h"
#include "CodyIdleState.h"
#include "Application.h"
#include "ModuleInput.h"

CodyAttackStateOne::CodyAttackStateOne() {
}


CodyAttackStateOne::~CodyAttackStateOne() {
}

void CodyAttackStateOne::Start(Player *player) {


	player->setCurrentAnimation(player->animations["attack3"]);

	switch (player->hits) {
	case 2:
		player->setCurrentAnimation(player->animations["attack2"]);
		break;
	case 3:
		player->setCurrentAnimation(player->animations["attack3"]);
		break;
	default:
		player->setCurrentAnimation(player->animations["attack1"]);
		break;
	}
	
	++player->hits;
}

PlayerStateMachine *CodyAttackStateOne::Update(Player *player) {
	if (player->getCurrentAnimation()->Finished()) {
		return new CodyIdleState();
	}
	return nullptr;
}
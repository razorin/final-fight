#include "CodyAttackStateOne.h"
#include "Player.h"
#include "Animation.h"
#include "CodyIdleState.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleCollision.h"

CodyAttackStateOne::CodyAttackStateOne() {
}


CodyAttackStateOne::~CodyAttackStateOne() {
}

void CodyAttackStateOne::Start(Player *player) {


	player->setCurrentAnimation("attack3");

	switch (player->hits) {
	case 2:
		player->setCurrentAnimation("attack2");
		break;
	case 3:
		player->setCurrentAnimation("attack3");
		break;
	default:
		player->setCurrentAnimation("attack1");
		break;
	}

	if (player->attackCollider != nullptr) {
		player->attackCollider->to_delete = true;
	}
	int attack_x = player->positionCollider->rect.x + (player->flipped ? -(player->positionCollider->rect.w / 2) : (player->positionCollider->rect.w / 2));
	int attack_w = player->positionCollider->rect.w;
	player->attackCollider = App->collision->AddCollider({attack_x, player->positionCollider->rect.y, attack_w, player->positionCollider->rect.h}, COLLIDER_TYPE::PLAYER_HIT, false, false, std::bind(&Player::OnCollision, player, std::placeholders::_1), player);
	
	//++player->hits;
}

PlayerStateMachine *CodyAttackStateOne::Update(Player *player) {
	if (player->getCurrentAnimation()->Finished()) {
		return new CodyIdleState();
	}
	return nullptr;
}
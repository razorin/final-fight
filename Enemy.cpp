#include "Enemy.h"
#include "Globals.h"
#include "ModuleCollision.h"
#include "EnemyIdleState.h"
#include <cassert>
#include "Player.h"
#include "Point.h"

Enemy::Enemy(const JSON_Object *enemyConfig, ENEMY_TYPE type) : type(type), Creature(enemyConfig, ENTITY_TYPE::ENEMY){
	state = new EnemyIdleState();
	JSON_Array *configAttacks = json_object_dotget_array(enemyConfig, "attacks");

	for (int i = 0; i < json_array_get_count(configAttacks); ++i) {
		JSON_Object *configAttack = json_array_get_object(configAttacks, i);
		attacks.push_back(json_object_dotget_string(configAttack, "name"));
	}
}

Enemy::Enemy(const Enemy *other) : type(other->type), attacks(other->attacks), Creature(other){
	state = new EnemyIdleState();
}


Enemy::~Enemy() {
	RELEASE(state);
	if (attackCollider != nullptr)
		attackCollider->to_delete = true;
}

iPoint &Enemy::distanceToTarget() const {
	iPoint result{ 0,0,0 };
	if (player != nullptr) {
		iPoint playerPoint = player->getBottomPoint();
		iPoint enemyPoint = getBottomPoint();
		result = playerPoint - enemyPoint;
	}
	//TODO: Random target to move enemy!
	return result;
}



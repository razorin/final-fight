#include "Enemy.h"
#include "Globals.h"
#include "ModuleCollision.h"

Enemy::Enemy(ENEMY_TYPE type) : type(type), Creature(ENTITY_TYPE::ENEMY){
}


Enemy::~Enemy() {
	RELEASE(state);
	if (attackCollider != nullptr)
		attackCollider->to_delete = true;

}

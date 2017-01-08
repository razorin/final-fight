#include "Creature.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"

Creature::Creature(const JSON_Object *creatureConfig, ENTITY_TYPE type) : Entity(type) {
	life = (int)json_object_dotget_number(creatureConfig, "life");
	max_life = life;
	attack = (int)json_object_dotget_number(creatureConfig, "attack");
	lives = (int)json_object_dotget_number(creatureConfig, "lives");
	baseSpeed = (int)json_object_dotget_number(creatureConfig, "baseSpeed");
}

Creature::Creature(Creature const *other) : baseSpeed(other->baseSpeed), 
	lives(other->lives), max_life(other->life), attack(other->attack),
	life(other->life), Entity(other->type) 
{
	
}


Creature::~Creature() {
}

void Creature::Move(const iPoint &movement) {
	*position += movement;
	positionCollider->AddPoint(movement);
}
#include "Creature.h"
#include "SDL/include/SDL.h"
#include "ModuleCollision.h"

Creature::Creature(const JSON_Object *creatureConfig, ENTITY_TYPE type) : Entity(type) {
	life = (int)json_object_dotget_number(creatureConfig, "life");
	max_life = life;
	attack = (int)json_object_dotget_number(creatureConfig, "attack");
	lives = (int)json_object_dotget_number(creatureConfig, "lives");
	baseSpeed = (int)json_object_dotget_number(creatureConfig, "baseSpeed");

	JSON_Array *configAttacks = json_object_dotget_array(creatureConfig, "attacks");

	for (int i = 0; i < json_array_get_count(configAttacks); ++i) {
		JSON_Object *configAttack = json_array_get_object(configAttacks, i);
		Attack attack;
		attack.name = json_object_dotget_string(configAttack, "name");
		attack.x = (int)json_object_dotget_number(configAttack, "x");
		attack.y = (int)json_object_dotget_number(configAttack, "y");
		attacks.push_back(attack);
	}
}

Creature::Creature(Creature const *other) : baseSpeed(other->baseSpeed), 
	lives(other->lives), max_life(other->life), attack(other->attack),
	life(other->life), Entity(other->type), attacks(other->attacks)
{
	
}


Creature::~Creature() {
}

void Creature::Move(const iPoint &movement) {
	*position += movement;
	positionCollider->AddPoint(movement);
}
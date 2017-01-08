#include "Globals.h"
#include "Application.h"
#include "ModuleEntity.h"
#include "ModuleTextures.h"
#include "Entity.h"
#include "Player.h"
#include "Section.h"
#include "ModuleRender.h"
#include "Point.h"
#include "Enemy.h"
#include "Bred.h"
#include "ModuleCollision.h"

ModuleEntity::ModuleEntity(const JSON_Value *json, bool enable) : Module(json, enable) {
	config = json_value_get_object(json);
}


ModuleEntity::~ModuleEntity() {
	RELEASE(bred);
}

Entity* ModuleEntity::Create(const ENTITY_TYPE &type) {
	static_assert(ENTITY_TYPE::UNKNOWN == 2, "Update entity types");
	Entity *result = nullptr;

	switch (type) {
		case ENTITY_TYPE::PLAYER: 
			//json_object_dotget_object(root, "config.entities")
			result = new Player(json_object_dotget_object(config, "player"));
			break;
	}

	if (result != nullptr) {
		entities.push_back(result);
		entities.sort([](const Entity *a, const Entity *b) { return a->positionCollider->rect.y + a->positionCollider->rect.h > b->positionCollider->rect.y + b->positionCollider->rect.h;});
	}

	return result;
}

Entity* ModuleEntity::Create(const ENEMY_TYPE &type) {
	static_assert(ENEMY_TYPE::UNKNOWN_ENEMY == 1, "Update enemy types");
	Entity *result = nullptr;

	switch (type) {
	case ENEMY_TYPE::BRED :
		result = new Bred(bred);
		//result = new Bred(bred);
		break;
	}

	if (result != nullptr) {
		entities.push_back(result);
		entities.sort([](const Entity *a, const Entity *b) { return a->position->z < b->position->z;});
	}

	return result;
}

bool ModuleEntity::Start() {
	LOG("Started Module Entity");
	bred = new Bred(json_object_dotget_object(config, "enemies.bred"));
	return true;
}

update_status ModuleEntity::PreUpdate() {
	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end();) {
		if ((*it)->to_delete == true) {
			RELEASE(*it);
			it = entities.erase(it);
		}
		else
			++it;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleEntity::Update() {
	entities.sort([](const Entity *a, const Entity *b) { return a->positionCollider->rect.y + a->positionCollider->rect.h < b->positionCollider->rect.y + b->positionCollider->rect.h;});
	std::list<Entity*>::iterator it;
	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
		if ((*it)->active) {
			(*it)->Update();
			if (&(*it)->getCurrentFrame() != nullptr)
				App->renderer->Blit((*it)->getGraphics(), *(*it)->position, &(*it)->getCurrentFrame(), (*it)->flipped);
		}
		
	}
	return update_status::UPDATE_CONTINUE;
}

bool ModuleEntity::CleanUp() {
	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it)
		RELEASE(*it);

	entities.clear();
	return true;
}

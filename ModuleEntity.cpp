#include "Globals.h"
#include "Application.h"
#include "ModuleEntity.h"
#include "ModuleTextures.h"
#include "Entity.h"
#include "Player.h"
#include "Section.h"
#include "ModuleRender.h"
#include "Point.h"

ModuleEntity::ModuleEntity(bool enable) : Module(enable) {
}


ModuleEntity::~ModuleEntity() {
}

Entity* ModuleEntity::Create(const ENTITY_TYPE &type) {
	static_assert(ENTITY_TYPE::UNKNOWN == 2, "Update entity types");
	Entity *result = nullptr;

	switch (type) {
		case ENTITY_TYPE::PLAYER: 
			result = new Player(App->textures->Load("resources/sprites/characters/cody.png"));
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
	return true;
}

bool ModuleEntity::CleanUp() {
	return true;
}

update_status ModuleEntity::Update() {
	for (std::list<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
		(*it)->Update();
		if ((*it)->to_delete) {
			RELEASE(*it);
			entities.remove(*it);
		}
		else {
			App->renderer->Blit((*it)->getGraphics(), *(*it)->position, &(*it)->getCurrentFrame(), (*it)->flipped);
		}
	}
	return update_status::UPDATE_CONTINUE;
}



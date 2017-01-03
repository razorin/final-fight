#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Point.h"
#include "ModuleCollision.h"

#include "ModuleLevelOneStageOne.h"
#include "ModuleEntity.h"
#include "Player.h"
#include "Animation.h"

ModuleLevelOneStageOne::ModuleLevelOneStageOne(const JSON_Object *json, bool active) : Module(json, active) {
}


ModuleLevelOneStageOne::~ModuleLevelOneStageOne() {
}

bool ModuleLevelOneStageOne::Start() {
	LOG("Loading Level 1-1 ");

	graphics = App->textures->Load("resources/sprites/levels/level1.png");

	player = (Player *)App->entities->Create(ENTITY_TYPE::PLAYER);

	player->Move(iPoint(16, 120, 120));

	App->collision->AddCollider({ 0, 0, 992, 175 }, 80, WALL);
	App->collision->AddCollider({ 0, 225, 992, 3 }, 128, WALL);

	Collider *leftWall = App->collision->AddCollider({ 0, 0, 3, 225 }, 0, WALL, true);
	Collider *righttWall = App->collision->AddCollider({ 381, 0, 3, 225 }, 0, WALL, true);

	return true;
}

update_status ModuleLevelOneStageOne::Update() {
	Frame *scene = new Frame({ 265, 3, 992, 195 });
	App->renderer->Blit(graphics, iPoint{ 0, 30 }, scene);

	return UPDATE_CONTINUE;
}

bool ModuleLevelOneStageOne::CleanUp() {
	LOG("Unloading Level 1-1");

	return true;
}
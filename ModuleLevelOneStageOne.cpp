#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "Point.h"

#include "ModuleLevelOneStageOne.h"

ModuleLevelOneStageOne::ModuleLevelOneStageOne(bool active) : Module(active) {
}


ModuleLevelOneStageOne::~ModuleLevelOneStageOne() {
}

bool ModuleLevelOneStageOne::Start() {
	LOG("Loading Level 1-1 ");

	graphics = App->textures->Load("resources/sprites/levels/level1.png");

	return true;
}

update_status ModuleLevelOneStageOne::Update() {
	SDL_Rect *rect = new SDL_Rect();
	*rect = { 265, 3, 992, 195 };
	App->renderer->Blit(graphics, iPoint{ 0, 30 }, rect);

	return UPDATE_CONTINUE;
}

bool ModuleLevelOneStageOne::CleanUp() {
	LOG("Unloading Level 1-1");

	return true;
}
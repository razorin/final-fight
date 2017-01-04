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
#include "ModuleInput.h"
#include "ModuleWindow.h"

ModuleLevelOneStageOne::ModuleLevelOneStageOne(const JSON_Object *json, bool active) : Module(json, active) {
}


ModuleLevelOneStageOne::~ModuleLevelOneStageOne() {
}

bool ModuleLevelOneStageOne::Start() {
	LOG("Loading Level 1-1 ");

	graphics = App->textures->Load("resources/sprites/levels/level1.png");

	player = (Player *)App->entities->Create(ENTITY_TYPE::PLAYER);
	player->Init(iPoint(16, 80, 0));
	//player->Move(iPoint(16, 120, 120 + 88));

	upperWall = App->collision->AddCollider({ 0, 0, 992, 145 }, WALL);
	App->collision->AddCollider({ 0, 191, 992, 3 }, WALL);

	leftWall = App->collision->AddCollider({ 0, 0, 2, 191 }, CAMERA_WALL, true, true);
	righttWall = App->collision->AddCollider({ 380, 0, 2, 191 }, CAMERA_WALL, true, true);

	return true;
}

update_status ModuleLevelOneStageOne::Update() {
	Frame *scene = new Frame({ 265, 3, 992, 195 });
	App->renderer->Blit(graphics, iPoint{ 0, 0 }, scene);

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN) {
		LOG("Wall Position: %i,%i,%i,%i,%i (x, y, z)", upperWall->rect.x, upperWall->rect.w, upperWall->rect.y, upperWall->rect.h, upperWall->z);
	}
	int playerCenter = player->positionCollider->rect.x + player->positionCollider->rect.w / 2;
	int cameraCenter = (App->renderer->camera.w / App->window->screen_size - App->renderer->camera.x) / 2;
	int movement = playerCenter - cameraCenter;
	
	if (movement > 0) {
		LOG("Movement: %i Player Center: %i Camera Center: %i", movement, playerCenter, cameraCenter);
		App->renderer->camera.x -= (movement * App->window->screen_size);
		leftWall->AddPoint(iPoint(movement, 0));
		righttWall->AddPoint(iPoint(movement, 0));
	}


	return UPDATE_CONTINUE;
}

bool ModuleLevelOneStageOne::CleanUp() {
	LOG("Unloading Level 1-1");

	return true;
}
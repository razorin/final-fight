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
#include "Section.h"

ModuleLevelOneStageOne::ModuleLevelOneStageOne(const JSON_Value *json, bool active) : Module(json, active) {
	config = json_value_get_object(json);
}


ModuleLevelOneStageOne::~ModuleLevelOneStageOne() {
	Clear();
}

bool ModuleLevelOneStageOne::Start() {
	LOG("Loading Level 1-1 ");
	player = (Player *)App->entities->Create(ENTITY_TYPE::PLAYER);
	player->Init(iPoint(16, 80, 0));

	const char* path = json_object_dotget_string(config, "graphics");
	graphics = App->textures->Load(path);

	scene = new Frame({ (int)json_object_dotget_number(config, "scene.x"),
		(int)json_object_dotget_number(config, "scene.y"),
		(int)json_object_dotget_number(config, "scene.width"),
		(int)json_object_dotget_number(config, "scene.height")
	});

	JSON_Array *configWalls = json_object_dotget_array(config, "walls");

	for (int i = 0; i < json_array_get_count(configWalls); ++i) {
		JSON_Object *configWall = json_array_get_object(configWalls, i);
		App->collision->AddCollider({ (int)json_object_dotget_number(configWall, "x"),
			(int)json_object_dotget_number(configWall, "y"),
			(int)json_object_dotget_number(configWall, "width"),
			(int)json_object_dotget_number(configWall, "height")
		}, COLLIDER_TYPE::WALL,
			(bool)json_object_dotget_boolean(configWall, "ignore_z"),
			(bool)json_object_dotget_boolean(configWall, "ignore_y"));
	}

	JSON_Array *configCameraWalls = json_object_dotget_array(config, "cameraWalls");

	for (int i = 0; i < json_array_get_count(configCameraWalls); ++i) {
		JSON_Object *configCameraWall = json_array_get_object(configCameraWalls, i);
		Collider * collider = App->collision->AddCollider({ (int)json_object_dotget_number(configCameraWall, "x"),
			(int)json_object_dotget_number(configCameraWall, "y"),
			(int)json_object_dotget_number(configCameraWall, "width"),
			(int)json_object_dotget_number(configCameraWall, "height")
		}, COLLIDER_TYPE::CAMERA_WALL, true, true);
		std::string name = json_object_dotget_string(configCameraWall, "name");
		cameraWalls[name] = collider;
	}

	JSON_Array *configSections = json_object_dotget_array(config, "sections");
	sections.reserve((int)json_array_get_count(configSections));

	for (int i = 0; i < json_array_get_count(configSections); ++i) {
		JSON_Object *configSection = json_array_get_object(configSections, i);
		sections.push_back(new Section((int)json_object_dotget_number(configSection, "endPoint"), 
			(int)json_object_dotget_number(configSection, "numberOfEnemies")));
	}

	return true;
}

update_status ModuleLevelOneStageOne::Update() {
	
	App->renderer->Blit(graphics, iPoint{ 0, 0 }, scene);
	//If current section is finished, increment section
	if (sections.at(currentSection)->IsFinished() && currentSection + 1 < sections.size()) {
		++currentSection;
	}

	Section *section = sections.at(currentSection);
	//Camera Movement
	int playerCenter = player->positionCollider->rect.x + player->positionCollider->rect.w / 2;
	int cameraCenter = (App->renderer->camera.w / 2 - App->renderer->camera.x) / App->window->screen_size;
	int movement = playerCenter - cameraCenter;

	if (App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN) {
		section->EnemyKilled();
	}

	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) {
		LOG("Camera Center: %i Player Center: %i", cameraCenter, playerCenter);
		LOG("Camera (x,w) %i,%i", App->renderer->camera.x, App->renderer->camera.w);
	}

	if (movement > 0) {
		bool sectionReached = cameraWalls["right"]->rect.x + 1 >= section->section_ends;
		
		if (!sectionReached) {
			App->renderer->camera.x -= (App->window->screen_size);
			cameraWalls["left"]->AddPoint(iPoint(1, 0));
			cameraWalls["right"]->AddPoint(iPoint(1, 0));
		}
	}

	return UPDATE_CONTINUE;
}

bool ModuleLevelOneStageOne::CleanUp() {
	LOG("Unloading Level 1-1");
	Clear();
	return true;
}

void ModuleLevelOneStageOne::Clear() {
	for (auto it = cameraWalls.begin(); it != cameraWalls.end(); ++it) {
		it->second->to_delete = true;
	}
	cameraWalls.clear();
	for (int i = 0; i < sections.size(); ++i) {
		RELEASE(sections.at(i));
	}
	sections.clear();
	RELEASE(scene);
	//RELEASE(graphics);
	json_object_clear(config);
	RELEASE(config);
}
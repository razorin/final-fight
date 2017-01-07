#include "Bred.h"
#include "Animation.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleCollision.h"

int Bred::number_of_instances = 0;

Bred::Bred(const JSON_Object *bredConfig) : Enemy(ENEMY_TYPE::BRED){
	const char* path = json_object_dotget_string(bredConfig, "graphics");
	graphics = App->textures->Load(path);
	JSON_Array *configAnimations = json_object_dotget_array(bredConfig, "animations");

	for (int i = 0; i < json_array_get_count(configAnimations); ++i) {
		JSON_Object *configAnimation = json_array_get_object(configAnimations, i);
		std::string key = json_object_dotget_string(configAnimation, "name");

		Animation *anim = new Animation();
		anim->loop = json_object_dotget_boolean(configAnimation, "loop");
		anim->speed = json_object_dotget_number(configAnimation, "speed");

		JSON_Array *configFrames = json_object_dotget_array(configAnimation, "frames");

		for (int j = 0; j < json_array_get_count(configFrames); ++j) {
			JSON_Object *configFrame = json_array_get_object(configFrames, j);
			anim->frames.push_back(Frame({ (int)json_object_dotget_number(configFrame, "x"), (int)json_object_dotget_number(configFrame, "y"),
				(int)json_object_dotget_number(configFrame, "width"), (int)json_object_dotget_number(configFrame, "height") },
				(int)json_object_dotget_number(configFrame, "offset_x"), (int)json_object_dotget_number(configFrame, "offset_y")));
		}

		animations[key] = anim;
	}

	currentAnimation = animations["idle"];
	//state = new CodyIdleState();

	positionCollider = App->collision->AddCollider({ position->x, position->y, 37, 88 }, ENEMY_COLLIDER, false, false, std::bind(&Bred::OnCollision, this, std::placeholders::_1));
	//state->Start(this);
	++number_of_instances;
}

Bred::Bred(const Bred *other) : Enemy(other->type) {
	graphics = other->graphics;
	for (auto it = other->animations.begin(); it != other->animations.end(); ++it) {
		Animation *anim = new Animation((*it->second));
		animations[(it->first)] = anim;
	}
	currentAnimation = animations["idle"];
	position = new iPoint(*other->position);
	positionCollider = App->collision->AddCollider({ position->x, position->y, 37, 88 }, ENEMY_COLLIDER, false, false, std::bind(&Bred::OnCollision, this, std::placeholders::_1));
	++number_of_instances;
}


Bred::~Bred() {
	--number_of_instances;
	if (number_of_instances > 0)
		graphics = nullptr;
	currentAnimation = nullptr;
}

void Bred::Init(const iPoint &initialPosition) {
	active = true;
	*position = initialPosition;
	positionCollider->SetPos(position->x + 40, position->y + 15, position->z);
}

void Bred::OnCollision(const Collider &other) {

}

void Bred::Move(const iPoint &movement) {
	*position += movement;
	positionCollider->AddPoint(movement);
}
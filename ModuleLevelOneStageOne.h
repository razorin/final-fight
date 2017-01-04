#ifndef ModuleLevelOneStageOne_H
#define ModuleLevelOneStageOne_H

#include "Module.h"

struct SDL_Texture;
class Player;
struct Collider;

class ModuleLevelOneStageOne : public Module {
public:
	ModuleLevelOneStageOne(const JSON_Object *json, bool active);
	~ModuleLevelOneStageOne();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
	Player *player = nullptr;
	Collider *upperWall = nullptr;
	Collider *leftWall = nullptr;
	Collider *righttWall = nullptr;
};

#endif // !ModuleLevelOneStageOne_H

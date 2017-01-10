#ifndef ModuleLevelOneStageOne_H
#define ModuleLevelOneStageOne_H

#include "Module.h"
#include <map>
#include <vector>

struct SDL_Texture;
class Player;
struct Collider;
class Section;
class Enemy;

class ModuleLevelOneStageOne : public Module {
public:
	ModuleLevelOneStageOne(const JSON_Value *json, bool active);
	~ModuleLevelOneStageOne();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

private:
	void Clear();

public:
	SDL_Texture* graphics = nullptr;
	Player *player = nullptr;
	JSON_Object *config = nullptr;
	Frame *scene = nullptr;
	std::map<std::string, Collider*> cameraWalls;
	std::vector<Section*> sections;
	int currentSection = 0;
	Enemy *enemy = nullptr;

};

#endif // !ModuleLevelOneStageOne_H

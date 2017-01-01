#ifndef ModuleLevelOneStageOne_H
#define ModuleLevelOneStageOne_H

#include "Module.h"

struct SDL_Texture;

class ModuleLevelOneStageOne : public Module {
public:
	ModuleLevelOneStageOne(bool active);
	~ModuleLevelOneStageOne();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics = nullptr;
};

#endif // !ModuleLevelOneStageOne_H

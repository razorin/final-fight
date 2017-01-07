#ifndef MODULE_ENTITY_H
#define MODULE_ENTITY_H

#include <list>
#include "Module.h"
#include "Parson.h"

class Entity;
enum ENTITY_TYPE;
enum ENEMY_TYPE;
class Bred;

class ModuleEntity : public Module {
public:
	ModuleEntity(const JSON_Value *json, bool enable);
	~ModuleEntity();

	bool Start();
	update_status Update();
	bool CleanUp();

	Entity* Create(const ENTITY_TYPE &type);
	Entity* Create(const ENEMY_TYPE &type);

private:
	JSON_Object *config = nullptr;
	std::list<Entity*> entities;
	Bred *bred = nullptr;
};

#endif // !MODULE_ENTITY_H


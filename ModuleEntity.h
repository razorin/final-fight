#ifndef MODULE_ENTITY_H
#define MODULE_ENTITY_H

#include <list>
#include "Module.h"
#include "Parson.h"

class Entity;
enum ENTITY_TYPE;

class ModuleEntity : public Module {
public:
	ModuleEntity(const JSON_Value *json, bool enable);
	~ModuleEntity();

	bool Start();
	update_status Update();
	bool CleanUp();

	Entity* Create(const ENTITY_TYPE &type);

	JSON_Object *config = nullptr;
	std::list<Entity*> entities;
};

#endif // !MODULE_ENTITY_H


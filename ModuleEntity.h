#ifndef MODULE_ENTITY_H
#define MODULE_ENTITY_H

#include <list>
#include "Module.h"

class Entity;
enum ENTITY_TYPE;

class ModuleEntity : public Module {
public:
	ModuleEntity(const JSON_Object *json, bool enable);
	~ModuleEntity();

	bool Start();
	update_status Update();
	bool CleanUp();

	Entity* Create(const ENTITY_TYPE &type);


	std::list<Entity*> entities;
};

#endif // !MODULE_ENTITY_H


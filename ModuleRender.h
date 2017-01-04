#ifndef __MODULERENDER_H__
#define __MODULERENDER_H__

#include "Module.h"
#include "Globals.h"

template <class TYPE> class Point;
typedef Point<int> iPoint;

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_Rect;
struct Frame;
struct Collider;

class ModuleRender : public Module
{
public:
	ModuleRender(const JSON_Object *json = nullptr);
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, iPoint &position, Frame* section, bool flip = false, float speed = 1.0f);
	bool DrawQuad(const Collider& collider, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera = true);

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;
	bool vsync = false;
};

#endif // __MODULERENDER_H__
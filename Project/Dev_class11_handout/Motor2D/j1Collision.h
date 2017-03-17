#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 300
#include"j1App.h"
#include"j1Module.h"
#include "SDL\include\SDL.h"
#include "j1Object.h"
enum COLLIDER_TYPE
{
	//example
	COLLIDER_NONE = -1,
	link,
	zelda,
	collider_chest,
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	j1Module* callback = nullptr;
	uint logic_height;
	Entity* parent = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Entity* parent, j1Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback),
		parent(parent)
	{
		logic_height = 1;
	}

	void SetPos(int x, int y, int n_logic_height)
	{
		rect.x = x;
		rect.y = y;
		logic_height = n_logic_height;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class j1Collision : public j1Module
{
public:

	j1Collision();
	~j1Collision();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	//update_status PostUpdate();
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type,Entity* parent, j1Module* callback = nullptr);
	bool EraseCollider(Collider* collider);
	void DebugDraw();

private:

	std::vector<Collider*> colliders;
	std::vector<std::vector<bool>> matrix_colliders;
	bool debug = false;
};

#endif // __ModuleCollision_H__#pragma once

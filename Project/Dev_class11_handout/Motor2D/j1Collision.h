#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#define MAX_COLLIDERS 400
#include"j1App.h"
#include"j1Module.h"
#include "SDL\include\SDL.h"
#include "j1Object.h"
enum COLLIDER_TYPE
{
	//example
	COLLIDER_NONE = -1,
	collider_link,
	front_link,
	collider_zelda,
	front_zelda,
	collider_arrow,
	collider_link_sword,
	collider_enemy_sword,
	collider_chest,
	collider_button,
	collider_double_button,
	collider_diana,
	collider_change_height,
	collider_jump,
	collider_enemy,
	collider_door,
	collider_warp,
	collider_colour_block,
	collider_fall,	
	coolider_bomb_explosion,
};

struct Collider
{
	SDL_Rect rect = {0,0,0,0};
	bool to_delete = false;
	COLLIDER_TYPE type = COLLIDER_NONE;
	j1Module* callback = nullptr;
	uint logic_height = 0;
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
	bool debug = false;
private:

	std::vector<Collider*> colliders;
	bool matrix[MAX_COLLIDERS][MAX_COLLIDERS];
	//std::vector<std::vector<bool>> matrix_colliders;

};

#endif // __ModuleCollision_H__#pragma once

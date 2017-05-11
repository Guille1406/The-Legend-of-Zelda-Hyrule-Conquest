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
	collider_boss_foot,
	collider_boss_eye,
	collider_boss_little_eye,
	collider_boss_hit,
	collider_boss_explosion,
	collider_boss_recover,
	collider_boss,
	collider_door,
	collider_warp,
	collider_colour_block,
	collider_bush,
	collider_fall,	
	coolider_bomb_explosion,
	collider_heart,
	collider_container_heart,
	collider_movable_object,

	collider_npc,

	collider_electric_ball,

};

enum collider_state {
	not_colliding,
	start_collision,
	im_colliding,
	end_collision,
};
struct Collider
{
	SDL_Rect rect = {0,0,0,0};
	bool to_delete = false;
	COLLIDER_TYPE type = COLLIDER_NONE;
	j1Module* callback = nullptr;
	uint logic_height = 0;
	Entity* parent = nullptr;
	collider_state  state_collider[MAX_COLLIDERS];
	bool is_colliding = false;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Entity* parent, j1Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback),
		parent(parent)
	{
		logic_height = parent->logic_height;
		for (int i = 0; i < MAX_COLLIDERS; i++) {
			state_collider[i] = not_colliding;
		}
	}

	void SetPos(int x, int y, int n_logic_height)
	{
		rect.x = x;
		rect.y = y;
		logic_height = n_logic_height;
	}

	bool CheckCollision(const SDL_Rect& r, int) ;
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

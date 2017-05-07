#ifndef _HYRULEBOMBSOLDIER_ENEMY_
#define _HYRULEBOMBSOLDIER_ENEMY_
#include "j1Enemy.h"
#include"j1Render.h"

struct Enemy_Bomb : public Entity {
	iPoint position = { 0,0 };
	SDL_Rect rang_bomb = {0,0,0,0};
	Collider *bomb_collider_explosion = nullptr;
	SDL_Rect texture_bomb_rect = {0,0,0,0};
	j1Timer Explosion_delay;
	bool bomb_explosion = true;
	Animation Explosion_animation;
};

class HyruleBombSoldier_Enemy : public Enemy {
public:
	HyruleBombSoldier_Enemy();
	HyruleBombSoldier_Enemy(const HyruleBombSoldier_Enemy&);
	~HyruleBombSoldier_Enemy();
	void Action();


public:
	iPoint temp_point = { 0,0 };
	iPoint bomb_point = {0,0};
	iPoint max_bomb_point = {0,0};
	iPoint player_position = { 0,0 };
	float t = 0;
	int off_set = 100;
	bool can_throw_bomb = true;
	bool continue_path_bomb = false;
	j1Timer bomb_timer;
	Enemy_Bomb *bomb;
};


#endif

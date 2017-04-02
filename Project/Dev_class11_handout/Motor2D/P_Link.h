#ifndef _PLINK_
#define _PLINK_


#include "p2Point.h"
#include "SDL\include\SDL.h"
#include "Character.h"
#include <vector>
#include "j1Enemy.h"
#include "j1Collision.h"

class Character;

struct Sword : public Entity {
	iPoint pos;
	SDL_Rect Attack_range;
	Enemy* attached_enemy;
};

class P_Link:public Character  {
public:
	
	P_Link() {
		//sprites_vector = new std::vector<Animation>;
		Link_sword = new Sword();

	}
	~P_Link() {
		//delete sprites_vector;
	}

	void Attack(float dt);
	
	Sword* Link_sword;
	player_event GetEvent();
	void link_sword_collider_update();
	void Orientation_collider_link_sword();

	bool Compare_Link_Sword_Collision(Enemy* enemy);
	void Link_Hurt_Opacity();

	uint Link_Hurt_Audio;
	uint Link_Sword_Audio;
	uint Link_Sword_Collides_Sword_Audio;
public:
	int opacity = 255;
	j1Timer collision_by_enemy_timmer;
	j1Timer enemy_col_sword_sword_timer;
	bool can_pick_up = false;
	bool im_lifting = false;
	bool link_sword_impact_sword = false;
	bool temp = false;

};

#endif


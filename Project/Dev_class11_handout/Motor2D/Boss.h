#ifndef _BOSS_
#define _BOSS_
#include "j1Object.h"
#include "j1Collision.h"
#include "j1App.h"
#include "j1Module.h"
#include "Character.h"

class Foot;
struct Legs;

enum boss_phase {
	boss_phase_1,
	boss_phase_2,
	boss_phase_3
};

enum foot_state {
	foot_idle,
	charging,
	following,
	attacking,
	after_attack,
	back_to_start,
};
enum boss_state {
	boss_idle,
	boss_move,
	boss_attack_link,
	boss_attack_zelda,
	boss_attack_both,
	boss_damaged,
	boss_charging_laser,
	boss_laser,
};


class Boss : public Entity {
public:
	void Draw(int height);
	void UpdateLegs();
	void GetEvent();
	void ExecuteEvent();
	void Move();
	void Attack(Character* focused_character);
	void LaserAttack();
	void CreateColliders();
	void DeleteColliders();

public:
	Boss();
	~Boss();
	iPoint pos;

	bool im_attacking = false;
	bool im_attacking_laser = false;
	bool can_attack = false;
	bool can_move = true;
	//SDL_Texture* boss_texture;
	//SDL_Texture* laser_texture;
	Legs* legs;
	iPoint centre_pos = {0,0};
	boss_state state = boss_idle;
	Foot* attacking_foot = nullptr;
	boss_phase actual_phase = boss_phase_1;

	SDL_Texture* boss_atlas;

	SDL_Rect boss_rect;
	SDL_Rect laser_rect;
	SDL_Rect laser_rect_fire;
	SDL_Rect laser_aim;
	SDL_Rect leg_rect;


	int moving_state = 0;
	float count = 0;


	bool im_active = false;

	std::vector<iPoint> colision_tiles_vec;

	//JUMP OBJECTS
	Object* jump_1;
	Object* jump_2;
	Object* jump_3;
	Object* jump_4;
};

class Foot : public Entity {
public:
	void Draw();
	void UpdatePivots();
	void CreateFootColliders();
	void DeleteFootColliders();
public:
	Foot() {};
	Foot(const Foot&);
	~Foot();
	iPoint pos = {0,0};
	iPoint pivot_point = {0,0};
	iPoint max_point = {0,0};
	iPoint parent_offset = {0,0};
	int live = 10;
	Boss* parent_boss = nullptr;
	SDL_Texture* leg = nullptr;
	int leg_height = 1;
	foot_state actual_foot_state = foot_idle;

	std::vector<iPoint> foot_collider_tiles;

	SDL_Rect foot_rect;
	SDL_Rect foot_rect_invulnerable;
	
};
struct Legs {

public:
	Legs() {};
	Legs(const Legs&);
	~Legs();

	Foot* foot1;
	Foot* foot2;
	Foot* foot3;
	Foot* foot4;
	Boss* parent_boss;

};
#endif 

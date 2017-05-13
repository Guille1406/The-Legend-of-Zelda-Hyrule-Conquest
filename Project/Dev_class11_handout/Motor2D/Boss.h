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
	waiting_for_attack,
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
	bool can_recover = true;
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

	Collider* eye1_collider;
	Collider* eye2_collider;
	Collider* eye3_collider;
	Collider* eye4_collider;

	int foot_live = 5;
	int eye_live = 5;
	int moving_state = 0;
	float count = 0;
	bool im_active = false;

	std::vector<iPoint> colision_tiles_vec;

	j1Timer damaged_boss_timer;
	Collider* recover_collider;

	//JUMP OBJECTS
	Object* jump_1;
	Object* jump_2;
	Object* jump_3;
	Object* jump_4;

	//EYE POS
	//         114,2
	// 8,98          220,98
	//         114,211
	iPoint eye_1 = { pos.x + 114,pos.y + 2 };
	iPoint eye_2 = { pos.x + 8,pos.y + 98 };
	iPoint eye_3 = { pos.x + 220,pos.y + 98 };
	iPoint eye_4 = { pos.x + 114,pos.y + 211 };

	iPoint particles_eye_1 = { eye_1.x + 10, eye_1.y };
	iPoint particles_eye_2 = { eye_2.x + 10, eye_2.y };
	iPoint particles_eye_3 = { eye_3.x + 10, eye_3.y };
	iPoint particles_eye_4 = { eye_4.x + 10, eye_4.y };

	SDL_Rect eye_1_tex = { 0,0,0,0 };
	SDL_Rect eye_2_tex = { 0,0,0,0 };
	SDL_Rect eye_3_tex = { 0,0,0,0 };
	SDL_Rect eye_4_tex = { 0,0,0,0 };

	SDL_Rect eye_phase_2 = { 244,64,80,85 };
	SDL_Rect eye_phase_3 = { 324,91,36,20 };

	SDL_Rect boss_shadow = { 0,243,244,243 };
	SDL_Rect foot_shadow = { 364,64,62,61 };

	SDL_Rect foot_hit = { 427,0,64,64 };
	SDL_Rect eye_hit = { 244,234,80,85 };

	j1Timer eye_hit_time;
	j1Timer foot_hit_timer;
	int eyes_open = 4;

	bool is_eye_1_open = true;
	bool is_eye_2_open = true;
	bool is_eye_3_open = true;
	bool is_eye_4_open = true;


	int dist_link = 0;
	int dist_zelda = 0;
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

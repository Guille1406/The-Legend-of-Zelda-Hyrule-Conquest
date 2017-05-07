#ifndef _ENEMY_
#define _ENEMY_
#include "j1App.h"
#include "j1Module.h"
#include "SDL\include\SDL.h"
#include"j1Object.h"
#include"p2Point.h"
#include"Character.h"
#include "Boss.h"
enum COLLIDER_TYPE;
class Green_Enemy;
#define RANG 150
#define PUSH_DISTANCE 50

enum EnemyState {
	doing_path= 0,
	following_player =0,
	push_back_enemy =1,
	throwing_bomb = 1,
	jumping =2,
	stunned =3,

};

enum OrientationEnemy{
	up_enemy,
	down_enemy,
	left_enemy,
	right_enemy,
	
};

enum enemyType {
	green_enemy = 3847,
	championsoldier_enemy= 3849,
	hyrulebombsoldier_enemy= 3851,
	statue_enemy= 3853,
	rope_enemy= 3850,
	skullrope_enemy=3855,
	rat_enemy = 3852,
	bat_enemy = 3854,
	no_enemy,

};

struct Item_Ofset_Enemy {
	iPoint Shield_dimensions = { 0,0 };
	iPoint up_ofset_item_enemy = {0,0};
	iPoint down_ofset_item_enemy = { 0,0 };
	iPoint right_ofset_item_enemy = { 0,0 };
	iPoint left_ofset_item_enemy = { 0,0 };
};

class Enemy : public Entity {
public:
	Enemy() {

	};
	Enemy(enemyType type): type(type) {

	};
	~Enemy() {};
	void Direction_Push_Election();
	void Enemy_Hurt_Displacement(int & pos, bool add);
	int GetLogicEnemy(int minus_height, iPoint pos);
	void UpdateState();
	void Enemy_Hit_Comprobation(Collider*);
	virtual void Action() {};
	virtual void Rang_Player();
	virtual void DropObject();
	void Direction_Push_Election_ChSoldier();

	
public:
	iPoint max_heigh_jump = { 0,0 };
	SDL_Rect rect = { 0,0,0,0 };
	enemyType type= no_enemy;
	iPoint array_pos = { 0, 0 };
	iPoint tile_pos = { 0, 0 };
	int live = 0;
	bool movable = true;
	std::list<iPoint> Path_Enemy;
	bool passedtile = true;
	Collider* shield_test=nullptr;
	Item_Ofset_Enemy item;
	OrientationEnemy Enemy_Orientation = up_enemy;
	bool tokill = false;
	Character* player_in_range = nullptr;
	std::vector<iPoint> green_enemy_path;
	bool temp = false;
	EnemyState state= doing_path;
	bool enemy_doing_script=false;
	j1Timer script_timer;
};

class j1Enemy : public j1Module {

public:
	j1Enemy()
	{
		//V_MyEnemies = new std::vector<Enemy*>;
	};
	~j1Enemy() {};
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float);
	bool PostUpdate();
	bool CleanUp();
	void Draw(int height, int y);
	iPoint CalculatePath(Enemy*);
	Enemy* Create_Enemy(uint, iPoint Pos, int height);
	bool FindInPath(iPoint, Enemy* enemy);
	void Update_Sword_Collision(Enemy* enemy);

	void OnCollision(Collider* collider1, Collider* collider2);
	void EndCollision(Collider* collider1, Collider* collider2);
	void StartCollision(Collider* collider1, Collider* collider2);
	


public:
	std::vector<Animation*> Green_Enemy_Animation;

	Enemy* enemy_green_perf=nullptr;
	Enemy* enemy_hyrulebomb_perf = nullptr;
	Enemy* enemy_shield_perf = nullptr;
	Enemy* enemy_statue_perf = nullptr;
	Enemy* enemy_rope_perf = nullptr;
	Enemy* enemy_skullrope_perf = nullptr;
	Enemy* enemy_rat_perf = nullptr;
	Enemy* enemy_bat_perf = nullptr;

	Animation Enemies_Appear;

	std::vector<Enemy*> V_MyEnemies;
	SDL_Texture* green_soldier_tex=nullptr;
	bool appear_enemies = false;
	uint one_time_appear = 0;
	uint enemy_dies_audio=0;
	uint enemy_pathfinding_audio = 0;
	Boss* Final_Boss = nullptr;
};

#endif
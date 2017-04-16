#ifndef _ENEMY_
#define _ENEMY_
#include "j1App.h"
#include "j1Module.h"
#include "SDL\include\SDL.h"
#include"j1Object.h"
#include"p2Point.h"
#include"Character.h"
class Green_Enemy;
#define RANG 150
#define PUSH_DISTANCE 50

enum EnemyState {
	doing_path,
	following_player,
	push_back_enemy,
};

enum OrientationEnemy{
	up_enemy,
	down_enemy,
	left_enemy,
	right_enemy,
	
};

enum enemyType {
	green_enemy = 3847,
	championsoldier_enemy= 1498,
	no_enemy,

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
	
	virtual void Action() {};
	virtual void Rang_Player() {};
public:

	SDL_Rect rect = { 0,0,0,0 };
	enemyType type= no_enemy;
	iPoint pix_world_pos = {0, 0};
	iPoint array_pos = { 0, 0 };
	iPoint tile_pos = { 0, 0 };
	int live = 0;
	bool movable = true;
	std::list<iPoint> Path_Enemy;
	bool passedtile = true;
	Collider* shield_test=nullptr;
	iPoint Shield_dimensions = { 0,0 };
	OrientationEnemy Enemy_Orientation = up_enemy;
	bool tokill = false;
	Character* player_in_range = nullptr;
	std::vector<iPoint> green_enemy_path;
	bool temp = false;
	EnemyState state= doing_path;
	bool enemy_doing_script=false;
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
	Enemy* Create_Enemy(uint, iPoint Pos);
	bool FindInPath(iPoint, Enemy* enemy);
	void Update_Sword_Collision(Enemy* enemy);
	
public:
	std::vector<Animation*> Green_Enemy_Animation;
	Enemy* enemy_perf=nullptr;
	std::vector<Enemy*> V_MyEnemies;
	SDL_Texture* green_soldier_tex=nullptr;
	bool appear_enemies = false;
	uint one_time_appear = 0;
	uint enemy_dies_audio=0;
	uint enemy_pathfinding_audio = 0;
};

#endif
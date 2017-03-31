#ifndef _ENEMY_
#define _ENEMY_
#include "j1App.h"
#include "j1Module.h"
#include "SDL\include\SDL.h"
#include"j1Object.h"
#include"p2Point.h"
class Green_Enemy;

enum OrientationEnemy{
	up_enemy,
	down_enemy,
	left_enemy,
	right_enemy,
	
};

enum enemyType {
	green_enemy = 3847,

};


class Enemy : public Entity {
public:
	Enemy() {

	};
	Enemy(enemyType type): type(type) {

	};
	~Enemy() {};

	virtual void Action() {};

public:

	SDL_Rect rect;
	enemyType type;
	iPoint pix_world_pos;
	iPoint array_pos;
	bool movable = true;
	std::list<iPoint> Path_Enemy;
	bool passedtile = true;
	Collider* shield_test;
	OrientationEnemy Enemy_Orientation;
	int live = 0;
	bool tokill = false;
};

class j1Enemy : public j1Module {

public:
	j1Enemy() {
		//V_MyEnemies = new std::vector<Enemy*>;


	};
	~j1Enemy() {};
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float);
	bool PostUpdate();
	bool CleanUp();
	iPoint CalculatePath(Enemy*);
	Enemy* Create_Enemy(uint, iPoint Pos);
	bool FindInPath(iPoint, Enemy* enemy);
	void Update_Sword_Collision(Enemy* enemy);


public:
	std::vector<Animation*> Green_Enemy_Animation;
	Enemy* enemy_perf;
	std::vector<Enemy*> V_MyEnemies;
	SDL_Texture* green_soldier_tex;
};


#endif
#ifndef _ENEMY_
#define _ENEMY_
#include "j1App.h"
#include "j1Module.h"
#include "SDL\include\SDL.h"
#include"j1Object.h"
#include"p2Point.h"
class Green_Enemy;

enum enemyType {
	green_enemy = 106,

};


class Enemy : public Entity {
public:
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

public:
	
	std::vector<Enemy*> V_MyEnemies;
	SDL_Texture* green_soldier_tex;
};


#endif
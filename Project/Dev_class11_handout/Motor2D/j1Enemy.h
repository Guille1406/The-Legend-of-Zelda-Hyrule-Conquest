#ifndef _ENEMY_
#define _ENEMY_
#include "j1App.h"
#include "j1Module.h"
#include "SDL\include\SDL.h"
#include"j1Object.h"
enum enemyType {
	test_enemy,

};


class Enemy : public Entity {
public:
	Enemy() {

	};
	~Enemy() {};

	virtual void Action() {};

public:

	//SDL_Rect rect;
	bool active;
	enemyType type;


};
class j1Enemy : public j1Module {

public:
	j1Enemy() {
		V_Enemies = new std::vector<Enemy*>;


	};
	~j1Enemy() {};

	bool Start();
	bool PreUpdate();
	bool Update(float);
	bool PostUpdate();
	bool CleanUp();

	Enemy* CreateEnemy(char*,pugi::xml_node);


public:
	std::vector<Enemy*>* V_Enemies;

};


#endif
#ifndef _J1PLAYER_
#define _J1PLAYER_

#include "j1Module.h"
#include "p2Point.h"
#include "MainScene.h"
#include "P_Link.h"
#include "P_Zelda.h"
#include "Character.h"

using namespace std;

class P_Link;
class P_Zelda;



class j1Player :public j1Module {
public:
	bool Awake(pugi::xml_node&);
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	void Draw();

	void Move();
	void Change_Player();
	void Chase();
	bool Move_Camera();

public:
	//p2Point<float>* pos;
	bool change = false;
	MainScene* actual_scene;
	int live;
	Character* selected_character;
	Character* other_character;
	P_Link* Link;
	P_Zelda* Zelda;

};



#endif
